import time
import serial
import json
from datetime import datetime
# https://docs.proglove.com/en/gateway-state-command.html


def gateway_state(ctx):
	data = json.dumps({
		"api_version": "1.0", 
		"event_type": "gateway_state!", 
		"event_id": "02114da8-feae-46e3-8b00-a3f7ea8672df",
		"time_created": int(datetime.now().timestamp() * 1000)
	}).encode('utf-8')
	ctx.write(data)
	ctx.flush()
	pass

def send_feedback(ctx, device:str):
	data = json.dump({
		"api_version": "1.0", 
		"event_type": "feedback!", 
		"event_id": "02114da8-feae-46e3-8b00-a3f7ea8672df",
		"time_created": int(datetime.now().timestamp() * 1000),
		"device_serial": device,
		"feedback_action_id": "FEEDBACK_POSITIVE"
	}).encode('utf-8')
	ctx.write(data)
	ctx.flush()
	pass

def send_display(ctx, device:str, duration=4000):
	data = json.dump({
		"api_version": "1.0",
		"event_type": "display!",
		"event_id": "02114da8-feae-46e3-8b00-a3f7ea8672df",
		"time_created": int(datetime.now().timestamp() * 1000),
		"time_validity_duration": duration,
		"device_serial": device,
		"display_template_id": "PG3",
		"display_refresh_type": "DEFAULT",
		"display_fields": [
			{ "display_field_id": 1, "display_field_header": "Storage Unit", "display_field_text": "R15" },
			{ "display_field_id": 2, "display_field_header": "Item", "display_field_text": "Engine 12" },
			{ "display_field_id": 3, "display_field_header": "Quantity", "display_field_text": "10" } ]
	}).encode('utf-8')
	ctx.write(data)
	ctx.flush()
	pass


def notify_device(ctx):
	data = ctx.read(size=1024)
	print(data)
	if len(data) <= 0:
		return False
	rows = data.decode().strip().split('\n')
	for row in rows:
		payload = json.loads(row)
		event = payload["event_type"]
		if event == "scan":
			device = payload["device_serial"]
			barcode = payload["scan_code"]
			print(f"Barcode: {barcode}: {device}")
		elif event == "errors":
			device = payload["device_serial"]
			severity = payload["error_severity"]
			message = payload["error_message"]
			code = payload["error_code"]
			print(f"Error: {severity}:{message} [{code}]")
		elif event == "scanner_state":
			device = payload["device_serial"]
			state = payload["device_connected_state"]
			reason = payload["device_disconnect_reason"]
			print(f"State: {state} - {reason}")
		elif event == "button_pressed":
			device = payload["device_serial"]
			gesture = payload["trigger_gesture"]
			print(f"Button: {gesture}")
			# test ---
			gateway_state(ctx)
		elif event == "gateway_state":
			serial = payload["gateway_serial"]
			version = payload["gateway_app_version"];
			print(f"gateway: {serial} - {version}")
			devices = ["device_connected_list"]
			for item in devices:
				
		pass
	return True

def main():
	ctx = serial.Serial(port="/dev/tty.usbmodemPGGW1015072001", baudrate=115200, timeout=4)
	gateway_state(ctx)
	while ctx.isOpen():
		notify_device(ctx)
		pass
	ctx.close()
	pass

if __name__ == "__main__":
	main()
	pass


function ProScanner(logging) {
	if(!("WebSocket" in window)) {
		alert("WebSocket NOT supported by your Browser!");
		return;
	}
	var socket = null;
	var device_serial = null;

	function startConnect() {
		socket = new WebSocket("ws://localhost:9090");
		socket.onopen = requestDevice;
		socket.onclose = closeConnect;
		socket.onmessage = recvCallback;
	}
	
	function closeConnect() {
		socket.close();
		socket = null;
		device_serial = null;
		logging("Connection is closed..."); 
	}

	function recvCallback(evt) {
		try {
			var event = JSON.parse(evt.data);
			// important!!
			device_serial = event.device_serial;
			// logging("Serial: " + device_serial);
			// switch/case
			if(event.event_type == "scan") {
				logging("Scan: " + event.scan_code);
				return;
			}
			if(event.event_type == "errors") {
				logging(event.error_severity + ": " + event.error_message);
				return;
			}
			if(event.event_type == "scanner_state") {
				if(event.device_connected_state == "STATE_DISCONNECTED") {
					device_serial = null;
				}
				logging("State: " + event.device_connected_state + " = " + event.device_serial);
				return;
			}
			if(event.event_type == "button_pressed") {
				logging("Button: " + event.trigger_gesture);
				return;
			}
		} catch(e) {
			logging(e.message);
		}
	}
	function requestDevice() {
		var data = {
			"api_version": "1.0",
			"event_type": "gateway_state!",
			"event_id": "02114da8-feae-46e3-8b00-a3f7ea8672df",
			"time_created": Date.now()
		}
		var json = JSON.stringify(data);
		socket.send(json);
	}
	function feedback(type) {
		if(device_serial == null) {
			log("Device serial is null!!");
			return;
		}
		var data = {
			"api_version": "1.0",
			"event_type": "feedback!",
			"event_id": "02114da8-feae-46e3-8b00-a3f7ea8672df",
			"time_created": Date.now(),
			"device_serial": device_serial,
			"feedback_action_id": type
		}
		var json = JSON.stringify(data);
		socket.send(json);
	}

	function display() {
		var data = {
			"api_version": "1.0",
			"event_type": "display!",
			"event_id": "02114da8-feae-46e3-8b00-a3f7ea8672df",
			"time_created": Date.now(),
			"time_validity_duration": 1000,
			"device_serial": device_serial,
			"display_template_id": "PG3",
			"display_refresh_type": "DEFAULT",
			"display_fields": [{
				"display_field_id": 1,
				"display_field_header": "Storage Unit",
				"display_field_text": "R15"
			}, {
				"display_field_id": 2,
				"display_field_header": "Item",
				"display_field_text": "Engine 12"
			}, {
				"display_field_id": 3,
				"display_field_header": "Quantity",
				"display_field_text": "10"
			}]
		};
		var json = JSON.stringify(data);
		socket.send(json);
	}
	return {
		startConnect,
		closeConnect,
		requestDevice,
		feedback,
		display,
		FEEDBACK_POSITIVE: "FEEDBACK_POSITIVE",
		FEEDBACK_NEGATIVE: "FEEDBACK_NEGATIVE",
		FEEDBACK_SPECIAL_YELLOW: "FEEDBACK_SPECIAL_YELLOW",
		FEEDBACK_SPECIAL_PURPLE: "FEEDBACK_SPECIAL_PURPLE",
		FEEDBACK_SPECIAL_CYAN: "FEEDBACK_SPECIAL_CYAN"
	}
}

function logging(msg) {
	var e = document.getElementById("content");
	if(e) {
		e.innerHTML += msg + "<br/>";
	}
}

var pg = new ProScanner(logging);
window.addEventListener("load", function(event) {
	pg.startConnect();
}, false);

function sendFeedback() {
	pg.feedback(pg.FEEDBACK_POSITIVE);
}

function sendDisplay() {
	pg.display();
}

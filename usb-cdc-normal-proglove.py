import time
import serial
import json
from datetime import datetime


def main():
	ctx = serial.Serial(port="/dev/tty.usbmodemPGGW1015072001", baudrate=9600, timeout=4)
	while ctx.isOpen():
		data = ctx.read(size=1024)
		if len(data) <= 0:
			continue
		print(data)
		pass
	ctx.close()
	pass

if __name__ == "__main__":
	main()
	pass


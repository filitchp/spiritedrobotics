
init: 
	echo -ne "\x80" > /dev/ttyUSB0
	echo -ne "\x02" > /dev/ttyUSB0
	echo -ne "\x01" > /dev/ttyUSB0
	echo -ne "\xC5" > /dev/ttyUSB0


fire_motor: 
	echo -ne "\x81" > /dev/ttyUSB0
	echo -ne "\x40" > /dev/ttyUSB0
	echo -ne "\x02" > /dev/ttyUSB0
	echo -ne "\x00" > /dev/ttyUSB0
	echo -ne "\xC5" > /dev/ttyUSB0

check_baud:
	stty -F /dev/ttyUSB0 

set_baud_9600:
	stty -F /dev/ttyUSB0 9600

set_baud_38400:
	stty -F /dev/ttyUSB0 38400

set_baud_115200:
	stty -F /dev/ttyUSB0 115200 

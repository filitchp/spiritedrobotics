
init: 
	echo -ne "\x80" > /dev/ttyUSB0
	echo -ne "\x02" > /dev/ttyUSB0
	echo -ne "\x01" > /dev/ttyUSB0
	echo -ne "\xC5" > /dev/ttyUSB0


fire_motor: 
	echo -ne "\x81" > /dev/ttyUSB0
	echo -ne "\x40" > /dev/ttyUSB0
	echo -ne "\x0F" > /dev/ttyUSB0
	echo -ne "\x00" > /dev/ttyUSB0
	echo -ne "\xC5" > /dev/ttyUSB0

fire_motor5: 
	echo -ne "\x85" > /dev/ttyUSB0
	echo -ne "\x40" > /dev/ttyUSB0
	echo -ne "\x02" > /dev/ttyUSB0
	echo -ne "\x00" > /dev/ttyUSB0
	echo -ne "\xC5" > /dev/ttyUSB0

set_all_leds_red:
	echo -ne "\x80" > /dev/ttyUSB0
	echo -ne "\x45" > /dev/ttyUSB0
	echo -ne "\x00" > /dev/ttyUSB0
	echo -ne "\xC5" > /dev/ttyUSB0

set_all_leds_green:
	echo -ne "\x80" > /dev/ttyUSB0
	echo -ne "\x45" > /dev/ttyUSB0
	echo -ne "\x01" > /dev/ttyUSB0
	echo -ne "\xC5" > /dev/ttyUSB0

set_all_leds_blue:
	echo -ne "\x80" > /dev/ttyUSB0
	echo -ne "\x45" > /dev/ttyUSB0
	echo -ne "\x02" > /dev/ttyUSB0
	echo -ne "\xC5" > /dev/ttyUSB0

set_all_leds_fill_inc:
	echo -ne "\x80" > /dev/ttyUSB0
	echo -ne "\x45" > /dev/ttyUSB0
	echo -ne "\x05" > /dev/ttyUSB0
	echo -ne "\xC5" > /dev/ttyUSB0

set_all_leds_pre_pour_fill:
	echo -ne "\x80" > /dev/ttyUSB0
	echo -ne "\x45" > /dev/ttyUSB0
	echo -ne "\x06" > /dev/ttyUSB0
	echo -ne "\xC5" > /dev/ttyUSB0

check_baud:
	stty -F /dev/ttyUSB0 

set_baud_9600:
	stty -F /dev/ttyUSB0 9600

set_baud_38400:
	stty -F /dev/ttyUSB0 38400

set_baud_115200:
	stty -F /dev/ttyUSB0 115200 

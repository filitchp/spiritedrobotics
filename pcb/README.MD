# Barbot Schematic/PCB

## Specification
- SPI bus for LEDs
- UART routed to full-duplex differential RS-485 bus
	- Carried on RJ-45 cable
- All unused processor pins broken out
- 1 unused/configurable op-amp

# To Do List

## Schematic
	
- Diode protection needed for motors
- Unused pairs of RJ-45 - what do we do with them?  break them out?
- Add testpoints!!
- More sheets?
- Frame attributes?
	
## Power
- 5V from USB port for logic supply?
- Where are peripherals powered from?
	- Can the LEDs run off of 6V?
- Large decoupling cap onboard for motor supply?

## Onboard Peripherals
- Relay(s)?
- Piezo?
- General purpose analog inputs -> Liquid level sensor?
- Need pinout for LED strips

## PCB
- Make rough size estimate
- Figure out hole sizes for wire holes
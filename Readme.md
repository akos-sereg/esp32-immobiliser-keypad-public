# esp32-immobiliser-keypad-public

PIN -based immobiliser firmware. This project might be useful for you, if you have a touch-based immobiliser in your car 
( eg. you need to touch two hidden metal surfaces before ignition), and you want to create an extension for it: if you enter 
the correct PIN code, an electromagnetic relay would switch on and connect the circuits. 

Make sure you hide the keypad, and the wiring as well.

Physical device that is using this code:
https://www.hackster.io/akossereg/keypad-immobiliser-05ffdc

## Configuration

You can find and modify the PIN code in `main/include/main.h`, look for `KEYPAD_PIN_CODE`. 

## Wiring

*Keypad*

Row 1-4: connected to GPIO output directly
Col 1-3: connected to GPIO input via 1 kOhm. GPIO inputs grounded via 1.5 kOhm

*Display LEDs*

LEDs connected to GPIO via 110 Ohm

*Relay*

Relays connected to GPIO via BC182 transistor, there is no resistor

*Buzzer*

Buzzer connected via BC182 (1.5 kOhm between GPIO and base; 110 Ohm between Collector and Buzzer Vcc)


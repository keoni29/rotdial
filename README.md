=== Phone dial input ===
Get input from a rotary dial found in old phones.

=== Notes on rotary dial wireing: ===
The rest wire typically the red wire in dials from dutch PTT phones
The count pulse wire is typically the blue wire
The common (ground) wire is typically the yellow wire

Wire up the rest and pulse wire to I/O pins on the arduino (specified below)
Use 10k pullup resistors to 5V on both pins.

=== Notes on light ring wireing: ===
Wire the positive lead of the LED to a resistor and the other end of the resistor to an I/O pin.
Next wire all negative leads of the LED's to ground. The I/O pins can be specified below.
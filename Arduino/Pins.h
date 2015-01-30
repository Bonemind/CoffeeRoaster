#ifndef Pins_h
#define Pins_h

/**
 * An enum containing the pin numbers for every device attached
 */
enum Pin {
	BEAN_STIRRER = 12,
	HEATING_ELEMENT = 11,
	ELECTROMAGNET = 10,
	COOLING_FAN = 9,
	OVEN_FAN = 8
};

/**
 * An array containing the Pin values
 * Used to loop over all pins
 */
extern Pin PinArray[5];

/**
 * Used to store the number of pins
 */
extern int PinCount;

#endif

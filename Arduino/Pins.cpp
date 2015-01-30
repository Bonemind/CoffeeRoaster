#include "Pins.h"

/**
 * Actually fills the PinArray defined in Pins.h with all enumerated pins
 */
Pin PinArray[5] = { BEAN_STIRRER, HEATING_ELEMENT, ELECTROMAGNET, COOLING_FAN, OVEN_FAN };

/**
 * Calculates the number of pins in the array
 */
int PinCount = sizeof(PinArray) / sizeof(PinArray[0]);

#ifndef TempPins_h
#define TempPins_h

/**
 * Defines the pins for the thermocouples
 */
enum TempPins {
	T1SCK = 2,
	T1CS = 3,
	T1SO = 4,
	T2SCK = 5,
	T2CS = 6,
	T2SO = 7
};

/**
 * Global variable holding the current air temp
 */
extern double Airtemp;

/**
 * Global variable holding the current bean temp
 */
extern double Beantemp;

#endif

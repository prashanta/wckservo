/* 	wCK Library 
	Uses Serial1 (Leonardo) for comm. with servo

   	Created by hi@prashanta.me
*/

#ifndef WCKSERVO_H
#define WCKSERVO_H

#if ARDUINO >= 100
#include "Arduino.h"       // for delayMicroseconds,digitalPinToBitMask, etc
#else
#include "WProgram.h"      // for delayMicroseconds
#include "pins_arduino.h"  // for digitalPinToBitMask, etc
#endif

#include <math.h>

#define HEADER	  	0xFF
#define TIME_OUT1	1000
#define CW 			4
#define CCW 		3

class Wckservo{

public:
	/**
 	 * Constructor
 	 * Initializes the serial port
	 */
	Wckservo(uint8_t sid);		
	
	/**
 	 * Send position move command to servo
 	 * @param torque 	Tarque (0-4)
 	 * @param position	Position to move to (0-254)
	 */
	uint8_t posSend(uint8_t torque, uint8_t position);
	
	/**
 	 * Read current position
	 */
	uint8_t posRead();
	
	/**
 	 * Rotate servo Clockwise
 	 * @param speed 	Speed of rotation (0: Stop; 1-15)
	 */	
	uint8_t rotateCW(uint8_t speed);

	/**
 	 * Rotate servo Counter Clockwise
 	 * @param speed 	Speed of rotation (0: Stop; 1-15)
	 */	
	uint8_t rotateCCW(uint8_t speed);	
private:

	uint8_t servoID; /*!< Servo ID (0-30) */
	uint8_t getByte(unsigned long timeout) ;
	void sendOperCommand(uint8_t Data1, uint8_t Data2);
};
#endif
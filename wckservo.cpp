/* 	wCK Library 
	Uses Serial1 (Leonardo) for comm. with servo

   	Created by hi@prashanta.me
*/

#include "Wckservo.h"

Wckservo::Wckservo(uint8_t sid){
	servoID = sid;	
	Serial1.begin(115200); 
}

uint8_t Wckservo::posMove(uint8_t torque, uint8_t position){
	uint8_t pos;
	sendOperCommand((torque<<5)|servoID, position);	
	getByte(TIME_OUT1); // this returns LOAD
	pos = getByte(TIME_OUT1); // this returns POS
	return pos;
}

uint8_t Wckservo::posRead(){
	uint8_t pos;
	sendOperCommand(0xa0|servoID, 0x00);
	getByte(TIME_OUT1); // this returns LOAD
	pos = getByte(TIME_OUT1); // this returns POSITION
	return pos;
}

uint8_t Wckservo::rotateCW(uint8_t speed){
	uint8_t pos;
	sendOperCommand((6<<5)|servoID, (CW<<4)|speed);
	getByte(TIME_OUT1); // this returns LOAD
	pos = getByte(TIME_OUT1); // this returns POSITION
	return pos;
}

uint8_t Wckservo::rotateCCW(uint8_t speed){
	uint8_t pos;
	sendOperCommand((6<<5)|servoID, (CCW<<4)|speed);
	getByte(TIME_OUT1); // this returns LOAD
	pos = getByte(TIME_OUT1); // this returns POSITION
	return pos;
}
	
uint8_t Wckservo::getByte(unsigned long timeout){
	unsigned long start = millis();
  	do{
    	if (SER.available())
      		return SER.read();
	}while (millis() - start <= timeout);
  	return 0;
}

void Wckservo::sendOperCommand(uint8_t Data1, uint8_t Data2){
	char checkSum = (Data1^Data2)&0x7f;	
	SER.write(HEADER);
	SER.write(Data1);
	SER.write(Data2);
	SER.write(checkSum);
}
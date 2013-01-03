/* 	wCK Library 
	Uses Serial1 (Leonardo) for comm. with servo

   	Created by hi@prashanta.me
*/

#include "Wckservo.h"

Wckservo::Wckservo(uint8_t sid){
	servoID = sid;	
	Serial1.begin(115200); 
}

uint8_t Wckservo::PosSend(uint8_t torque, uint8_t position){
	uint8_t current;
	SendOperCommand((torque<<5)|servoID, position);	
	GetByte(TIME_OUT1);
	current = GetByte(TIME_OUT1);
	return current;
}

uint8_t Wckservo::PosRead(){
	uint8_t position;
	SendOperCommand(0xa0|servoID, 0x00);
	GetByte(TIME_OUT1);
	position = GetByte(TIME_OUT1);
	return position;
}

uint8_t Wckservo::rotateCW(uint8_t speed){
	uint8_t current;
	SendOperCommand((6<<5)|servoID, (CW<<4)|speed);
	GetByte(TIME_OUT1);
	current = GetByte(TIME_OUT1);
	return current;
}

uint8_t Wckservo::rotateCCW(uint8_t speed){
	uint8_t current;
	SendOperCommand((6<<5)|servoID, (CCW<<4)|speed);
	GetByte(TIME_OUT1);
	current = GetByte(TIME_OUT1);
	return current;
}
	
uint8_t Wckservo::GetByte(unsigned long timeout){
	unsigned long start = millis();
  	do{
    	if (Serial1.available())
      		return Serial.read();
	}while (millis() - start <= timeout);
  	return 0;
}

void Wckservo::SendOperCommand(uint8_t Data1, uint8_t Data2){
	char checkSum = (Data1^Data2)&0x7f;	
	Serial1.write(HEADER);
	Serial1.write(Data1);
	Serial1.write(Data2);
	Serial1.write(checkSum);
}
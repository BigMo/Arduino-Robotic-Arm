#pragma once
#include "stdafx.h"

class IOManager
{
public:
	void DigitalWrite(byte p_Pin, byte value);
	byte DigitalRead(byte p_Pin);
	byte AnalogRead(byte p_Pin);
	void ServoWrite(void* p_Servo, uint value);
	void* ServoCreate(byte p_Pin);
	void ServoRelease(void* p_Servo);
protected:
private:
} GIOManager;

void IOManager::DigitalWrite(byte p_Pin, byte value)
{
	//digitalWrite(p_Pin, value);
}

byte IOManager::DigitalRead(byte p_Pin)
{
	//return digitalRead(p_Pin);
	return 0;
}

byte IOManager::AnalogRead(byte p_Pin)
{
	//return map(analogRead(p_Pin), 0, 1023, 0, 255);
	return 0;
}

void IOManager::ServoWrite(void* p_Servo, uint value)
{
	assert(p_Servo != NULL);
	//((Servo*)p_Servo)->write(value);
}

void* IOManager::ServoCreate(byte p_Pin)
{
	//Servo *servo = new Servo();
	//servo->attach(p_Pin);
	//return servo;
	return NULL;
}

void IOManager::ServoRelease(void* p_Servo)
{
	assert(p_Servo != NULL);
	delete p_Servo;
}
// RoboticArmDummy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Joint.h"
#include "SensorJoint.h"
#include "ServoJoint.h"
#include "TemplateArm.h"
#include "ServoArm.h"
#include "Capture.h"
#include "Button.h"

#define SLEEPDURATION 20
#define TicksPerSec (1000 / SLEEPDURATION)
#define PIN_TOGGLE_CAPTURE 10
#define PIN_TOGGLE_REPLAY 11

void Setup();
void Loop();

uint pinsServo[5] = { 0, 1, 2, 3, 4 };
uint pinsSensor[5] = { 5, 6, 7, 8, 9 };
ServoArm servoArm;
SensorArm sensorArm;
Capture capture(&servoArm, (SensorArm*)&servoArm, TicksPerSec * 30);
Button buttonToggleCapture, buttonToggleReplay;

#define GETSNSJOINT(x) ((SensorJoint*)servoArm.GetJoint(x))
#define GETSRVJOINT(x) ((ServoJoint*)servoArm.GetJoint(x))

int main()
{
	Setup();
	//while (true)
	//	Loop();

	capture.StartRecording();
	for (uint snap = 0; snap < 10; snap++)
	{
		for (uint i = 0; i < servoArm.GetNumberOfJoints(); i++)
		{
			GETSRVJOINT(i)->SetDegrees(GETSRVJOINT(i)->GetDegrees() + rand() % 10);
		}
		capture.Update();
	}
	capture.Print();
	printf("W8\n");
	system("pause");

	capture.Smooth();

	capture.Print();
	printf("Done\n");
	system("pause");

    return 0;
}

void Setup()
{
	servoArm.Init(5, pinsServo);
	sensorArm.Init(5, pinsSensor);

	buttonToggleCapture.Init(PIN_TOGGLE_CAPTURE);
	buttonToggleReplay.Init(PIN_TOGGLE_REPLAY);
}

void Loop()
{
	servoArm.Update();
	sensorArm.Update();

	buttonToggleCapture.Update();
	buttonToggleReplay.Update();

	if (buttonToggleCapture.WentUp())
		capture.ToggleCapture();
	if (buttonToggleReplay.WentUp())
		capture.ToggleReplay();

	capture.Update();

	//delay(SLEEPDURATION);
}
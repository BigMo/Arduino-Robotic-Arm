// RoboticArmDummy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Joint.h"
#include "SensorJoint.h"
#include "ServoJoint.h"
#include "TemplateArm.h"
#include "ServoArm.h"
#include "Capture.h"

int main()
{
	uint pinsServo[5] = { 0, 1, 2, 3, 4 };
	uint pinsSensor[5] = { 5, 6, 7, 8, 9 };

	ServoArm servoArm = ServoArm();
	servoArm.Init(5, pinsServo);
	SensorArm sensorArm = SensorArm();
	sensorArm.Init(5, pinsSensor);

	servoArm.Update();
	sensorArm.Update();

	Capture* capture = new Capture(&servoArm, 100000);
	capture->StartCapture();
	
	for (int i = 0; i < 1000; i++) 
	{
		for (int j = 0; j < servoArm.GetNumberOfJoints(); j++)
			((ServoJoint*)servoArm.GetJoint(j))->SetDegrees(i * j * 2 + 1);
		capture->Update();
		capture->Print();
		system("pause");
	}

	delete capture;

	printf("Done\n");
	system("pause");

	servoArm.MimicSensorArm(&sensorArm);

    return 0;
}
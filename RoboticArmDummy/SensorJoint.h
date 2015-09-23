#pragma once
#include "Joint.h"

class SensorJoint : public Joint
{
public:
	SensorJoint(byte p_SensorPin);
	void Update();
private:
};

void SensorJoint::Update()
{
	//this->SetDegrees(analogRead(this->GetPin()));
}

SensorJoint::SensorJoint(byte p_SensorPin) : Joint(p_SensorPin)
{ }
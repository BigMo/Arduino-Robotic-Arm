#pragma once
#include "Joint.h"
//#include "Servo.h"

class ServoJoint : public Joint
{
public:
	ServoJoint(byte p_SensorPin);
	virtual void Update();
	void SetDegrees(byte p_Degrees);
protected:
private:
	//Servo m_Servo;
};

ServoJoint::ServoJoint(byte p_SensorPin) : Joint(p_SensorPin)
{
	//m_Servo.attach(p_SensorPin);
}

void ServoJoint::Update()
{
	if (this->HasChanged())
	{
		//m_Servo.write(this->GetDegrees());
	}
}

void ServoJoint::SetDegrees(byte p_Degrees)
{
	Joint::SetDegrees(p_Degrees);
}
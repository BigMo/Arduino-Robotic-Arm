#pragma once
#include "Joint.h"
#include "IOManager.h"

class ServoJoint : public Joint
{
public:
	ServoJoint(byte p_ServoPin);
	virtual void Update();
	void SetDegrees(byte p_Degrees);
protected:
private:
	void* m_Servo;
};

ServoJoint::ServoJoint(byte p_ServoPin) : Joint(p_ServoPin)
{
	this->m_Servo = GIOManager.ServoCreate(p_ServoPin);
}

void ServoJoint::Update()
{
	if (this->HasChanged())
	{
		GIOManager.ServoWrite(this->m_Servo, this->GetDegrees());
	}
}

void ServoJoint::SetDegrees(byte p_Degrees)
{
	Joint::SetDegrees(p_Degrees);
}
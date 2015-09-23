#pragma once
#include "TemplateArm.h"
#include "ServoJoint.h"
#include "SensorJoint.h"
#include "SensorArm.h"

class ServoArm : public TemplateArm<ServoJoint>
{
public:
	ServoArm() : TemplateArm<ServoJoint>() { }
	void MimicSensorArm(SensorArm *p_Arm);
protected:
	virtual ServoJoint* CreateJoint(byte p_Pin);
private:
};

ServoJoint* ServoArm::CreateJoint(byte p_Pin)
{
	return new ServoJoint(p_Pin);
}

void ServoArm::MimicSensorArm(SensorArm *p_Arm)
{
	assert(this->GetNumberOfJoints() == p_Arm->GetNumberOfJoints());
	for (uint i = 0; i < this->GetNumberOfJoints(); i++)
	{
		SensorJoint *sensor = (SensorJoint*)p_Arm->GetJoint(i);
		if (sensor->HasChanged())
		{
			ServoJoint *servo = (ServoJoint*)this->GetJoint(i);
			servo->SetDegrees(sensor->GetDegrees());
		}
	}
}
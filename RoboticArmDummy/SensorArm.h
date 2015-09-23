#pragma once
#include "TemplateArm.h"
#include "SensorJoint.h"

typedef TemplateArm<SensorJoint> SensorTemplateArm;

class SensorArm : public SensorTemplateArm
{
public:
	SensorArm() : SensorTemplateArm() { }
protected:
	virtual SensorJoint* CreateJoint(byte p_Pin);
private:
};

SensorJoint* SensorArm::CreateJoint(byte p_Pin)
{
	return new SensorJoint(p_Pin);
}
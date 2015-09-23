#pragma once
#include "RoboticArm.h"

template <class T>
class TemplateArm : public RoboticArm
{
public:
	void Init(uint p_Count, uint* p_Pins);
protected:
	virtual T* CreateJoint(byte p_Pin) = 0;
private:
};

template <class T>
void TemplateArm<T>::Init(uint p_Count, uint* p_Pins)
{
	RoboticArm::Init(p_Count);

	for (int j = 0; j < p_Count; j++)
		this->AddJoint((uint)j, this->CreateJoint(p_Pins[j]));
}
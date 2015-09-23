#pragma once
#include "Joint.h"

class RoboticArm
{
public:
	RoboticArm();
	~RoboticArm();
	Joint* GetJoint(uint p_Index);
	uint GetNumberOfJoints();
	virtual void Init(uint count);
	virtual void Update();
protected:
	void AddJoint(uint p_Index, Joint* p_Joint);
private:
	Joint **m_pJoints;
	uint m_iNumberOfJoints;
};

RoboticArm::RoboticArm()
{
	this->m_pJoints = NULL;
	this->m_iNumberOfJoints = 0;
}

void RoboticArm::Init(uint p_NumberOfArms)
{
	this->m_iNumberOfJoints = p_NumberOfArms;
	this->m_pJoints = new Joint*[p_NumberOfArms];
}

RoboticArm::~RoboticArm()
{
	for (uint i = 0; i < this->m_iNumberOfJoints; i++)
	{
		Joint *pJoint = this->m_pJoints[i];
		delete pJoint;
	}
	delete[] m_pJoints;
}

void RoboticArm::AddJoint(uint p_Index, Joint* p_Joint)
{
	this->m_pJoints[p_Index] = p_Joint;
}

Joint* RoboticArm::GetJoint(uint p_Index)
{
	if (p_Index >= this->m_iNumberOfJoints)
		return NULL;
	return this->m_pJoints[p_Index];
}

uint RoboticArm::GetNumberOfJoints()
{
	return this->m_iNumberOfJoints;
}

void RoboticArm::Update()
{
	for (uint i = 0; i < this->GetNumberOfJoints(); i++)
		this->GetJoint(i)->Update();
}
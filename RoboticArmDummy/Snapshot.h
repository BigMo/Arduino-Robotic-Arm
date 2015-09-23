#pragma once
#include "RoboticArm.h"

class Snapshot
{
public:
	Snapshot(RoboticArm* p_Arm);
	~Snapshot();
	uint GetNumberOfDegrees();
	byte GetDegree(uint p_Index);
	void SetDegree(uint p_Index, byte p_Degree);
protected:
private:
	byte *m_Degrees;
	uint m_iNumberOfDegrees;
};

Snapshot::Snapshot(RoboticArm *p_Arm)
{
	this->m_iNumberOfDegrees = p_Arm->GetNumberOfJoints();
	this->m_Degrees = new byte[this->m_iNumberOfDegrees];

	for (uint i = 0; i < this->m_iNumberOfDegrees; i++)
		this->m_Degrees[i] = p_Arm->GetJoint(i)->GetDegrees();
}

Snapshot::~Snapshot()
{
	delete[] this->m_Degrees;
}

uint Snapshot::GetNumberOfDegrees()
{
	return this->m_iNumberOfDegrees;
}

byte Snapshot::GetDegree(uint p_Index)
{
	assert(p_Index < this->m_iNumberOfDegrees);
	return this->m_Degrees[p_Index];
}

void Snapshot::SetDegree(uint p_Index, byte p_Degree) 
{
	assert(p_Index < this->m_iNumberOfDegrees);
	this->m_Degrees[p_Index] = p_Degree;
}
#pragma once
#include "stdafx.h"

class Joint
{
public:
	Joint(byte p_Pin);
	byte GetDegrees();
	byte GetPin();
	virtual void Update() = 0;
	bool HasChanged();
protected:
	virtual void SetDegrees(byte degrees);
	void SetChanged(bool p_Changed);
private:
	byte m_Degree;
	byte m_Pin;
	bool m_bDegreesChanged;
};

void Joint::SetDegrees(byte p_Degrees)
{
	bool changed = p_Degrees != this->GetDegrees();
	this->SetChanged(changed);
	if (changed)
		this->m_Degree = p_Degrees;
}

Joint::Joint(byte p_Pin)
{
	this->m_Pin = p_Pin;
}

byte Joint::GetDegrees()
{
	return this->m_Degree;
}

byte Joint::GetPin()
{
	return this->m_Pin;
}

bool Joint::HasChanged()
{
	return this->m_bDegreesChanged;
}

void Joint::SetChanged(bool p_Changed)
{
	this->m_bDegreesChanged = p_Changed;
}
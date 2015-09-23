#pragma once
#include "stdafx.h"
#include "IOManager.h"

struct Button
{
	byte m_iPin;
	bool lastState, currentState;

	void Init(byte p_Pin)
	{
		this->m_iPin = p_Pin;
		this->lastState = this->currentState = false;
	}

	void Update()
	{
		this->lastState = this->currentState;
		this->currentState = GIOManager.DigitalRead(this->m_iPin);
	}

	inline bool IsDown() { return this->currentState; }
	inline bool WentDown() { return this->currentState && !this->lastState; }
	inline bool WentUp() { return !this->currentState && this->lastState; }
	inline bool Changed() { return this->currentState != this->lastState; }
};
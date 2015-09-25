#pragma once
//#include <list>
#include <vector>
#include "Snapshot.h"
#include "RoboticArm.h"

#define POSITIVE 1
#define NEGATIVE -1
#define ZERO 0
#define SIGN(x) (x == 0 ? ZERO : (x < 0 ? NEGATIVE : POSITIVE))
#define GETDEG(x,y) (this->m_Snapshots[x]->GetDegree(y))
#define SETDEG(x,y,z) (this->m_Snapshots[x]->SetDegree(y, z))

class Capture
{
public:
	Capture(ServoArm *m_pServoArm, SensorArm *p_SensorArm, uint p_NumberOfCaptures);
	~Capture();
	void Print();

	void StartRecording();
	void StopRecording();
	bool IsRecording();
	void ResetCapture();
	void ToggleCapture();

	void StartReplay();
	void StopReplay();
	bool IsReplaying();
	void ResetReplay();
	void ToggleReplay();
	
	void Update();
	void Smooth();
protected:
	void SaveSnapshot();
	void ApplyNextSnapshot();
private:
	void SmoothJoint(uint idx);
	void ApplySmoothing(uint pJointIdx, uint pBegin, uint pEnd);
	void ReleaseSnapshots();
	Snapshot* m_Snapshots[10];
	ServoArm *m_pServoArm;
	SensorArm *m_pSensorArm;
	bool m_bRecording;
	bool m_bReplaying;
	uint m_iNumberOfCaptures;
	uint m_iCurrentReplayIndex;
	uint m_iCurrentRecordIndex;
};

Capture::Capture(ServoArm *p_Arm, SensorArm *p_SensorArm, uint p_NumberOfCaptures)
{
	this->m_pServoArm = p_Arm;
	this->m_pSensorArm = p_SensorArm;
	this->m_iNumberOfCaptures = 10;// p_NumberOfCaptures;
	//this->m_Snapshots = new Snapshot*[this->m_iNumberOfCaptures];
	for (uint i = 0; i < this->m_iNumberOfCaptures; i++)
		this->m_Snapshots[i] = NULL;
}

Capture::~Capture()
{
	this->ReleaseSnapshots();
	delete[] this->m_Snapshots;
}

void Capture::Update()
{
	if (this->m_bRecording)
		this->SaveSnapshot();
	else if (this->m_bReplaying)
		this->ApplyNextSnapshot();
}

void Capture::SaveSnapshot()
{
	this->m_iCurrentRecordIndex %= this->m_iNumberOfCaptures;

	Snapshot *snap = this->m_Snapshots[this->m_iCurrentRecordIndex];
	delete snap;
	this->m_Snapshots[this->m_iCurrentRecordIndex] = new Snapshot(this->m_pSensorArm);

	this->m_iCurrentRecordIndex++;
}

void Capture::ApplyNextSnapshot()
{
	this->m_iCurrentReplayIndex %= this->m_iNumberOfCaptures;

	this->m_Snapshots[this->m_iCurrentReplayIndex]->ApplyToArm(this->m_pServoArm);

	this->m_iCurrentReplayIndex++;
}

void Capture::Print()
{
	printf("Number of captures: %i\n", this->m_iNumberOfCaptures);
	
	for (uint i = 0; i < this->m_iNumberOfCaptures; i++)
	{  
		if (this->m_Snapshots[i] == NULL)
			break;
		printf("Snapshot #%i: ", i);
		for (uint i = 0; i < this->m_Snapshots[i]->GetNumberOfDegrees(); i++) {
			printf("%i ", this->m_Snapshots[i]->GetDegree(i));
		}
		printf("\n");
	}     
}

void Capture::ReleaseSnapshots()
{
	for (uint i = 0; i < this->m_iNumberOfCaptures; i++)
		delete m_Snapshots[i];
}

void Capture::StartRecording()
{
	this->m_bRecording = true;
	if (this->m_bReplaying)
		this->StopReplay();
}

void Capture::StopRecording()
{
	this->m_bRecording = false;
}

void Capture::ResetCapture()
{
	this->ReleaseSnapshots();
	this->m_iCurrentRecordIndex = 0;
}

void Capture::StartReplay()
{
	this->m_bReplaying = true;
	if (this->m_bRecording)
		this->StopRecording();
}

void Capture::StopReplay()
{
	this->m_bReplaying = false;
}

void Capture::ResetReplay()
{
	this->m_iCurrentReplayIndex = 0;
}

bool Capture::IsRecording()
{
	return this->m_bRecording;
}

bool Capture::IsReplaying()
{
	return this->m_bReplaying;
}

void Capture::ToggleCapture()
{
	if (this->m_bRecording)
		this->StopRecording();
	else
		this->StartRecording();
}

void Capture::ToggleReplay()
{
	if (this->m_bReplaying)
		this->StopReplay();
	else
		this->StartReplay();
}

void Capture::Smooth()
{
	if (this->m_Snapshots[0] == NULL)
		return;
	for (uint i = 0; i < this->m_Snapshots[0]->GetNumberOfDegrees(); i++)
		this->SmoothJoint(i);
}

void Capture::SmoothJoint(uint idx)
{
	uint begin = 0, end;
	byte currentDir;
	char currentDist = 0;
	bool applySmoothing;
	currentDir = SIGN(GETDEG(0, idx));

	for (uint snap = 1; snap < this->m_iNumberOfCaptures; snap++)
	{
		applySmoothing = false;

		if (this->m_Snapshots[snap] == NULL)
		{
			applySmoothing = true;
		}
		else
		{
			currentDist = GETDEG(snap, idx) - GETDEG(snap - 1, idx);
			byte sign = SIGN(currentDist); //this->m_Snapshots[snap]->GetDegree(idx));
			if (sign != currentDir)
				applySmoothing = true;
		}
		if (applySmoothing) 
		{
			end = snap - 1;
			this->ApplySmoothing(idx, begin, end);
			begin = end;
			currentDir = SIGN(GETDEG(snap, idx) - GETDEG(snap - 1, idx));//SIGN(GETDEG(snap, idx));
		}
	}
}

void Capture::ApplySmoothing(uint pJointIdx, uint pBegin, uint pEnd)
{
	//pBegin = 0
	//pEnd = 3
	//valBegin = 2
	//varEnd = 9
	//steps = 3 - 0 - 1
	//steps - 1 = 2
	//stepSize = (3 - 0) / 2 = 2

	//[pBegin + 1 + steps] = [pBegin] + stepSize
	//[0] = 2				= 2
	//[0 + 1] = 2 + 2 * 1	= 4
	//[0 + 2] = 2 + 2 * 2	= 6
	//[3] = 9				= 9
	byte valBegin = GETDEG(pBegin, pJointIdx), valEnd = GETDEG(pEnd, pJointIdx);
	uint steps = pEnd - pBegin;
	if (steps <= 2)
		return;
	steps -= 1; //skip first and last
	char stepSize = (valEnd - valBegin) / steps;
	
	for (uint i = 0; i < steps; i++)
		SETDEG(pBegin + 1 + i, pJointIdx, GETDEG(pBegin, pJointIdx) + stepSize * (i + 1));
}
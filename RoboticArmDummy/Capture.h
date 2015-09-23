#pragma once
#include <list>
#include "Snapshot.h"
#include "RoboticArm.h"

class Capture
{
public:
	Capture(ServoArm *m_pArm, uint p_NumberOfCaptures);
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
protected:
	void SaveSnapshot();
	void ApplyNextSnapshot();
private:
	void ReleaseSnapshots();
	std::list<Snapshot*> m_Snapshots;
	ServoArm *m_pArm;
	bool m_bRecording;
	bool m_bReplaying;
	uint m_iNumberOfCaptures;
	uint m_iCurrentReplayIndex;
};

Capture::Capture(ServoArm *p_Arm, uint p_NumberOfCaptures)
{
	this->m_pArm = p_Arm;
	this->m_iNumberOfCaptures = p_NumberOfCaptures;
}

Capture::~Capture()
{
	this->ReleaseSnapshots();
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
	m_Snapshots.push_back(new Snapshot(this->m_pArm));
	
	if (m_Snapshots.size() > this->m_iNumberOfCaptures)
	{
		Snapshot *snap = *m_Snapshots.begin();
		m_Snapshots.pop_front();
		delete snap;
	}
}

void Capture::ApplyNextSnapshot()
{
	this->m_iCurrentReplayIndex %= this->m_Snapshots.size();

	int idx = 0;
	for (auto it = m_Snapshots.begin(); it != m_Snapshots.end(); it++, idx++)
		if (idx == m_iCurrentReplayIndex)
			(*it)->ApplyToArm(this->m_pArm);

	this->m_iCurrentReplayIndex++;
}

void Capture::Print()
{
	int idx = 0;
	int numElements = this->m_Snapshots.size();
	printf("Number of captures: %i\n", numElements);
	
	for (auto it = m_Snapshots.begin(); it != m_Snapshots.end(); it++)
	{  
		printf("Snapshot #%i: ", idx++);
		for (uint i = 0; i < (*it)->GetNumberOfDegrees(); i++) {
			printf("%i ", (*it)->GetDegree(i));
		}
		printf("\n");
	}     
}

void Capture::ReleaseSnapshots()
{
	for (auto it = m_Snapshots.begin(); it != m_Snapshots.end(); it++)
		delete *it;
	m_Snapshots.clear();
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
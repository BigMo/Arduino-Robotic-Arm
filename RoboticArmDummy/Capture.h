#pragma once
#include <list>
#include "Snapshot.h"
#include "RoboticArm.h"

class Capture
{
public:
	Capture(RoboticArm *m_pArm, uint p_NumberOfCaptures);
	~Capture();
	void Print();
	void StartCapture();
	void StopCapture();
	void ResetCapture();
	void Update();
protected:
	void SaveSnapshot();
private:
	void ReleaseSnapshots();
	std::list<Snapshot*> m_Snapshots;
	RoboticArm *m_pArm;
	bool m_bRecording;
	uint m_iNumberOfCaptures;
};

Capture::Capture(RoboticArm *p_Arm, uint p_NumberOfCaptures)
{
	this->m_pArm = p_Arm;
	this->m_iNumberOfCaptures = p_NumberOfCaptures;
}

Capture::~Capture()
{
	this->ReleaseSnapshots();
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

void Capture::StartCapture()
{
	this->m_bRecording = true;
}

void Capture::StopCapture()
{
	this->m_bRecording = false;
}

void Capture::ResetCapture()
{
	this->ReleaseSnapshots();
}

void Capture::Update()
{
	if (this->m_bRecording)
		this->SaveSnapshot();
}
#pragma once
#include <list>
#include "Snapshot.h"
#include "RoboticArm.h"

class Capture
{
public:
	Capture();
	~Capture();
	void SaveSnapshot(RoboticArm *p_Arm);
	void Print();
protected:
private:
	std::list<Snapshot*> m_Snapshots;
};

Capture::Capture()
{

}

Capture::~Capture()
{
	for (auto it = m_Snapshots.begin(); it != m_Snapshots.end(); it++)
		delete *it;
}

void Capture::SaveSnapshot(RoboticArm *p_Arm)
{
	m_Snapshots.push_back(new Snapshot(p_Arm));
}

void Capture::Print()
{
	int idx = 0;
	for (auto it = m_Snapshots.begin(); it != m_Snapshots.end(); it++)
	{
		printf("Snapshot #%i: ", idx++);
		for (uint i = 0; i < (*it)->GetNumberOfDegrees(); i++) {
			printf("%i ", (*it)->GetDegree(i));
		}
		printf("\n");
	}
}
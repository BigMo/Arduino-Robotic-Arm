========================================================================
    CONSOLE APPLICATION : RoboticArmDummy Project Overview
========================================================================

This is a dummy-application designed for developing and testing the code before running it on an arduino.

Classes of interest:
	- SensorArm
		Create an instance and call Init once.
		Call Update regularly (updates all of its joints automatically).
	- ServoArm
		Create an instance and call Init once.
		Call Update and MimicSensorArm regularly to "mimic" the current pose of the passed SensorArm.
	- SensorJoint
		Create an instance and call Update regularly.
	- ServoJoint
		Create an instance and call SetDegrees to move the servo, call Update regularly.
	- Capture
		Create an instance and call StartCapture, StopCapture or ReserCapture, call Update regularly.

Basic concept:
	Arms consist of joints.
	Those joints can either get their current rotation (SensorJoint) or set it (ServoJoint).
	To avoid micromanagement, there are two variants of arms:
		SensorArms manage SensorJoints: By calling their joints' Update-method, their joints receive their current rotation.
		ServoArms manage ServoJoints: By calling their joints' Update-method, their joints will apply their rotation.
			-> Call MimicSensorArm to "mimic" the pose of the passed arm
	Also, there's a capture-feature (to implement Teach-In):
	Create a capture, start capturing and call Update to capture the current pose of an arm.

Important:
	This project works with servos that have a max range of 180 degrees (byte: 0-255)!
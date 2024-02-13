#pragma once

class StateVectorComponent
{
public:
	Vector3<float> Position; //0x0000 
	Vector3<float> PrevPosition; //0x000C 
	Vector3<float> r_Velocity; //0x0018 
};
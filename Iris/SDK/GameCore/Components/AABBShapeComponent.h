#pragma once

class AABBShapeComponent
{
public:
	Vector3<float> r_Pos_Lower = { 0, 0, 0 }; //0x0000
	Vector3<float> r_Pos_Upper = { 0, 0, 0 }; //0x000C
	Vector2<float> r_Hitbox = { 0, 0 }; //0x0018 
};
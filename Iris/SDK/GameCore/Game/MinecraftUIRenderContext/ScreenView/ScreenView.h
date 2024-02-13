#pragma once

#include "TreeView.h"

class ScreenView
{
private:
	char pad_0x0000[0x4]; //0x0000
public:
	float deltaTime; //0x0004 
private:
	char pad_0x0008[0x8]; //0x0008
public:
	Vector2<float> ScreenScale; //0x0010 
private:
	char pad_0x0018[0x30]; //0x0018
public:
	VisualTree* tree; //0x0048 
};
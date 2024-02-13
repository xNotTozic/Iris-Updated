#pragma once

#include "RootUIControl.h"

class VisualTree
{
private:
	char pad_0x0000[0x28]; //0x0000
public:
	RootUIControl* root;
};
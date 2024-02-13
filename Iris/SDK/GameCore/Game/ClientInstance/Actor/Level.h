#pragma once

const int Offset_GetTime = 113;

class Dimension {
};

class Level
{
public:
	int GetTime()
	{
		return CallVFunc<Offset_GetTime, int>(this);
	}

	void SetTime(int value)
	{
		return CallVFunc<Offset_GetTime + 1, void, int>(this, value);
	}

	int GetSeed()
	{
		return CallVFunc<Offset_GetTime + 2, int>(this);
	}

    //virtual void getTime(); // 114
    //virtual void setTime(int a1); // 115
    //virtual void getSeed(); // 116

private:
	char pad_0x0000[0xC48]; //0x0000
public:
	Vector3<float> Origin; //0x0BD8 
	Vector3<float> RelativeRayEnd;
	int HitType;
	int BlockFace;
	Vector3<int> IBlockPos; //0x0BF8 
	Vector3<float> AbsoluteHitPos;
};
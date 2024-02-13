#pragma once

class Minecraft
{
private:
	virtual void D0Func(); // 0
public:
	virtual uintptr_t getEntityRegistry();
	virtual uintptr_t getEntityRegistry2();

private:
	char pad_0x0000[0xD8]; //0x0000 // Updated timer offset
public:
	float* timer; //0x00D8 
	float* renderTimer;

	void setTimerSpeed(float tps) {
		*this->timer = tps;
		*this->renderTimer = tps;
	};
};
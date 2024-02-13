#pragma once

class GuiData // ci 0x500
{
public:
private:
	char pad_0x0000[0x30]; //0x0000
public:
	Vector2<float> WindowResolution; //0x0030 
	Vector2<float> WindowResolution2; //0x0038 
	Vector2<float> ScaledResolution; //0x0040 
private:
	char pad_0x0048[0x4]; //0x0048
public:
	float GuiScale; //0x004C 
private:
	char pad_0x0050[0x1A]; //0x0050
public:
	Vector2<short> MousePos; //0x006A 
};
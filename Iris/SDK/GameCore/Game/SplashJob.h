#pragma once

class SplashJob
{
public:
    uintptr_t** VTable; //0x0000 
    float Opacity; //0x0008 
private:
    char pad_0x000C[0xC]; //0x000C
public:
    __int32 SplashState; //0x0018 
    float SplashSpeed; //0x001C 
};
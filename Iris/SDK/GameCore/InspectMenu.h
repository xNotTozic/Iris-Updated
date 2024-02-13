#pragma once

class InspectMenu
{
public:
	uintptr_t baseAddr = 0x0;

	InspectMenu(uintptr_t addr)
	{
		baseAddr = addr;
	}

	float* GetParamaSpeed()
	{
		return reinterpret_cast<float*>(baseAddr + 0x0);
	}

	bool* GetAllInspect()
	{
		return reinterpret_cast<bool*>(baseAddr + 0x4);
	}

	bool* GetFocusInspect()
	{
		return reinterpret_cast<bool*>(baseAddr + 0x5);
	}
};
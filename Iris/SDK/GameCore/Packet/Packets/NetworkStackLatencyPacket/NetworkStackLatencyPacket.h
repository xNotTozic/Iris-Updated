#pragma once

class NetworkStackLatencyPacket : public Packet
{
public:
	NetworkStackLatencyPacket() { init(); };

	__int64 timeStamp;
	bool needsResponse;

	void init()
	{
		static void* sig = nullptr;
		if (!sig) sig = findSig("48 8D 05 ? ? ? ? 48 89 44 24 ? 49 8B"); // Updated to 1.20.51
		// 48 8D 05 ? ? ? ? 48 89 44 24 ? 49 8B 40 30 48 89 44 24 ? 88 54 24 58 48 8B 89 ? ? ? ? 48 8B 01 48 8D 54 24 ? 48 8B 40 10 FF 15 ? ? ? ? C6 43 11 01 
		// 48 8D 05 ? ? ? ? 0F 11 43 ? in 1.20.0.1
		this->setVTable<NetworkStackLatencyPacket>(reinterpret_cast<uintptr_t*>(sig));
	}
};

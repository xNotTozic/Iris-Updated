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
		if (!sig) sig = findSig("48 8D 05 ? ? ? ? 0F 11 43 ?");
		this->setVTable<NetworkStackLatencyPacket>(reinterpret_cast<uintptr_t*>(sig));
	}
};

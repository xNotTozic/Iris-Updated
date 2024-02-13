#pragma once

class MobEquipmentPacket : public Packet
{
public:
    enum ContainerID {
        Invalid = -1,
        Inventory = 0,
        First = 1,
        Last = 100,
        Offhand = 119,
        Armor = 120,
        SelectionSlots = 122,
        PlayerUIOnly = 124,
    };

    MobEquipmentPacket() {
        init();
    }

    MobEquipmentPacket(uint64_t id, int hotbar, int inv) {
        init();
        this->actorRuntimeId = id;
        this->selectedSlot0 = hotbar;
        this->inventorySlot0 = inv;
    };

public:
    __int64 actorRuntimeId;  // 0x28
    ItemStack item; //0x30
    int inventorySlot; //0x0098
    int selectedSlot; //0x009C
    uint8_t containerId; //0x00A0
    uint8_t inventorySlot0; //0x00A1
    uint8_t selectedSlot0; //0x00A2
    uint8_t containerId0; //0x00A3
private:
    char fart;

    void init()
    {
        static void* sig = nullptr;
        if (!sig) sig = findSig("48 8D 0D ? ? ? ? 0F 57 C0 0F 11 00 C7 40 ? ? ? ? ? C7 40 ? ? ? ? ? 48 8D 05 ? ? ? ? 48 89 02 33 C0 48 89 42 28 48 89 42 40 48 89 42 50 48 89 4A 10");
        this->setVTable<MobEquipmentPacket>(reinterpret_cast<uintptr_t*>(sig));
    }
};
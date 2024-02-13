#pragma once

enum class SourceType {
	InvalidInventory = -1,
	ContainerInventory,
	GlobalInventory,
	WorldInteraction,
	CreativeInventory,
	UntrackedInteractionUI = 100,
	NotImplemented = 99999
};

enum class SourceFlags {
	NoFlag,
	WorldInteractionRandom,
};

enum class ContainerId {
	Inventory,
	First,
	Last = 100,
	Offhand = 119,
	Armor,
	Creative,
	Hotbar,
	FixedInventory,
	UI,
	None = 0xFF,
};

class ItemDescriptor {
private:
	char pad_0x0[0x98]; //0x0000
public:
	ItemDescriptor() {
		memset(this, 0x0, sizeof(ItemDescriptor));
	}
	void fromStack(ItemStack* item);
};

class InventoryAction {
public:
	InventoryAction() = default;

	InventoryAction(int slot, ItemStack* sourceItem, ItemStack* targetItem, ContainerId containerId = ContainerId::Inventory, SourceType sourceType = SourceType::ContainerInventory, SourceFlags flags = SourceFlags::NoFlag) {
		memset(this, 0x0, sizeof(InventoryAction));
		this->slot = slot;


		if (sourceItem != nullptr)
			this->sourceItem = *sourceItem;
		if (targetItem != nullptr)
			this->targetItem = *targetItem;

		this->sourceItemDescriptor.fromStack(&this->sourceItem);
		this->targetItemDescriptor.fromStack(&this->targetItem);

		this->sourceType = sourceType;
		this->containerId = containerId;
		this->flags = flags;
	}

public:
	SourceType sourceType;       // 0x0
	ContainerId containerId;         // 0x4
	SourceFlags flags;  // 0x8
	int slot;   //0xC
private:
	ItemDescriptor sourceItemDescriptor; //0x10
	ItemDescriptor targetItemDescriptor; //0xA8

public:
	ItemStack sourceItem;  //0x140
	ItemStack targetItem;  //0x1E0
};

class InventoryTransaction {
private:
	char pad_0x0[8];
public:
	__int64 ptr; // 0x008
private:
	char pad_0x10[0x58 - 16];  //0x10
};

class InventoryTransactionManager {
public:
	uintptr_t* player;               //0x0
	InventoryTransaction transac;  //0x8
private:
	int unknown;  //0x60
	// Total size: 0x68
public:
	void addInventoryAction(InventoryAction const& action, bool idk = false) {
		using InventoryTransactionManager__addAction_t = void(__fastcall*)(InventoryTransactionManager*, InventoryAction const&, bool);
		static auto InventoryTransactionManager__addAction = reinterpret_cast<InventoryTransactionManager__addAction_t>(findSig("48 89 5c 24 ? 55 56 57 41 56 41 57 48 83 ec ? 45 0f b6 f8 4c 8b f2 48 8b f1 48 8b 01 48 8b 88"));
		if (InventoryTransactionManager__addAction) {
			InventoryTransactionManager__addAction(this, action, idk);
		}
	};
};

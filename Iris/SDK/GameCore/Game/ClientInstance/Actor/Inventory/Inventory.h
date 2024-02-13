#pragma once

class ContainerContentChangeListener;
class ItemStack;
class Level;

class Inventory
{
private:
	virtual ~Inventory();
public:

	void dropSlot(int slots)
	{
		static void* dropSlot = findSig("85 D2 ? ? ? ? ? ? 48 89 5C 24 18 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 41");
		CallFunc<void, Inventory*, int, char>(
			dropSlot,
			this,
			slots,
			0
		);
	}
	virtual void init(void);
	virtual void serverInitItemStackIds();
	virtual void addContentChangeListener(ContainerContentChangeListener*);
	virtual void removeContentChangeListener(ContainerContentChangeListener*);
	virtual ItemStack* getItem(int);
	virtual void hasRoomForItem(ItemStack const&);
	virtual void addItem(ItemStack&);
	virtual void addItemWithForceBalance(ItemStack&);
	virtual void addItemToFirstEmptySlot(ItemStack const&);
	virtual void setItem(int, ItemStack const&);
	virtual void setItemWithForceBalance(int, ItemStack const&, bool);
	virtual void removeItem(int, int);
	virtual void removeAllItems(void);
	virtual void removeAllItemsWithForceBalance(void);
	virtual void dropContents(BlockSource&, struct Vec3 const&, bool);
	virtual int getContainerSize(void);
	virtual int getMaxStackSize(void);
	virtual void startOpen(Player&);
	virtual void stopOpen(Player&);
	virtual int getSlotCopies(void);
	virtual int getSlots(void);
	virtual int getEmptySlotsCount(void);
	virtual int getItemCount(ItemStack const&);
	virtual void findFirstSlotForItem(ItemStack const&);
	virtual void canPushInItem(int, int, ItemStack const&);
	virtual void canPullOutItem(int, int, ItemStack const&);
	virtual void setContainerChanged(int);
	virtual void setContainerMoved(void);
	virtual void setCustomName(std::string const&);
	virtual void hasCustomName(void);
	virtual void readAdditionalSaveData(class CompoundTag const&);
	virtual void addAdditionalSaveData(CompoundTag&);
	virtual void createTransactionContext();
	virtual void initializeContainerContents(BlockSource&);
	virtual bool isEmpty(void);
	virtual void add(ItemStack&);
	virtual void canAdd(ItemStack const&);
	virtual void clearSlot(int);
	virtual void clearInventory(int);
	virtual void load(class ListTag const&, class SemVersion const&, Level&);
	virtual int getFirstEmptySlot(void);
	virtual void setContainerSize(int);

};

class PlayerInventory
{
private:
	char pad_0x0000[0x10];  //0x0000
public:
	int hotbarSlot;  //0x0010
private:
	char pad_0x0014[0xAC];  // 0x0014
public:
	Inventory* inventory;  //0x00B0
};

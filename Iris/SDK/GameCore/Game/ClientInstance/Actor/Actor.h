#pragma once

Vector3<float> getNextPoint(Vector3<float> point1, Vector3<float> point2, float multiplier = 14) {
    float xdiff = point2.x - point1.x;
    float ydiff = point2.y - point1.y;
    float zdiff = point2.z - point1.z;

    float distance = std::sqrt(xdiff * xdiff + ydiff * ydiff + zdiff * zdiff);
    float xstep = xdiff / distance;
    float ystep = ydiff / distance;
    float zstep = zdiff / distance;

    xstep *= multiplier;
    ystep *= multiplier;
    zstep *= multiplier;

    Vector3<float> nextPoint;
    nextPoint.x = point1.x + xstep;
    nextPoint.y = point1.y + ystep;
    nextPoint.z = point1.z + zstep;

    return nextPoint;
}

// actor components (ty riester)
#include "../../../Components/StateVectorComponent.h"
#include "../../../Components/AABBShapeComponent.h"
#include "../../../Components/MovementInterpolatorComponent.h"
#include "../../../Components/Components.h"

#include "Level.h"

#include "EntityContext/EntityContext.h"

class ActorFlags;
class ActorLocation;
class ActorDamageSource;
class NewInteractionModel;
class InputMode;
class UIProfanityContext;
class ActorUniqueID;
class ActorDamageCause;
class ItemStack;
class ActorEvent;
class ArmorSlot;
class EquipmentSlot;
class CompoundTag;
class DataLoadHelper;
class ActorLink;
class LevelSoundEvent;
class AnimationComponent;
class RenderParams;
class HandSlot;
class EquipmentTableDefinition;
class Options;
class ActorInteraction;
class ItemStackBase;
class MobEffectInstance;
class Attribute;
class AnimationComponentGroupType;
class ItemUseMethod;
class ResolvedTextObject;
class INpcDialogueData;
class ChalkboardBlockPlayer;
class BlockPlayer;
class Tick;
class ChunkSource;
class LayeredAbilities;
class ChunkPos;
class MovementEventType;
class Item;
class Container;
class EventPacket;
class GameType;

class InitializationMethod;
class VariantParameterList;

// packets
class ChangeDimensionPacket;

class Actor { // v 1.20.62
public:
    virtual ~Actor(void);
    virtual void getStatusFlag();
    virtual void setStatusFlag(bool);
    virtual void outOfWorld(void);
    virtual void reloadHardcoded();
    virtual void reloadHardcodedClient();
    virtual void initializeComponents();
    virtual void reloadComponents();
    virtual void _serverInitItemStackIds(void);
    virtual void _doInitialMove(void);
    virtual bool hasComponent();
    //virtual void ~Actor();
    virtual void resetUserPos(bool);
    virtual void getOwnerEntityType(void);
    virtual void remove(void);
    virtual bool isRuntimePredictedMovementEnabled(void);
    virtual void getFiringPos(void);
    virtual void getInterpolatedBodyRot(float);
    virtual void getInterpolatedHeadRot(float);
    virtual void getInterpolatedBodyYaw(float);
    virtual void getYawSpeedInDegreesPerSecond(void);
    virtual void getInterpolatedRidingOffset(float, int);
    virtual void resetInterpolated(void);
    virtual bool isFireImmune(void);
    virtual void breaksFallingBlocks(void);
    virtual void blockedByShield();
    virtual bool canDisableShield(void);
    virtual void teleportTo(Vector3<float> const&, bool, int, int, bool);
    virtual void lerpMotion(Vector3<float> const&);
    virtual void tryCreateAddActorPacket(void);
    virtual void normalTick(void);
    virtual void baseTick(void);
    virtual void passengerTick(void);
    virtual void startRiding(Actor&);
    virtual void addPassenger(Actor&);
    virtual void getExitTip(std::string const&);
    virtual void getEntityLocNameString(void);
    virtual bool isInWall(void);
    virtual bool isInvisible(void);
    virtual bool canShowNameTag(void);
    virtual void getFormattedNameTag(void);
    virtual void getNameTagTextColor(void);
    virtual void getShadowRadius(void);
    virtual void getHeadLookVector(float);
    virtual bool canInteractWithOtherEntitiesInGame(void);
    virtual void getBrightness(float);
    virtual void playerTouch();
    virtual bool isImmobile(void);
    virtual bool isSilentObserver(void);
    virtual bool isPickable(void);
    virtual bool isSleeping(void);
    virtual void setSleeping(bool);
    virtual void setSneaking(bool);
    virtual bool isBlocking(void);
    virtual bool isDamageBlocked();
    virtual bool isAlive(void);
    virtual bool isOnFire(void);
    virtual bool isSurfaceMob(void);
    virtual bool isTargetable(void);
    virtual bool isLocalPlayer(void);
    virtual bool isPlayer(void);
    virtual bool canAttack(Actor*, bool);
    virtual void setTarget(Actor*);
    virtual bool isValidTarget(Actor*);
    virtual void attack(Actor&);
    virtual void performRangedAttack(Actor&, float);
    virtual void setOwner();
    virtual void setSitting(bool);
    virtual void onTame(void);
    virtual void onFailedTame(void);
    virtual void setStanding(bool);
    virtual bool canPowerJump(void);
    virtual bool isEnchanted(void);
    virtual void shouldRender(void);
    virtual void playAmbientSound(void);
    virtual void getAmbientSound(void);
    virtual bool isInvulnerableTo();
    virtual void getBlockDamageCause(Block const&);
    virtual void doFireHurt(int);
    virtual void onLightningHit(void);
    virtual void feed(int);
    virtual void handleEntityEvent();
    virtual void getPickRadius(void);
    virtual void getActorRendererId(void);
    virtual void despawn(void);
    virtual void setArmor();
    virtual void getArmorMaterialTypeInSlot();
    virtual void getArmorMaterialTextureTypeInSlot();
    virtual void getArmorColorInSlot();
    virtual void setEquippedSlot();
    virtual void setCarriedItem(ItemStack const&);
    virtual void getCarriedItem(void);
    virtual void setOffhandSlot(ItemStack const&);
    virtual void getEquippedTotem(void);
    virtual void consumeTotem(void);
    virtual void save();
    virtual void load();
    virtual void queryEntityRenderer(void);
    virtual void getSourceUniqueID(void);
    virtual bool canFreeze(void);
    virtual void getLiquidAABB();
    virtual void handleInsidePortal();
    virtual void getPortalCooldown(void);
    virtual void getPortalWaitTime(void);
    virtual bool canChangeDimensionsUsingPortal(void);
    virtual void FunctionDimension();
    virtual void changeDimension();
    virtual void getControllingPlayer(void);
    virtual void checkFallDamage(float, bool, bool);
    virtual void causeFallDamageToActor();
    virtual void onSynchedDataUpdate(int);
    virtual bool canAddPassenger(Actor&);
    virtual bool canPickupItem(ItemStack const&);
    virtual bool canBePulledIntoVehicle(void);
    virtual void inCaravan(void);
    virtual void sendMotionPacketIfNeeded();
    virtual bool canSynchronizeNewEntity(void);
    virtual void startSwimming(void);
    virtual void stopSwimming(void);
    virtual void buildDebugInfo(std::string&);
    virtual void getCommandPermissionLevel(void);
    virtual void getDeathTime(void);
    virtual bool canBeAffected();
    virtual bool canBeAffectedByArrow();
    virtual void onEffectAdded();
    virtual void onEffectUpdated();
    virtual void onEffectRemoved();
    virtual bool canObstructSpawningAndBlockPlacement(void);
    virtual void getAnimationComponent(void);
    virtual void openContainerComponent();
    virtual void swing(void);
    virtual void useItem(void*, int, bool);
    virtual void getDebugText(std::vector<std::string>&);
    virtual void getMapDecorationRotation(void);
    virtual void getPassengerYRotation(Actor const&);
    virtual void add(ItemStack&);
    virtual void drop(ItemStack const&, bool);
    virtual void getInteraction();
    virtual bool canDestroyBlock(Block const&);
    virtual void setAuxValue(int);
    virtual void startSpinAttack(void);
    virtual void stopSpinAttack(void);
    virtual void renderDebugServerState();
    virtual void kill(void);
    virtual void die();
    virtual void shouldDropDeathLoot(void);
    virtual void applySnapshot(EntityContext const&, EntityContext const&);
    virtual void getNextStep(float);
    virtual void onPush(Actor&);
    virtual void getLastDeathPos(void);
    virtual void getLastDeathDimension(void);
    virtual bool hasDiedBefore(void);
    virtual void doEnterWaterSplashEffect(void);
    virtual void doExitWaterSplashEffect(void);
    virtual void doWaterSplashEffect(void);
    virtual void _shouldProvideFeedbackOnHandContainerItemSet();
    virtual void _shouldProvideFeedbackOnArmorSet();
    virtual void updateEntitySpecificMolangVariables();
    virtual void shouldTryMakeStepSound(void);
    virtual void _hurt();
    virtual void readAdditionalSaveData();
    virtual void addAdditionalSaveData();
    virtual void _playStepSound(Vector3<int> const&, Block const&);
    virtual void _doAutoAttackOnTouch(Actor&);
};

class Mob : public Actor { // v1.20.62
public:
    virtual void knockback(Actor*, int, float, float, float, float, float);
    virtual void spawnAnim(void);
    virtual void setSprinting(bool);
    virtual void getHurtSound(void);
    virtual void getDeathSound(void);
    virtual void getSpeed(void);
    virtual void setSpeed(float);
    virtual void hurtEffects();
    virtual void aiStep(void);
    virtual void pushActors(void);
    virtual void checkSpawnRules(bool);
    virtual void checkSpawnObstruction(void);
    virtual int getItemUseDuration(void);
    virtual void getItemUseStartupProgress(void);
    virtual void getItemUseIntervalProgress(void);
    virtual void getMaxHeadXRot(void);
    virtual bool isAlliedTo(Mob*);
    virtual void doHurtTarget();
    virtual void getArmorValue(void);
    virtual void hurtArmorSlots();
    virtual void setDamagedArmor();
    virtual void sendArmorDamage();
    virtual void sendArmor();
    virtual void getAllHand(void);
    virtual void getAllEquipment(void);
    virtual void Function25();
    virtual void dropEquipmentOnDeath(void);
    virtual void clearVanishEnchantedItemsOnDeath(void);
    virtual void sendInventory(bool);
    virtual void getDamageAfterEnchantReduction();
    virtual void createAIGoals(void);
    virtual void onBorn(Actor&, Actor&);
    virtual void setItemSlot(ItemStack const&);
    virtual void setTransitioningSitting(bool);
    virtual void getAttackTime(void);
    virtual void _getWalkTargetValue();
    virtual bool canExistWhenDisallowMob(void);
    virtual void initBodyControl(void);
    virtual void newServerAiStep(void);
    virtual void tickDeath(void);
    virtual void _getAdjustedAABBForSpawnCheck(AABB<float> const&, Vector3<float> const&);
};

class Player : public Mob { // v1.20.0.1
public:
    virtual void prepareRegion();
    virtual void destroyRegion(void);
    virtual void suspendRegion(void);
    virtual void _fireDimensionChanged(void);
    virtual void changeDimensionWithCredits();
    virtual void tickWorld();
    virtual void Function5();
    virtual void getTickingOffsets(void);
    virtual void moveView(void);
    virtual void moveSpawnView();
    virtual void checkMovementStats();
    virtual void getCurrentStructureFeature(void);
    virtual bool isAutoJumpEnabled(void);
    virtual void respawn(void);
    virtual void resetRot(void);
    virtual bool isInTrialMode(void);
    virtual void openPortfolio(void);
    virtual void openBook(int, bool, int);
    virtual void openTrading();
    virtual void openChalkboard();
    virtual void openNpcInteractScreen();
    virtual void openInventory(void);
    virtual void displayChatMessage(std::string const&, std::string const&);
    virtual void displayClientMessage(std::string const&);
    virtual void displayTextObjectMessage(std::string const&, std::string const&);
    virtual void displayTextObjectWhisperMessage(std::string const&, std::string const&);
    virtual void displayTextObjectWhisperMessage(std::string const&, std::string const&, std::string const&);
    virtual void displayWhisperMessage(std::string const&, std::string const&, std::string const&, std::string const&);
    virtual void startSleepInBed();
    virtual void stopSleepInBed(bool, bool);
    virtual bool canStartSleepInBed(void);
    virtual void openSign();
    virtual void playEmote(std::string const&, bool);
    virtual bool isLoading(void);
    virtual bool isPlayerInitialized(void);
    virtual void stopLoading(void);
    virtual void setPlayerGameType();
    virtual void initHUDContainerManager(void);
    virtual void _crit(Actor&);
    virtual void getEventing(void);
    virtual void getUserId(void);
    virtual void addExperience(int);
    virtual void addLevels(int);
    virtual void Function42();
    virtual void Function43();
    virtual void Function44();
    virtual void deleteContainerManager(void);
    virtual bool isActorRelevant(Actor const&);
    virtual void Function47();
    virtual void onSuspension(void);
    virtual void onLinkedSlotsChanged(void);
    virtual void Function50();
    virtual void Function51();
    virtual void sendNetworkPacket(Packet&);
    virtual void Function53();
    virtual bool isSimulated(void);
    virtual void getXuid(void);
    virtual void getMovementSettings(void);
    virtual void requestMissingSubChunk();
    virtual void getMaxChunkBuildRadius(void);
    virtual void onMovePlayerPacketNormal(float);
    virtual void _createChunkSource();
    virtual void setAbilities();
    virtual void Function62();
    virtual void Function63();

public:
    PlayerInventory* getSupplies()
    {
        uintptr_t address = reinterpret_cast<uintptr_t>(this);
        return *reinterpret_cast<PlayerInventory**>(address + 0x7B0); // Updated to 1.20.71
        // 0x7E8 1.20.51
        // 0x848 1.20.0.1
    }
    RenderPositionComponent* getRenderPositionComponent() {
        using getRenderPositionComponent = RenderPositionComponent * (__cdecl*)(void*, EntityId*);
        static auto func = reinterpret_cast<getRenderPositionComponent>(findSig(xorstr_("48 89 5C 24 ? 57 48 83 EC ? 48 8B DA BA 6E F3 E8 D4"))); // Updated to 1.20.61
        //40 53 48 83 EC 20 48 8B DA BA 6E F3 E8 D4 1.20.51
        //40 53 48 83 EC ? 48 8B DA BA 6E F3 E8 D4 1.20.0.1
        auto registryBase = *reinterpret_cast<void**>(this->GetEntityContext()->registry);
        return func(registryBase, &this->GetEntityContext()->entityId);
    }

    RuntimeIDComponent* getRuntimeIDComponent() {
        using getRuntimeIDComponent = RuntimeIDComponent * (__cdecl*)(void*, EntityId*);
        static auto func = reinterpret_cast<getRuntimeIDComponent>(findSig(xorstr_("40 53 48 83 EC ? 48 8B DA BA 14 14 A1 3C")));
        auto registryBase = *reinterpret_cast<void**>(this->GetEntityContext()->registry);
        return func(registryBase, &this->GetEntityContext()->entityId);
    }

    RenderRotationComponent* getRenderRotationComponent() {
        using getRenderRotationComponent = RenderRotationComponent * (__cdecl*)(void*, EntityId*);
        static auto func = reinterpret_cast<getRenderRotationComponent>(findSig(xorstr_("40 53 48 83 EC ? 48 8B DA BA A5 3A 53 2B")));
        auto registryBase = *reinterpret_cast<void**>(this->GetEntityContext()->registry);
        return func(registryBase, &this->GetEntityContext()->entityId);
    }

    InventoryTransactionManager* getTransactionManager() {
        static unsigned int offset = 0;
        if (!offset) {
            void* address = findSig(xorstr_("49 8D 8E ? ? ? ? E8 ? ? ? ? 90 48 8D 8D ? ? ? ? E8 ? ? ? ? EB"));
            offset = *reinterpret_cast<int*>(reinterpret_cast<char*>(address) + 3);
        }
        return reinterpret_cast<InventoryTransactionManager*>(reinterpret_cast<char*>(this) + offset);
    }

    GameMode* getGameMode()
    {
        uintptr_t address = reinterpret_cast<uintptr_t>(this);
        return *reinterpret_cast<GameMode**>(address + 0xEC8); // Updated to 1.20.71
        // 0xF10 1.20.51
        // 0xEF8 1.20.0.1
    }

    void DisplayClientMessage(const char* msg)
    {
        TextHolder holder = TextHolder(msg);
        CallFunc<void*, Player*, TextHolder*>(Addresses::DisplayClientMessageAddr, this, &holder);
    }

    void TeleportTo(Vector3<float> pos) // 232 swing?
    {
        CallFunc<void*, Player*, Vector3<float> const&>(Addresses::TeleportToAddr, this, pos);
    }

    DirectPlayerMovementProxy* getMovementProxy()
    {
        using fn = void(__fastcall*)(Player*, std::shared_ptr<void>*);
        static fn oFunc = (fn)Addresses::GetMovementProxy;
        std::shared_ptr<void> ptr;
        oFunc(this, &ptr);
        return (DirectPlayerMovementProxy*)ptr.get(); //TODO: fix proxy crashing
    }
    void jumpFromDaGround()
    {
        //return CallVFunc<342, void>(this);

    }

    void PacketAttack(Player* target)
    {
        Vector3<float> startPoint = GetPosition();
        Vector3<float> endPoint = target->GetPosition();

        float distance = startPoint.distance(endPoint);

        GameMode* gameMode = Game::GetGameMode();

        if (!gameMode)
            return;

        if (distance <= 7)
        {
            gameMode->attack(target);
            return; // already in range so discard teleport packets
        }

        if (distance <= 18)
        {
            Vector3<float> newPoint = getNextPoint(startPoint, endPoint, 7);

            TeleportTo(newPoint);
            gameMode->attack(target);
            lifeboatTpTarget = startPoint;
        }
    }

    Vector3<float>* GetHurttime()
    {
        if (!this)
            return nullptr;

        return reinterpret_cast<Vector3<float>*>((uintptr_t)this + Addresses::hurttimeComponent);
    }

    Vector2<float> getMoveVec()
    {
        Vector2<float> moveVec = { 0.0f, 0.0f };

        if (Game::Core::Keymap[GameInput::Forwards])
            moveVec.x += 1.0f;

        if (Game::Core::Keymap[GameInput::Backwards])
            moveVec.x -= 1.0f;

        if (Game::Core::Keymap[GameInput::Left])
            moveVec.y -= 1.0f;

        if (Game::Core::Keymap[GameInput::Right])
            moveVec.y += 1.0f;

        return moveVec;
    }

    bool isOnGround()
    {
        DirectPlayerMovementProxy* proxy = this->getMovementProxy();

        if (!proxy)
            return true;

        return this->getMovementProxy()->isOnGround();
    }

    Block* GetStandingBlock()
    {
        BlockSource* src = Game::GetInstance()->getBlockSource();

        if (!src)
            return nullptr;

        Vector3<float> blockBelow = this->GetPosition();

        return src->getBlock(blockBelow.ToInt());
    }

    bool IsBadPtr()
    {
        MEMORY_BASIC_INFORMATION mbi;

        if (VirtualQuery(reinterpret_cast<LPCVOID>(this), &mbi, sizeof(mbi)) == 0 ||
            mbi.State != MEM_COMMIT || !(mbi.Protect & PAGE_READWRITE))
            return true;

        if (!this)
            return true;

        return false;
    }

    template<typename T>
    T* try_get()
    {
        if (IsBadReadPtr(this, sizeof(Player)))
            return nullptr;

        uintptr_t ptr = (uintptr_t)this + 0x290; // Updated to 1.20.71
        // 0x2D0 in 1.20.51

        if (ptr >= range_start || ptr <= 0x1000)
            return nullptr;

        if (std::is_same<T, StateVectorComponent>::value)
        {
            return *reinterpret_cast<T**>(ptr);
        }

        if (std::is_same<T, AABBShapeComponent>::value)
        {
            // The iris homeless way
            return *reinterpret_cast<T**>((uintptr_t)this + 0x298); // Updated to 1.20.61
            // 0x2D0 in 1.20.51
        }

        if (std::is_same<T, MovementInterpolatorComponent>::value)
        {
            return *reinterpret_cast<T**>(ptr + 16);
        }

        EntityContext* ctx = GetEntityContext();

        void* registryBase = *reinterpret_cast<void**>(ctx->registry);;
        EntityId* entId = &ctx->entityId;

        if (std::is_same<T, RuntimeIDComponent>::value)
        {
            return CallFunc<T*, void*, EntityId*>(Addresses::TryGet_RuntimeId, registryBase, entId);
        }
    }

    EntityContext* GetEntityContext()
    {
        uintptr_t address = reinterpret_cast<uintptr_t>(this);
        return reinterpret_cast<EntityContext*>((uintptr_t)this + 0x8); // Updated to 1.20.71
        // The same offset in 1.20.51
        // The same offset in 1.20.0.1
    }

    Level* GetLevel()
    {
        uintptr_t address = reinterpret_cast<uintptr_t>(this);
        return *reinterpret_cast<Level**>(address + 0x250); // Updated to 1.20.71
        // 0x288 in 1.20.51
        // 0x260 in 1.20.0.1
    }

    float getVerticalSpeed()
    {
        StateVectorComponent* stateVec = try_get<StateVectorComponent>();

        if (!stateVec)
            return 0;

        float currentYPosition = stateVec->Position.y;
        float lastYPosition = stateVec->PrevPosition.y;

        return (currentYPosition - lastYPosition) * (*Game::GetInstance()->getMinecraft()->timer);
    }

    float GetReachDistance()
    {
        return 3;
    }

    float getHorizontalSpeed()
    {
        StateVectorComponent* stateVec = try_get<StateVectorComponent>();

        if (!stateVec)
            return 0;

        Vector3<float> currentPosition = stateVec->Position;
        currentPosition.y = 0;

        Vector3<float> lastPosition = stateVec->PrevPosition;
        lastPosition.y = 0;

        // i replaced timer 0xD0 to 0xD8 and minecraft from 0xD0 to 0xD8 now timer doesn't work on 1.20.61 idk why
        return (currentPosition.distance(lastPosition)) * /*(*Game::GetInstance()->getMinecraft()->timer)*/ 20;
    }

    Vector3<float> GetPosition(bool tpReady = true)
    {
        return stateVector->Position; // Updated to 1.20.61
    }

    Vector3<int> GetBlockPosition()
    {
        DirectPlayerMovementProxy* proxy = getMovementProxy();

        if (!proxy)
            return { 0,0,0 };

        Vector3<float> pos = proxy->getAABB()->lower;

        return { (int)floor(pos.x), (int)floor(pos.y), (int)floor(pos.z) };
    }

    void SetPos(Vector3<float> pos)
    {
        AABBShapeComponent* shape = try_get<AABBShapeComponent>();

        if (!shape)
            return;

        shape->r_Pos_Lower = pos;
        shape->r_Pos_Upper = pos + shape->r_Hitbox;
    }

    Vector3<float> getDirectionalVector(Vector2<float> rots)
    {
        Vector3<float> tmpVec;

        tmpVec.x = cos(rots.x) * cos(rots.y);
        tmpVec.y = sin(rots.y);
        tmpVec.x = sin(rots.x) * cos(rots.y);

        return tmpVec;
    }

    bool isBot()
    {
        AABBShapeComponent* shape = try_get<AABBShapeComponent>();
        MovementInterpolatorComponent* movement = try_get<MovementInterpolatorComponent>();

        if (!shape || !movement)
            return true;

        if (shape->r_Hitbox.x != 0.6f || shape->r_Hitbox.y != 1.8f)
            return true;

        if (movement->Rotations.x == 0 || movement->Rotations.y == 0)
            return true;

        return false;
    }

    Vector3<float> getLookingVector()
    {
        Vector3<float> tmpVec;

        MovementInterpolatorComponent* move = try_get<MovementInterpolatorComponent>();

        Vector2<float> rots = move->Rotations;

        float cYaw = (rots.y + 90) * 0.01745327;
        float cPitch = rots.x * 0.01745327;

        tmpVec.x = cos(cYaw) * cos(cPitch);
        tmpVec.y = sin(cPitch);
        tmpVec.z = sin(cYaw) * cos(cPitch);

        return tmpVec;
    }

    uintptr_t* GetVTable(int index)
    {
        uintptr_t** VTable = reinterpret_cast<uintptr_t**>(this);

        return VTable[index];
    }
public:
    BUILD_ACCESS(this, struct EntityContext, entityContext, 0x8); // Updated to 1.20.71
    BUILD_ACCESS(this, class EntityLocation*, location, 0x290); // Updated to 1.20.71


    BUILD_ACCESS(this, StateVectorComponent*, stateVector, 0x290); // Updated to 1.20.71
    BUILD_ACCESS(this, AABBShapeComponent*, aabbShape, 0x298); // Updated to 1.20.71
    BUILD_ACCESS(this, MovementInterpolatorComponent*, moveInterpolator, 0x2A0); // Updated to 1.20.71
};

static std::map<__int32, uintptr_t> __o__entitylist = std::map<__int32, uintptr_t>();
static std::map<__int32, uintptr_t> prev___o___entitylist = std::map<__int32, uintptr_t>();
static std::map<__int32, uintptr_t> vprev___o___entitylist = std::map<__int32, uintptr_t>();

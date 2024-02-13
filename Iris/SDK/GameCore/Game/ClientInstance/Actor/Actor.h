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

class Actor {
public:
};

class Mob : public Actor { // v1.20.0.1
public:
    //virtual void setStatusFlag(ActorFlags, bool);
    //virtual int getLastHurtByMob(void);
    //virtual void setLastHurtByMob(Mob*);
    //virtual int getLastHurtByPlayer(void);
    //virtual void setLastHurtByPlayer(Player*);
    //virtual int getLastHurtMob(void);
    //virtual void setLastHurtMob(Actor*);
    //virtual void outOfWorld(void);
    //virtual void reloadHardcoded(/*Actor::InitializationMethod, VariantParameterList const&*/);
    //virtual void reloadHardcodedClient(/*Actor::InitializationMethod, VariantParameterList const&*/);
    //virtual void initializeComponents(/*Actor::InitializationMethod, VariantParameterList const&*/);
    //virtual void reloadComponents(/*Actor::InitializationMethod, VariantParameterList const&*/);
    //virtual void _serverInitItemStackIds(void);
    //virtual void _doInitialMove(void);
    //virtual void hasComponent(HashedString const&);
    //virtual void destructor();
    //virtual void destructor2();
    //virtual void resetUserPos(bool);
    //virtual int getOwnerEntityType(void);
    //virtual void remove(void);
    //virtual bool isRuntimePredictedMovementEnabled(void);
    //virtual int getPredictedMovementValues(void);
    //virtual Vector3<float> getPosition(void);
    //virtual int getPosPrev(void);
    //virtual float getPosExtrapolated(float);
    //virtual float getAttachPos(ActorLocation, float);
    //virtual int getFiringPos(void);
    //virtual void move(struct Vec3 const&);
    //virtual void move(class IActorMovementProxy&, struct Vec3 const&);
    //virtual float getInterpolatedRidingPosition(float);
    //virtual float getInterpolatedBodyRot(float);
    //virtual float getInterpolatedHeadRot(float);
    //virtual float getInterpolatedBodyYaw(float);
    //virtual int getYawSpeedInDegreesPerSecond(void);
    //virtual float getInterpolatedWalkAnimSpeed(float);
    //virtual float getInterpolatedRidingOffset(float, int);
    //virtual void resetInterpolated(void);
    //virtual void updateEntityInside(AABB<float> const&);
    //virtual void updateEntityInside(void);
    //virtual bool isFireImmune(void);
    //virtual void breaksFallingBlocks(void);
    //virtual void blockedByShield(ActorDamageSource const&, Actor&);
    //virtual void canDisableShield(void);
    //virtual void teleportTo(struct Vec3 const&, bool, int, int, bool);
    //virtual void tryTeleportTo(struct Vec3 const&, bool, bool, int, int);
    //virtual void chorusFruitTeleport(struct Vec3 const&);
    //virtual void lerpMotion(struct Vec3 const&);
    //virtual void tryCreateAddActorPacket(void);
    //virtual void normalTick(void);
    //virtual void baseTick(void);
    //virtual void passengerTick(void);
    //virtual void positionPassenger(Actor&, float);
    //virtual void startRiding(Actor&);
    //virtual void addPassenger(Actor&);
    //virtual void flagPassengerToRemove(Actor&);
    //virtual int getExitTip(std::string const&, InputMode, NewInteractionModel);
    //virtual int getEntityLocNameString(void);
    //virtual void intersects(struct Vec3 const&, struct Vec3 const&);
    //virtual bool isInWall(void);
    //virtual bool isInvisible(void);
    //virtual void canShowNameTag(void);
    //virtual void canExistInPeaceful(void);
    //virtual void setNameTagVisible(bool);
    //virtual TextHolder* getNameTag(void);
    //virtual int getNameTagAsHash(void);
    //virtual int getFormattedNameTag(void);
    //virtual void filterFormattedNameTag(UIProfanityContext const&);
    //virtual void setNameTag(std::string const&);
    //virtual int getAlwaysShowNameTag(void);
    //virtual void setScoreTag(std::string const&);
    //virtual int getScoreTag(void);
    //virtual bool isInWater(void);
    //virtual bool isUnderLiquid(MaterialType);
    //virtual bool isOverWater(void);
    //virtual void setBlockMovementSlowdownMultiplier(BlockLegacy const&, struct Vec3 const&);
    //virtual void resetBlockMovementSlowdownMultiplier(void);
    //virtual int getCameraOffset(void);
    //virtual int getShadowHeightOffs(void);
    //virtual int getShadowRadius(void);
    //virtual float getHeadLookVector(float);
    //virtual void canSeeInvisible(void);
    //virtual void canSee(Actor const&);
    //virtual void canSee(struct Vec3 const&);
    //virtual void canInteractWithOtherEntitiesInGame(void);
    //virtual bool isSkyLit(float);
    //virtual float getBrightness(float, class IConstBlockSource const&);
    //virtual void interactPreventDefault(void);
    //virtual void playerTouch(Player&);
    //virtual void onAboveBubbleColumn(bool);
    //virtual void onInsideBubbleColumn(bool);
    //virtual bool isImmobile(void);
    //virtual bool isSilent(void);
    //virtual bool isSilentObserver(void);
    //virtual bool isPickable(void);
    //virtual bool isFishable(void);
    //virtual bool isSleeping(void);
    //virtual void setSleeping(bool);
    //virtual bool isShootable(void);
    //virtual void setSneaking(bool);
    //virtual bool isBlocking(void);
    //virtual bool isDamageBlocked(ActorDamageSource const&);
    //virtual bool isAlive(void);
    //virtual bool isOnFire(void);
    //virtual bool isOnHotBlock(void);
    //virtual bool isCreativeModeAllowed(void);
    //virtual bool isSurfaceMob(void);
    //virtual bool isTargetable(void);
    //virtual bool isLocalPlayer(void);
    //virtual bool isRemotePlayer(void);
    //virtual bool isPlayer(void);
    //virtual bool isAffectedByWaterBottle(void);
    //virtual void canAttack(Actor*, bool);
    //virtual void setTarget(Actor*);
    //virtual bool isValidTarget(Actor*);
    //virtual void attack(Actor&, ActorDamageCause const&);
    //virtual void performRangedAttack(Actor&, float);
    //virtual int getEquipmentCount(void);
    //virtual void setOwner(uint64_t);
    //virtual void setSitting(bool);
    //virtual void onTame(void);
    //virtual void onFailedTame(void);
    //virtual int getInventorySize(void);
    //virtual int getEquipSlots(void);
    //virtual int getChestSlots(void);
    //virtual void setStanding(bool);
    //virtual void canPowerJump(void);
    //virtual void setCanPowerJump(bool);
    //virtual bool isEnchanted(void);
    //virtual void vehicleLanded(struct Vec3 const&, struct Vec3 const&);
    //virtual void shouldRender(void);
    //virtual void playAmbientSound(void);
    //virtual int getAmbientSound(void);
    //virtual bool isInvulnerableTo(ActorDamageSource const&);
    //virtual int getBlockDamageCause(Block const&);
    //virtual void animateHurt(void);
    //virtual void doFireHurt(int);
    //virtual void onLightningHit(void);
    //virtual void onBounceStarted(BlockPos const&, Block const&);
    //virtual void feed(int);
    //virtual void handleEntityEvent(ActorEvent, int);
    //virtual int getPickRadius(void);
    //virtual int getActorRendererId(void);
    //virtual void spawnAtLocation(int, int);
    //virtual void spawnAtLocation(int, int, float);
    //virtual void spawnAtLocation(ItemStack const&, float);
    //virtual void despawn(void);
    //virtual void killed(Actor&);
    //virtual void awardKillScore(Actor&, int);
    //virtual void setArmor(ArmorSlot, ItemStack const&);
    //virtual int getArmor(ArmorSlot);
    //virtual int getAllArmor(void);
    //virtual int getArmorMaterialTypeInSlot(ArmorSlot);
    //virtual int getArmorMaterialTextureTypeInSlot(ArmorSlot);
    //virtual int getArmorColorInSlot(ArmorSlot, int);
    //virtual int getEquippedSlot(EquipmentSlot);
    //virtual void setEquippedSlot(EquipmentSlot, ItemStack const&);
    //virtual void setCarriedItem(ItemStack const&);
    //virtual int getCarriedItem(void);
    //virtual void setOffhandSlot(ItemStack const&);
    //virtual int getEquippedTotem(void);
    //virtual void consumeTotem(void);
    //virtual void save(CompoundTag&);
    //virtual void saveWithoutId(CompoundTag&);
    //virtual void load(CompoundTag const&, DataLoadHelper&);
    //virtual void loadLinks(CompoundTag const&, std::vector<ActorLink>&, DataLoadHelper&);
    //virtual int getEntityTypeId(void);
    //virtual void queryEntityRenderer(void);
    //virtual int getSourceUniqueID(void);
    //virtual void thawFreezeEffect(void);
    //virtual void canFreeze(void);
    //virtual bool isWearingLeatherArmor(void);
    //virtual int getLiquidAABB(MaterialType);
    //virtual void handleInsidePortal(BlockPos const&);
    //virtual int getPortalCooldown(void);
    //virtual int getPortalWaitTime(void);
    //virtual void canChangeDimensionsUsingPortal(void);
    //virtual void changeDimension();
    //virtual void changeDimension(ChangeDimensionPacket const&);
    //virtual int getControllingPlayer(void);
    //virtual void checkFallDamage(float, bool);
    //virtual void causeFallDamage(float, float, ActorDamageSource);
    //virtual void handleFallDistanceOnServer(float, float, bool);
    //virtual void playSynchronizedSound(LevelSoundEvent, struct Vec3 const&, Block const&, bool);
    //virtual void playSynchronizedSound(LevelSoundEvent, struct Vec3 const&, int, bool);
    //virtual void onSynchedFlagUpdate(int, long, long);
    //virtual void onSynchedDataUpdate(int);
    //virtual void canAddPassenger(Actor&);
    //virtual void canPickupItem(ItemStack const&);
    //virtual void canBePulledIntoVehicle(void);
    //virtual void inCaravan(void);
    //virtual bool isLeashableType(void);
    //virtual void tickLeash(void);
    //virtual void sendMotionPacketIfNeeded(void);
    //virtual void canSynchronizeNewEntity(void);
    //virtual void stopRiding(bool, bool, bool);
    //virtual void startSwimming(void);
    //virtual void stopSwimming(void);
    //virtual void buildDebugInfo(std::string&);
    //virtual int getCommandPermissionLevel(void);
    //virtual bool isClientSide(void);
    //virtual int getMutableAttribute(Attribute const&);
    //virtual int getAttribute(Attribute const&);
    //virtual int getDeathTime(void);
    //virtual void heal(int);
    //virtual bool isInvertedHealAndHarm(void);
    //virtual void canBeAffected(int);
    //virtual void canBeAffectedByArrow(MobEffectInstance const&);
    //virtual void onEffectAdded(MobEffectInstance&);
    //virtual void onEffectUpdated(MobEffectInstance&);
    //virtual void onEffectRemoved(MobEffectInstance&);
    //virtual void canObstructSpawningAndBlockPlacement(void);
    //virtual int getAnimationComponent(void);
    //virtual void openContainerComponent(Player&);
    //virtual void swing(void);
    //virtual void useItem(ItemStackBase&, ItemUseMethod, bool);
    //virtual void hasOutputSignal(char);
    //virtual int getOutputSignal(void);
    //virtual int getDebugText(std::vector<std::string>&);
    //virtual int getMapDecorationRotation(void);
    //virtual int getPassengerYRotation(Actor const&);
    //virtual void add(ItemStack&);
    //virtual void drop(ItemStack const&, bool);
    //virtual int getInteraction(Player&, ActorInteraction&, struct Vec3 const&);
    //virtual void canDestroyBlock(Block const&);
    //virtual void setAuxValue(int);
    //virtual void setSize(float, float);
    //virtual void onOrphan(void);
    //virtual void wobble(void);
    //virtual void wasHurt(void);
    //virtual void startSpinAttack(void);
    //virtual void stopSpinAttack(void);
    //virtual void setDamageNearbyMobs(bool);
    //virtual void renderDebugServerState(Options const&);
    //virtual void reloadLootTable(void);
    //virtual void reloadLootTable(EquipmentTableDefinition const&);
    //virtual int getDeletionDelayTimeSeconds(void);
    //virtual void kill(void);
    //virtual void die(ActorDamageSource const&);
    //virtual void shouldDropDeathLoot(void);
    //virtual void shouldTick(void);
    //virtual void applySnapshot(EntityContext const&, EntityContext const&);
    //virtual float getNextStep(float);
    //virtual int getLootTable(void);
    //virtual void onPush(Actor&);
    //virtual int getLastDeathPos(void);
    //virtual int getLastDeathDimension(void);
    //virtual void hasDiedBefore(void);
    //virtual void doWaterSplashEffect(void);
    //virtual void _shouldProvideFeedbackOnHandContainerItemSet(HandSlot, ItemStack const&);
    //virtual void _shouldProvideFeedbackOnArmorSet(ArmorSlot, ItemStack const&);
    //virtual void updateEntitySpecificMolangVariables(RenderParams&);
    //virtual void shouldTryMakeStepSound(void);
    //virtual void canMakeStepSound(void);
    //virtual void _hurt(ActorDamageSource const&, float, bool, bool);
    //virtual void markHurt(void);
    //virtual void _getAnimationComponent(std::shared_ptr<AnimationComponent>&, AnimationComponentGroupType);
    //virtual void readAdditionalSaveData(CompoundTag const&, DataLoadHelper&);
    //virtual void addAdditionalSaveData(CompoundTag&);
    //virtual void _playStepSound(BlockPos const&, Block const&);
    //virtual void _playFlySound(BlockPos const&, Block const&);
    //virtual void _makeFlySound(void);
    //virtual void checkInsideBlocks(float);
    //virtual void pushOutOfBlocks(struct Vec3 const&);
    //virtual void spawnTrailBubbles(void);
    //virtual void updateInsideBlock(void);
    //virtual void _removePassenger(uint64_t const&, bool, bool, bool);
    //virtual void _onSizeUpdated(void);
    //virtual void _doAutoAttackOnTouch(Actor&);
    //virtual void knockback(Actor*, int, float, float, float, float, float);
    //virtual void spawnAnim(void);
    //virtual void setSprinting(bool);
    //virtual int getHurtSound(void);
    //virtual int getDeathSound(void);
    //virtual int getSpeed(void);
    //virtual void setSpeed(float);
    //virtual void hurtEffects(ActorDamageSource const&, float, bool, bool);
    //virtual int getMeleeWeaponDamageBonus(Actor);
    //virtual int getMeleeKnockbackBonus(void);
    //virtual void travel(float, float, float, bool);
    //virtual void applyFinalFriction(float, bool);
    //virtual void aiStep(void);
    //virtual void aiStep2(class IMobMovementProxy&);
    //virtual void pushActors(void);
    //virtual void lookAt(Actor*, float, float);
    //virtual bool isLookingAtAnEntity(void);
    //virtual void checkSpawnRules(bool);
    //virtual void checkSpawnObstruction(void);
    //virtual float getAttackAnim(float);
    //virtual int getItemUseDuration(void);
    //virtual int getItemUseStartupProgress(void);
    //virtual int getItemUseIntervalProgress(void);
    //virtual int getItemUseIntervalAxis(void);
    //virtual int getTimeAlongSwing(void);
    //virtual void ate(void);
    //virtual int getMaxHeadXRot(void);
    //virtual bool isAlliedTo(Actor);
    //virtual void doHurtTarget(Actor*, ActorDamageCause const&);
    //virtual void canBeControlledByPassenger(void);
    //virtual void leaveCaravan(void);
    //virtual void joinCaravan(Actor);
    //virtual void hasCaravanTail(void);
    //virtual int getCaravanHead(void);
    //virtual int getArmorValue(void);
    //virtual int getArmorCoverPercentage(void);
    //virtual int getToughnessValue(void);
    //virtual void hurtArmorSlots(ActorDamageSource const&, int, std::bitset<4ul>);
    //virtual void setDamagedArmor(ArmorSlot, ItemStack const&);
    //virtual void sendArmorDamage(std::bitset<4ul>);
    //virtual void sendArmor(std::bitset<4ul>);
    //virtual void containerChanged(int);
    //virtual void updateEquipment(void);
    //virtual void clearEquipment(void);
    //virtual int getAllArmorID(void);
    //virtual int getAllHand(void);
    //virtual int getAllEquipment(void);
    //virtual int getArmorTypeHash(void);
    //virtual void dropEquipmentOnDeath(ActorDamageSource const&, int);
    //virtual void dropEquipmentOnDeath(void);
    //virtual void clearVanishEnchantedItemsOnDeath(void);
    //virtual void sendInventory(bool);
    //virtual float getDamageAfterEnchantReduction(ActorDamageSource const&, float);
    //virtual float getDamageAfterArmorReduction(ActorDamageSource const&, float);
    //virtual float getDamageAfterResistanceEffect(ActorDamageSource const&, float);
    //virtual void createAIGoals(void);
    //virtual void onBorn(Actor&, Actor&);
    //virtual void setItemSlot(EquipmentSlot, ItemStack const&);
    //virtual void setTransitioningSitting(bool);
    //virtual void attackAnimation(Actor*, float);
    //virtual int getAttackTime(void);
    //virtual void _getWalkTargetValue(BlockPos const&);
    //virtual void canExistWhenDisallowMob(void);
    //virtual void ascendLadder(void);
    //virtual void ascendBlockByJumping(void);
    //virtual void descendBlockByCrouching(void);
    //virtual void dropContainer(void);
    //virtual void initBodyControl(void);
    //virtual void jumpFromGround(IConstBlockSource const&);
    //virtual void jumpFromGround(class IMobMovementProxy&, IConstBlockSource const&);
    //virtual void newServerAiStep(void);
    //virtual void _serverAiMobStep(void);
    //virtual void dropBags(void);
    //virtual void tickDeath(void);
    //virtual void updateGliding(void);
    //virtual void _allowAscendingScaffolding(void);
    //virtual void _getAdjustedAABBForSpawnCheck(AABB<float> const&, struct Vec3 const&);
};

class Player : public Mob { // v1.20.0.1
public:
    virtual void setStatusFlag(ActorFlags, bool);
    virtual int getLastHurtByMob(void);
    virtual void setLastHurtByMob(Mob*);
    virtual int getLastHurtByPlayer(void);
    virtual void setLastHurtByPlayer(Player*);
    virtual int getLastHurtMob(void);
    virtual void setLastHurtMob(Actor*);
    virtual void outOfWorld(void);
    virtual void reloadHardcoded(/*Actor::InitializationMethod, VariantParameterList const&*/);
    virtual void reloadHardcodedClient(/*Actor::InitializationMethod, VariantParameterList const&*/);
    virtual void initializeComponents(/*Actor::InitializationMethod, VariantParameterList const&*/);
    virtual void reloadComponents(/*Actor::InitializationMethod, VariantParameterList const&*/);
    virtual void _serverInitItemStackIds(void);
    virtual void _doInitialMove(void);
    virtual void hasComponent(HashedString const&);
    virtual void destructor();
    virtual void destructor2();
    virtual void resetUserPos(bool);
    virtual int getOwnerEntityType(void);
    virtual void remove(void);
    virtual bool isRuntimePredictedMovementEnabled(void);
    virtual int getPredictedMovementValues(void);
    virtual Vector3<float> getPosition(void);
    virtual int getPosPrev(void);
    virtual float getPosExtrapolated(float);
    virtual float getAttachPos(ActorLocation, float);
    virtual int getFiringPos(void);
    virtual void move(struct Vec3 const&);
    virtual void move(class IActorMovementProxy&, struct Vec3 const&);
    virtual float getInterpolatedRidingPosition(float);
    virtual float getInterpolatedBodyRot(float);
    virtual float getInterpolatedHeadRot(float);
    virtual float getInterpolatedBodyYaw(float);
    virtual int getYawSpeedInDegreesPerSecond(void);
    virtual float getInterpolatedWalkAnimSpeed(float);
    virtual float getInterpolatedRidingOffset(float, int);
    virtual void resetInterpolated(void);
    virtual void updateEntityInside(AABB<float> const&);
    virtual void updateEntityInside(void);
    virtual bool isFireImmune(void);
    virtual void breaksFallingBlocks(void);
    virtual void blockedByShield(ActorDamageSource const&, Actor&);
    virtual void canDisableShield(void);
    virtual void teleportTo(Vector3<float>, bool, int, int, bool);
    virtual void tryTeleportTo(struct Vec3 const&, bool, bool, int, int);
    virtual void chorusFruitTeleport(struct Vec3 const&);
    virtual void lerpMotion(Vector3<float> const&);
    virtual void tryCreateAddActorPacket(void);
    virtual void normalTick(void);
    virtual void baseTick(void);
    virtual void passengerTick(void);
    virtual void positionPassenger(Actor&, float);
    virtual void startRiding(Actor&);
    virtual void addPassenger(Actor&);
    virtual void flagPassengerToRemove(Actor&);
    virtual int getExitTip(std::string const&, InputMode, NewInteractionModel);
    virtual int getEntityLocNameString(void);
    virtual void intersects(struct Vec3 const&, struct Vec3 const&);
    virtual bool isInWall(void);
    virtual bool isInvisible(void);
    virtual void canShowNameTag(void);
    virtual void canExistInPeaceful(void);
    virtual void setNameTagVisible(bool);
    virtual TextHolder* getNameTag(void);
    virtual int getNameTagAsHash(void);
    virtual int getFormattedNameTag(void);
    virtual void filterFormattedNameTag(UIProfanityContext const&);
    virtual void setNameTag(std::string const&);
    virtual int getAlwaysShowNameTag(void);
    virtual void setScoreTag(std::string const&);
    virtual int getScoreTag(void);
    virtual bool isInWater(void);
    virtual bool isUnderLiquid(MaterialType);
    virtual bool isOverWater(void);
    virtual void setBlockMovementSlowdownMultiplier(BlockLegacy const&, struct Vec3 const&);
    virtual void resetBlockMovementSlowdownMultiplier(void);
    virtual int getCameraOffset(void);
    virtual int getShadowHeightOffs(void);
    virtual int getShadowRadius(void);
    virtual float getHeadLookVector(float);
    virtual bool canSeeInvisible(void);
    virtual bool canSee(Player const&);
    virtual bool canSee(Vector3<float> const&);
    virtual void canInteractWithOtherEntitiesInGame(void);
    virtual bool isSkyLit(float);
    virtual float getBrightness(float, BlockSource* const&);
    virtual void interactPreventDefault(void);
    virtual void playerTouch(Player&);
    virtual void onAboveBubbleColumn(bool);
    virtual void onInsideBubbleColumn(bool);
    virtual bool isImmobile(void);
    virtual bool isSilent(void);
    virtual bool isSilentObserver(void);
    virtual bool isPickable(void);
    virtual bool isFishable(void);
    virtual bool isSleeping(void);
    virtual void setSleeping(bool);
    virtual bool isShootable(void);
    virtual void setSneaking(bool);
    virtual bool isBlocking(void);
    virtual bool isDamageBlocked(ActorDamageSource const&);
    virtual bool isAlive(void);
    virtual bool isOnFire(void);
    virtual bool isOnHotBlock(void);
    virtual bool isCreativeModeAllowed(void);
    virtual bool isSurfaceMob(void);
    virtual bool isTargetable(void);
    virtual bool isLocalPlayer(void);
    virtual bool isRemotePlayer(void);
    virtual bool isPlayer(void);
    virtual bool isAffectedByWaterBottle(void);
    virtual void canAttack(Actor*, bool);
    virtual void setTarget(Actor*);
    virtual bool isValidTarget(Actor*);
    virtual void attack(Actor&, ActorDamageCause const&);
    virtual void performRangedAttack(Actor&, float);
    virtual int getEquipmentCount(void);
    virtual void setOwner(uint64_t);
    virtual void setSitting(bool);
    virtual void onTame(void);
    virtual void onFailedTame(void);
    virtual int getInventorySize(void);
    virtual int getEquipSlots(void);
    virtual int getChestSlots(void);
    virtual void setStanding(bool);
    virtual void canPowerJump(void);
    virtual void setCanPowerJump(bool);
    virtual bool isEnchanted(void);
    virtual void vehicleLanded(struct Vec3 const&, struct Vec3 const&);
    virtual void shouldRender(void);
    virtual void playAmbientSound(void);
    virtual int getAmbientSound(void);
    virtual bool isInvulnerableTo(ActorDamageSource const&);
    virtual int getBlockDamageCause(Block const&);
    virtual void animateHurt(void);
    virtual void doFireHurt(int);
    virtual void onLightningHit(void);
    virtual void onBounceStarted(BlockPos const&, Block const&);
    virtual void feed(int);
    virtual void handleEntityEvent(ActorEvent, int);
    virtual int getPickRadius(void);
    virtual int getActorRendererId(void);
    virtual void spawnAtLocation(int, int);
    virtual void spawnAtLocation(int, int, float);
    virtual void spawnAtLocation(ItemStack const&, float);
    virtual void despawn(void);
    virtual void killed(Actor&);
    virtual void awardKillScore(Actor&, int);
    virtual void setArmor(ArmorSlot, ItemStack const&);
    virtual int getArmor(ArmorSlot);
    virtual int getAllArmor(void);
    virtual int getArmorMaterialTypeInSlot(ArmorSlot);
    virtual int getArmorMaterialTextureTypeInSlot(ArmorSlot);
    virtual int getArmorColorInSlot(ArmorSlot, int);
    virtual int getEquippedSlot(EquipmentSlot);
    virtual void setEquippedSlot(EquipmentSlot, ItemStack const&);
    virtual void setCarriedItem(ItemStack const&);
    virtual int getCarriedItem(void);
    virtual void setOffhandSlot(ItemStack const&);
    virtual int getEquippedTotem(void);
    virtual void consumeTotem(void);
    virtual void save(CompoundTag&);
    virtual void saveWithoutId(CompoundTag&);
    virtual void load(CompoundTag const&, DataLoadHelper&);
    virtual void loadLinks(CompoundTag const&, std::vector<ActorLink>&, DataLoadHelper&);
    virtual int getEntityTypeId(void);
    virtual void queryEntityRenderer(void);
    virtual int getSourceUniqueID(void);
    virtual void thawFreezeEffect(void);
    virtual void canFreeze(void);
    virtual bool isWearingLeatherArmor(void);
    virtual int getLiquidAABB(MaterialType);
    virtual void handleInsidePortal(BlockPos const&);
    virtual int getPortalCooldown(void);
    virtual int getPortalWaitTime(void);
    virtual void canChangeDimensionsUsingPortal(void);
    virtual void changeDimension(/*AutomaticID<Dimension, int>*/);
    virtual void changeDimension(ChangeDimensionPacket const&);
    virtual int getControllingPlayer(void);
    virtual void checkFallDamage(float, bool);
    virtual void causeFallDamage(float, float, ActorDamageSource);
    virtual void handleFallDistanceOnServer(float, float, bool);
    virtual void playSynchronizedSound(class LevelSoundEvent, struct Vec3 const&, Block const&, bool);
    virtual void playSynchronizedSound(class LevelSoundEvent, struct Vec3 const&, int, bool);
    virtual void onSynchedFlagUpdate(int, long, long);
    virtual void onSynchedDataUpdate(int);
    virtual void canAddPassenger(Actor&);
    virtual void canPickupItem(ItemStack const&);
    virtual void canBePulledIntoVehicle(void);
    virtual void inCaravan(void);
    virtual bool isLeashableType(void);
    virtual void tickLeash(void);
    virtual void sendMotionPacketIfNeeded(void);
    virtual void canSynchronizeNewEntity(void);
    virtual void stopRiding(bool, bool, bool);
    virtual void startSwimming(void);
    virtual void stopSwimming(void);
    virtual void buildDebugInfo(std::string&);
    virtual int getCommandPermissionLevel(void);
    virtual bool isClientSide(void);
    virtual int getMutableAttribute(Attribute const&);
    virtual int getAttribute(Attribute const&);
    virtual int getDeathTime(void);
    virtual void heal(int);
    virtual bool isInvertedHealAndHarm(void);
    virtual void canBeAffected(int);
    virtual void canBeAffectedByArrow(MobEffectInstance const&);
    virtual void onEffectAdded(MobEffectInstance&);
    virtual void onEffectUpdated(MobEffectInstance&);
    virtual void onEffectRemoved(MobEffectInstance&);
    virtual void canObstructSpawningAndBlockPlacement(void);
    virtual int getAnimationComponent(void);
    virtual void openContainerComponent(Player&);
    virtual void swing(void);
    virtual void useItem(ItemStackBase&, ItemUseMethod, bool);
    virtual void hasOutputSignal(char);
    virtual int getOutputSignal(void);
    virtual int getDebugText(std::vector<std::string>&);
    virtual int getMapDecorationRotation(void);
    virtual int getPassengerYRotation(Actor const&);
    virtual void add(ItemStack&);
    virtual void drop(ItemStack const&, bool);
    virtual int getInteraction(Player&, ActorInteraction&, struct Vec3 const&);
    virtual void canDestroyBlock(Block const&);
    virtual void setAuxValue(int);
    virtual void setSize(float, float);
    virtual void onOrphan(void);
    virtual void wobble(void);
    virtual void wasHurt(void);
    virtual void startSpinAttack(void);
    virtual void stopSpinAttack(void);
    virtual void setDamageNearbyMobs(bool);
    virtual void renderDebugServerState(Options const&);
    virtual void reloadLootTable(void);
    virtual void reloadLootTable(EquipmentTableDefinition const&);
    virtual int getDeletionDelayTimeSeconds(void);
    virtual void kill(void);
    virtual void die(ActorDamageSource const&);
    virtual void shouldDropDeathLoot(void);
    virtual void shouldTick(void);
    virtual void applySnapshot(EntityContext const&, EntityContext const&);
    virtual float getNextStep(float);
    virtual int getLootTable(void);
    virtual void onPush(Actor&);
    virtual int getLastDeathPos(void);
    virtual int getLastDeathDimension(void);
    virtual void hasDiedBefore(void);
    virtual void doWaterSplashEffect(void);
    virtual void _shouldProvideFeedbackOnHandContainerItemSet(HandSlot, ItemStack const&);
    virtual void _shouldProvideFeedbackOnArmorSet(ArmorSlot, ItemStack const&);
    virtual void updateEntitySpecificMolangVariables(RenderParams&);
    virtual void shouldTryMakeStepSound(void);
    virtual void canMakeStepSound(void);
    virtual void _hurt(ActorDamageSource const&, float, bool, bool);
    virtual void markHurt(void);
    virtual void _getAnimationComponent(std::shared_ptr<AnimationComponent>&, AnimationComponentGroupType);
    virtual void readAdditionalSaveData(CompoundTag const&, DataLoadHelper&);
    virtual void addAdditionalSaveData(CompoundTag&);
    virtual void _playStepSound(BlockPos const&, Block const&);
    virtual void _playFlySound(BlockPos const&, Block const&);
    virtual void _makeFlySound(void);
    virtual void checkInsideBlocks(float);
    virtual void pushOutOfBlocks(struct Vec3 const&);
    virtual void spawnTrailBubbles(void);
    virtual void updateInsideBlock(void);
    virtual void _removePassenger(uint64_t const&, bool, bool, bool);
    virtual void _onSizeUpdated(void);
    virtual void _doAutoAttackOnTouch(Actor&);
    virtual void knockback(Actor*, int, float, float, float, float, float);
    virtual void spawnAnim(void);
    virtual void setSprinting(bool);
    virtual int getHurtSound(void);
    virtual int getDeathSound(void);
    virtual int getSpeed(void);
    virtual void setSpeed(float);
    virtual void hurtEffects(ActorDamageSource const&, float, bool, bool);
    virtual int getMeleeWeaponDamageBonus(Actor);
    virtual int getMeleeKnockbackBonus(void);
    virtual void travel(float, float, float, bool);
    virtual void applyFinalFriction(float, bool);
    virtual void aiStep(void);
    virtual void aiStep2(class IMobMovementProxy&);
    virtual void pushActors(void);
    virtual void lookAt(Actor*, float, float);
    virtual bool isLookingAtAnEntity(void);
    virtual void checkSpawnRules(bool);
    virtual void checkSpawnObstruction(void);
    virtual float getAttackAnim(float);
    virtual int getItemUseDuration(void);
    virtual int getItemUseStartupProgress(void);
    virtual int getItemUseIntervalProgress(void);
    virtual int getItemUseIntervalAxis(void);
    virtual int getTimeAlongSwing(void);
    virtual void ate(void);
    virtual int getMaxHeadXRot(void);
    virtual bool isAlliedTo(Actor);
    virtual void doHurtTarget(Actor*, ActorDamageCause const&);
    virtual void canBeControlledByPassenger(void);
    virtual void leaveCaravan(void);
    virtual void joinCaravan(Actor);
    virtual void hasCaravanTail(void);
    virtual int getCaravanHead(void);
    virtual int getArmorValue(void);
    virtual int getArmorCoverPercentage(void);
    virtual int getToughnessValue(void);
    virtual void hurtArmorSlots(ActorDamageSource const&, int, std::bitset<4ul>);
    virtual void setDamagedArmor(ArmorSlot, ItemStack const&);
    virtual void sendArmorDamage(std::bitset<4ul>);
    virtual void sendArmor(std::bitset<4ul>);
    virtual void containerChanged(int);
    virtual void updateEquipment(void);
    virtual void clearEquipment(void);
    virtual int getAllArmorID(void);
    virtual int getAllHand(void);
    virtual int getAllEquipment(void);
    virtual int getArmorTypeHash(void);
    virtual void dropEquipmentOnDeath(ActorDamageSource const&, int);
    virtual void dropEquipmentOnDeath(void);
    virtual void clearVanishEnchantedItemsOnDeath(void);
    virtual void sendInventory(bool);
    virtual float getDamageAfterEnchantReduction(ActorDamageSource const&, float);
    virtual float getDamageAfterArmorReduction(ActorDamageSource const&, float);
    virtual float getDamageAfterResistanceEffect(ActorDamageSource const&, float);
    virtual void createAIGoals(void);
    virtual void onBorn(Actor&, Actor&);
    virtual void setItemSlot(EquipmentSlot, ItemStack const&);
    virtual void setTransitioningSitting(bool);
    virtual void attackAnimation(Actor*, float);
    virtual int getAttackTime(void);
    virtual void _getWalkTargetValue(class BlockPos const&);
    virtual void canExistWhenDisallowMob(void);
    virtual void ascendLadder(void);
    virtual void ascendBlockByJumping(void);
    virtual void descendBlockByCrouching(void);
    virtual void dropContainer(void);
    virtual void initBodyControl(void);
    virtual void jumpFromGround(BlockSource* const&);
    virtual void jumpFromGround(class IMobMovementProxy&, BlockSource* const&);
    virtual void newServerAiStep(void);
    virtual void _serverAiMobStep(void);
    virtual void dropBags(void);
    virtual void tickDeath(void);
    virtual void updateGliding(void);
    virtual void _allowAscendingScaffolding(void);
    virtual void _getAdjustedAABBForSpawnCheck(AABB<float> const&, struct Vec3 const&);
    virtual void prepareRegion(ChunkSource&);
    virtual void destroyRegion(void);
    virtual void suspendRegion(void);
    virtual void resendAllChunks(void);
    virtual void _fireWillChangeDimension(void);
    virtual void _fireDimensionChanged(void);
    virtual void changeDimensionWithCredits(/*AutomaticID<Dimension, int>*/);
    virtual void tickWorld(Tick const&);
private:
    virtual void Function353();
public:
    virtual int getTickingOffsets(void);
    virtual void moveView(void);
    virtual void moveSpawnView(/*struct Vec3 const&, AutomaticID<Dimension, int>*/);
    virtual void setName(std::string const&);
    virtual int getTravelledMethod(void);
    virtual void checkMovementStats(struct Vec3 const&);
    virtual int getCurrentStructureFeature(void);
    virtual bool isAutoJumpEnabled(void);
    virtual void respawn(void);
    virtual void resetRot(void);
    virtual bool isInTrialMode(void);
    virtual void hasResource(int);
    virtual void completeUsingItem(void);
    virtual void startDestroying(void);
    virtual void stopDestroying(void);
    virtual void openPortfolio(void);
    virtual void openBook(int, bool, int, class BlockActor*);
    virtual void openTrading(uint64_t const&, bool);
    virtual void canOpenContainerScreen(void);
    virtual void openChalkboard(class ChalkboardBlockActor&, bool);
    virtual void openNpcInteractScreen(std::shared_ptr<INpcDialogueData>);
    virtual void openInventory(void);
    virtual void displayChatMessage(std::string const&, std::string const&);
    virtual void displayClientMessage(std::string const&);
    virtual void displayTextObjectMessage(class TextObjectRoot const&, std::string const&, std::string const&);
    virtual void displayTextObjectWhisperMessage(ResolvedTextObject const&, std::string const&, std::string const&);
    virtual void displayTextObjectWhisperMessage(std::string const&, std::string const&, std::string const&);
    virtual void displayWhisperMessage(std::string const&, std::string const&, std::string const&, std::string const&);
    virtual void startSleepInBed(BlockPos const&);
    virtual void stopSleepInBed(bool, bool);
    virtual void canStartSleepInBed(void);
    virtual int getSleepTimer(void);
    virtual int getPreviousTickSleepTimer(void);
    virtual void openSign(BlockPos const&, bool);
    virtual void playEmote(std::string const&, bool);
    virtual bool isHostingPlayer(void);
    virtual bool isLoading(void);
    virtual bool isPlayerInitialized(void);
    virtual void stopLoading(void);
    virtual void registerTrackedBoss(uint64_t);
    virtual void unRegisterTrackedBoss(uint64_t);
    virtual void setPlayerGameType(GameType);
    virtual void initHUDContainerManager(void);
    virtual void _crit(Actor&);
    virtual int getEventing(void);
    virtual int getUserId(void);
    virtual void sendEventPacket(EventPacket&);
    virtual void addExperience(int);
    virtual void addLevels(int);
private:
    virtual void Function403();
    virtual void Function404();
public:
    virtual void inventoryChanged(Container&, int, ItemStack const&, ItemStack const&, bool);
private:
    virtual void Function406();
public:
    virtual void deleteContainerManager(void);
    virtual bool isActorRelevant(Actor const&);
private:
    virtual void Function409();
public:
    virtual void onSuspension(void);
    virtual void onLinkedSlotsChanged(void);
    virtual void startCooldown(Item const*, bool);
    virtual int getItemCooldownLeft(HashedString const&);
    virtual int getItemCooldownLeft(int);
    virtual int getMaxItemCooldownLeft(void);
    virtual bool isItemOnCooldown(HashedString const&);
private:
    virtual void Function417();
    virtual void Function418();
public:
    virtual void sendNetworkPacket(Packet&);
private:
    virtual void Function420();
public:
    virtual void reportMovementTelemetry(MovementEventType);
    virtual bool isSimulated(void);
    virtual int getXuid(void);
    virtual int getMovementSettings(void);
    virtual void addSavedChunk(ChunkPos const&);
    virtual int getMaxChunkBuildRadius(void);
    virtual void onMovePlayerPacketNormal(struct Vec3 const&, struct Vec2 const&, float);
    virtual void _createChunkSource(ChunkSource&);
    virtual void setAbilities(LayeredAbilities const&);

public:
    PlayerInventory* getSupplies()
    {
        uintptr_t address = reinterpret_cast<uintptr_t>(this);
        return *reinterpret_cast<PlayerInventory**>(address + 0x848);
    }
    RenderPositionComponent* getRenderPositionComponent() {
        using getRenderPositionComponent = RenderPositionComponent * (__cdecl*)(void*, EntityId*);
        static auto func = reinterpret_cast<getRenderPositionComponent>(findSig(xorstr_("40 53 48 83 EC ? 48 8B DA BA 6E F3 E8 D4")));
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
        return *reinterpret_cast<GameMode**>(address + 0xEF8);
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
        return CallVFunc<342, void>(this);
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

    /*
    
    std::string getNameTag()
    {
        if (!this || IsBadPtr())
            return std::string("");

        if (Game::GetLocalPlayer()->GetPosition().distance(GetPosition()) < 320)
            return std::string("");

        const char* ptr = reinterpret_cast<const char*>(this + 0x1CC0);

        if (ptr == nullptr || reinterpret_cast<uintptr_t>(ptr) >= range_start)
            return std::string("");

        int length = 0;
        std::string result;
        while (*ptr != '\0')
        {
            result += *ptr;
            ptr++;
            length++;

            if (length >= 24)
                return std::string("");
        }
        return result;
    }

    */

    template<typename T>
    T* try_get()
    {
        if (IsBadReadPtr(this, sizeof(Player)))
            return nullptr;

        uintptr_t ptr = (uintptr_t)this + Addresses::actorStateComponent;

        if (ptr >= range_start || ptr <= 0x1000)
            return nullptr;

        if (std::is_same<T, StateVectorComponent>::value)
        {
            return *reinterpret_cast<T**>(ptr);
        }

        if (std::is_same<T, AABBShapeComponent>::value)
        {
            return *reinterpret_cast<T**>(ptr + 8);
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
        return reinterpret_cast<EntityContext*>(address + 8);
    }

    Level* GetLevel()
    {
        uintptr_t address = reinterpret_cast<uintptr_t>(this);
        return *reinterpret_cast<Level**>(address + 0x260);
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

        return (currentPosition.distance(lastPosition)) * (*Game::GetInstance()->getMinecraft()->timer);
    }

    Vector3<float> GetPosition(bool tpReady = true)
    {
        DirectPlayerMovementProxy* proxy = getMovementProxy();

        if (!proxy)
            return { 0,0,0 };

        Vector3<float> pos = proxy->getAABB()->lower;

        if (tpReady)
        {
            pos.x += proxy->getAABBDim().x / 2;
            pos.z += proxy->getAABBDim().x / 2;
        }

        return pos;
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
};

static std::map<__int32, uintptr_t> __o__entitylist = std::map<__int32, uintptr_t>();
static std::map<__int32, uintptr_t> prev___o___entitylist = std::map<__int32, uintptr_t>();
static std::map<__int32, uintptr_t> vprev___o___entitylist = std::map<__int32, uintptr_t>();
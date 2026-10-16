#ifndef DUNGEON_OVL_FA7000_H
#define DUNGEON_OVL_FA7000_H
#include "shared/bank_actor_state.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/tile_object.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_800A9E70_arg0.h"
extern u8 D_80174AD4[];
void func_80047784();
s32 dungeonCompareMonsterNeighborValues();
/* This retail bank used the signed-halfword declaration. */
s16 func_800BCB04();
void func_8009A3D0();
void func_8009A21C();
s32 dungeonCheckEntityRelation();
s16 dungeonGetActorHeightDifference();
s32 dungeonPlaceActorAtDirectionalNeighbor();
s32 dungeonApplyCameraOffsetAndSelectTarget();
s32 dungeonAdvanceStatusTimers();
void dungeonReduceActorFoodMeter();
s32 dungeonBeginReadyActorDirectionalAction();
s32 dungeonGetRoundedFacingAndRoundingFlag();
void * func_8003FD64();
s32 func_8004491C();
s32 func_800A56E0();
void *func_80170880(s16 flags, s16 kind_id, s16 variant, s16 spawn_value);
void dungeonUpdateBankActorMovement(void *entity, void *motion_arg, void *sprite_arg);
void dungeonUpdateBankActorState(void *actor_in, void *context_in, void *sprite_in, void *stats_in);
void dungeonAdvanceBankActorPath();
void dungeonSelectBankActorMovement(Rec_func_800A9E70_arg0 *move_data, void *context, TileObject *position_data, EntityRec *actor_data);
s32 dungeonBeginBankDirectionalEffect(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, SpriteFrameState *sprite, EntityRec *actor);
void dungeonInitializeBankActorAction(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, SpriteFrameState *sprite, EntityRec *entity);
s32 func_80172258(EntityRec *actor, void *primary_context, void *secondary_context, s32 force_move);
void dungeonSelectBankResidentCallback(BankActorState *state, s32 unused, SpriteFrameState *source, EntityRec *target);
void dungeonSelectBankActorCallback(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target);
void dungeonUpdateBankStagedMovement(void *action, void *motion, void *map_actor, void *actor_arg);
void dungeonUpdateBankActorTargetedAction(void *owner_input, EntityRec *motion_input, void *actor_input, EntityRec *object);
void dungeonRestoreBankActorTile(void *action, EntityRec *motion, void *sprite, EntityRec *entity);
void func_80173294(void *effect_data, void *motion_data, void *sprite_data, void *object_data);
void dungeonForwardBankActorCallbackA(void *state, s32 action, SpriteFrameState *source, EntityRec *target);
void dungeonForwardBankActorCallbackB(void *state, s32 action, SpriteFrameState *source, EntityRec *target);
void dungeonRestoreBankActorCallbackA(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target);
void func_8017357C(void *controller, EntityRec *motion, void *sprite, EntityRec *actor);
void dungeonAdvanceBankActorAnimation(void *controller, void *context, void *sprite, void *entity);
void dungeonUpdateBankActorSpriteState(BankActorState *actor, s32 action, SpriteFrameState *sprite, EntityRec *target);
void func_80173E00(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target);
void dungeonRestoreBankActorCallbackB(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target);
void dungeonRestoreBankActorCallbackC(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target);
void dungeonRestoreBankActorCallbackD(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target);
void dungeonUpdateBankEffectFade(void *effect, void *position, void *visual);
void dungeonStartBankActorHitReaction(void *work, void *part_a, void *part_b, EntityRec *actor);
void dungeonUpdateBankTimedEffect(void *state_input, void *motion_input, void *animation_input, void *actor_input);
void func_801745E0(void *state);
#endif

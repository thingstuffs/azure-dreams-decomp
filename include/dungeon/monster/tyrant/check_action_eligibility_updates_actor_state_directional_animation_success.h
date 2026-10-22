#ifndef DUNGEON_OVL_7F0F7800_P04_H
#define DUNGEON_OVL_7F0F7800_P04_H
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_800A9E70_arg0.h"



extern void select_sprite_entry(void *, u8, s32);
extern void func_80047784(void *, u8, s32);
extern void prepare_directional_attack(void *, void *, s16, s32, s32);
extern s32 get_actor_height_difference(s32, void *);
extern s32 probe_directional_neighbor(void *, u8, u8, s16);
extern s32 try_claim_dungeon_action_slot(void *);
extern s32 check_entity_interaction_compatibility(void *, s32);
extern void apply_camera_offset_and_select_target(void *, s32, s32, s32);
extern u8 D_80173FB8[];
s32 check_action_eligibility_updates_actor_state_directional_animation_success(void *action_state, s32 action_id, SpriteFrameState *sprite, ActorRecord *actor);
#endif

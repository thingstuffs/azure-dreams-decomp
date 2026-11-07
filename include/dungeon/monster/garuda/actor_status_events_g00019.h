#ifndef DUNGEON_MONSTER_GARUDA_ACTOR_STATUS_EVENTS_G00019_H
#define DUNGEON_MONSTER_GARUDA_ACTOR_STATUS_EVENTS_G00019_H
#include "dungeon/monster/garuda_frames.h"
/* Actor status events shared declarations (G00019). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00019 - PD:dungeon/bank_1025000:801748E8, PD:dungeon/bank_102b000:8016E8E8, PD:dungeon/bank_1031000:801688E8, PD:dungeon/bank_1037000:801628E8, PD:dungeon/bank_103d000:8015C8E8, PD:dungeon/bank_1043000:801568E8. */

#include "common.h"
#include "dungeon/monster/garuda.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800AA258_arg2.h"

typedef struct S_801734E0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0xA];
    u16 unk_A6;
    u8 pad_A8[0xA];
    u16 unk_B2;
} S_801734E0_0;

/* copy_arg0 in update_actor_status_callback */
extern s32 get_entity_effect_value(ActorRecord *entry, s32 effect_id);
extern void clear_slots_of_type(ActorRecord *owner, s8 match_type);
extern s32 get_tile_chebyshev_distance(void *, void *);
#include "dungeon/player/object/action_state.h"
extern s32 generate_random_value(void);
extern void update_actor_status_and_mp(ActorRecord *entity);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void func_80173834(void *, void *, void *, void *);
extern u8 garuda_frame_set_1[];

typedef struct S_80047784 S_80047784;
struct SpriteFrameState;
extern void select_sprite_entry(void *, s16, s16);
extern u8 garuda_action_resume_address[];

/* Functions defined in this translation unit. */
void update_actor_status_callback(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);

#endif

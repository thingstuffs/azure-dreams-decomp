#ifndef DUNGEON_MONSTER_GARUDA_ACTOR_STATUS_EVENTS_G00019_H
#define DUNGEON_MONSTER_GARUDA_ACTOR_STATUS_EVENTS_G00019_H
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

typedef struct S_801730B4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_801730B4_0;

/* arg0 in update_actor_status_callback */
typedef struct S_801730B4_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_801730B4_1;

/* arg2 in update_actor_status_callback */
typedef struct S_801730B4_2 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_801730B4_2;

/* arg3 in update_actor_status_callback */
typedef struct S_801730B4_5 {
    u8 pad_00[0x92];
    u16 unk_92;
    u8 pad_94[0x12];
    u16 unk_A6;
    u8 pad_A8[0xA];
    u16 unk_B2;
} S_801730B4_5;

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

/* arg0 in advance_entity_directional_events */
typedef struct S_801734E0_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801734E0_2;

/* base in advance_entity_directional_events */
typedef struct S_801734E0_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_801734E0_4;

/* copy_arg0 in update_actor_status_callback */
extern s32 get_entity_effect_value(void *, s32);
extern void clear_slots_of_type(void *, s32);
extern s32 check_entity_relation(void *, void *);
extern s32 get_tile_chebyshev_distance(void *, void *);
#include "dungeon/player/object/action_state.h"
extern s32 generate_random_value(void);
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, u8 *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void func_80173834(void *, void *, void *, void *);
extern u8 garuda_frame_set_2[];
extern u8 garuda_frame_set_1[];

typedef struct S_80047784 S_80047784;
struct SpriteFrameState;
extern void select_sprite_entry(void *, s16, s16);
extern u8 garuda_action_resume_address[];

/* Functions defined in this translation unit. */
void update_actor_status_callback(void *actor_in, void *context_in, SpriteFrameState *sprite_in, void *entity_in);


#endif

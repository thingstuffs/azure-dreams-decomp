#ifndef DUNGEON_MONSTER_DEATH_ACTOR_STATUS_FLAGS_G00165_H
#define DUNGEON_MONSTER_DEATH_ACTOR_STATUS_FLAGS_G00165_H
/* Actor status flags shared declarations (G00165). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00165 - PD:dungeon/bank_be1000:8017468C, PD:dungeon/bank_be7000:8016E68C, PD:dungeon/bank_bed000:8016868C, PD:dungeon/bank_bf3000:8016268C, PD:dungeon/bank_bf9000:8015C68C, PD:dungeon/bank_bff000:8015668C. */

#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800AA258_arg2.h"

typedef struct S_80173CD4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x8];
    union { struct { u32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_A4;   /* overlapping accesses */
    u32 unk_A8;
    u32 unk_AC;
    u32 unk_B0;
    u8 pad_B4[0x4];
    u16 unk_B8;
} S_80173CD4_0;

/* arg0 in advance_actor_action_state_handle_status */
typedef struct S_80173CD4_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_80173CD4_1;

/* arg2 in advance_actor_action_state_handle_status */
typedef struct S_80173CD4_2 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80173CD4_2;

/* arg3 in advance_actor_action_state_handle_status */
typedef struct S_80173CD4_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80173CD4_4;

typedef struct S_8017409C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x8];
    union { struct { u32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_A4;   /* overlapping accesses */
    u32 unk_A8;
    u32 unk_AC;
    u32 unk_B0;
    u8 pad_B4[0x4];
    u16 unk_B8;
} S_8017409C_0;

/* arg0 in advance_actor_states_and_entity_flags */
typedef struct S_8017409C_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8017409C_2;

/* base in advance_actor_states_and_entity_flags */
typedef struct S_8017409C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_8017409C_4;

/* global in advance_actor_action_state_handle_status */
extern s32 get_entity_effect_value(void *, s32);
extern void clear_slots_of_type(void *, s32);
extern void select_sprite_entry(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
extern s16 get_tile_chebyshev_distance(void *, void *);
extern s32 has_pending_actor_or_turn_action(void *);
extern s32 generate_random_value(void);
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, s32);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void func_801743F0(void *, void *, void *, void *);
extern s32 D_801719DC;
extern u8 D_80174684[];
extern u8 D_8017468C[];

/* Functions defined in this translation unit. */
void advance_actor_action_state_handle_status(void *action_in, void *context_in, void *sprite_in, void *actor_in);
void advance_actor_states_and_entity_flags(void *actor, void *context, void *animation, void *entity);

#endif

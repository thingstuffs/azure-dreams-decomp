#ifndef DUNGEON_MONSTER_CYCLONE_FACE_TARGET_AND_START_ACTION_G00250_H
#define DUNGEON_MONSTER_CYCLONE_FACE_TARGET_AND_START_ACTION_G00250_H

struct ObjectPosition;
/* Face target and start action. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00250 - CL:dungeon/func_80E0EC38@dungeon/bank_e2d000, CL:dungeon/func_80E0EC38@dungeon/bank_e33000, CL:dungeon/func_80E0EC38@dungeon/bank_e39000, CL:dungeon/func_80E0EC38@dungeon/bank_e3f000, CL:dungeon/func_80E0EC38@dungeon/bank_e45000, CL:dungeon/func_80E0EC38@dungeon/bank_e4b000, CL:dungeon/func_80E0EF2C@dungeon/bank_e2d000, CL:dungeon/func_80E0EF2C@dungeon/bank_e33000 (+4 more). */

#include "common.h"
#include "dungeon/monster/cyclone.h"
#include "shared/dungeon_image_buffer.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"
#include "shared/sprite_frame_state.h"

#define D_801764A0_OFF 0x2C4A0

typedef struct S_801722E4_5_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801722E4_5_pre;

typedef struct S_801722E4_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_801722E4_1;

/* arg2 in face_target_and_start_action */
typedef struct S_801722E4_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801722E4_2;

typedef struct S_801722E4_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_801722E4_3;

typedef struct S_80172438_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172438_1;

/* arg2 in search_ahead_and_start_action */
typedef struct S_80172438_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x16];
    u16 unk_B2;
} S_80172438_2;

/* extern */
typedef struct S_8017283C_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_8017283C_1;

/* extern */
typedef struct S_8017294C_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_8017294C_1;

extern s16 get_rounded_facing_and_rounding_flag();
extern s32 select_nearby_target_and_initialize_slot(s32 slot_id,struct ObjectPosition *target, s32 target_id, s32 slot_value);
extern u8 cyclone_frame_set_2[];
/* arg0 in search_ahead_and_start_action */
extern s32 check_layer_offset_height(s32, s32, s16, s32);
extern s16 sample_terrain_surface_height(u16, u16, s16);
extern s32 find_eligible_entry_at_coordinates(void *, u16, u16);
extern s32 check_entity_interaction_compatibility(void *, void *);


/* Shared import declarations; data casts preserve each measured view. */
extern void select_sprite_entry(void *, u8, s32);
extern s32 try_claim_dungeon_action_slot(void *);
extern void advance_status_timers(void *);
extern void apply_camera_offset_and_select_target(void *, void *, s32, s32);

/* Functions defined in this translation unit. */
void face_target_and_start_action(S_801722E4_3 *action_state, s32 event_context, SpriteFrameState *sprite, ActorRecord *actor);
s32 search_ahead_and_start_action(void *action_state, void *action_context, SpriteFrameState *sprite, ActorRecord *actor);
void update_action_state_direction_specific(void *action_state, s32 action_param, SpriteFrameState *sprite, void *actor);
void clear_actor_action_flag_and_animate(S_8017283C_1 *action_state, s32 action_context, SpriteFrameState *animation, ActorRecord *actor);


#endif

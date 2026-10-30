#ifndef DUNGEON_ACTOR_MOVEMENT_PATH_G00371_H
#define DUNGEON_ACTOR_MOVEMENT_PATH_G00371_H
/* Movement path shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800D38EC, CL:dungeon/func_800D3B60, CL:dungeon/func_800D40C0, PD:dungeon/engine:800E260C. */

#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "records/Rec_D_80082E80.h"
#include "shared/actor_status.h"
#include "shared/record_ptrs.h"
#include "shared/sprite_frame_state.h"

typedef void (*Callback)();

typedef struct S_func_800D8728_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[3];
    u8 unk_71;
    u8 pad_72[0x16];
    union {
        s16 s16;
        u16 u16;
    } unk_88;
    u8 pad_8A[2];
    Callback unk_8C;
    union {
        s32 s32;
        struct {
            u8 pad_90[2];
            union {
                s16 s16;
                u16 u16;
            } unk_92;
        } half;
    } unk_90;
    s16 unk_94;
    u8 pad_96[2];
    u16 unk_98;
    u8 unk_9A;
    u8 pad_9B[2];
    u8 unk_9D;
    u8 pad_9E[2];
    union {
        s16 s16;
        u16 u16;
    } unk_A0;
} S_func_800D8728_0;

typedef struct S_func_800D8728_1 {
    union {
        s32 s32;
        struct {
            u8 pad_00[2];
            u16 unk_02;
        } half;
    } unk_00;
    union {
        s32 s32;
        struct {
            u8 pad_04[2];
            u16 unk_06;
        } half;
    } unk_04;
    u8 pad_08[2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_func_800D8728_1;

typedef struct S_func_800D8728_2 {
    u8 pad_00[4];
    s8 unk_04;
    u8 pad_05[0xD];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[6];
    u8 *unk_2C;
} S_func_800D8728_2;

typedef struct S_800D904C_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    s16 unk_8A;
} S_800D904C_0;

/* state in advance_actor_queued_path */
/* entry in advance_actor_queued_path */
typedef struct S_800D904C_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
} S_800D904C_3;

typedef struct S_800D92C0_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x19];
    u8 unk_45;
    u16 unk_46;
    u8 pad_48[0x25];
    union { u8 u; s8 s; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x3];
    s8 unk_71;
    u8 pad_72[0x16];
    u16 unk_88;
} S_800D92C0_0;

/* arg3 in advance_actor_traversable_heading */
typedef struct S_800D92C0_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x2C];
    s32 unk_58;
} S_800D92C0_1;

/* *D_800814A8 in advance_actor_traversable_heading */
typedef struct S_800D92C0_2 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    s8 unk_26;
} S_800D92C0_2;

/* arg2 in advance_actor_traversable_heading */
/* (arg3 + ((u8) ((S_800D92C0_0 *)arg3)->unk_71 & 0x7F)) in advance_actor_traversable_heading */
typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonEntry;

extern void advance_sprite_animation_and_textures(void *entity);
extern s32 rand(void);
extern s32 refresh_actor_facing_and_lifecycle();
extern s32 try_move_actor_to_valid_position(void *action, void *context, void *position, void *entity);
extern u8 actor_action_resume_address;
extern u8 actor_movement_frames[];
extern Callback actor_contact_callbacks[];
extern s32 find_active_rect_containing_point(s32, s32);
extern s32 can_entity_gain_level(void *);

extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);

extern void *actor_action_frames[];
/* Load-bearing second view of D_80082E80: the asm label gives cc1 a distinct SYMBOL_REF ("*D_80082E80") so cse
 * does not share the base register with the plain D_80082E80 uses (retail rebuilds the address after the calls). */
extern TileObject D_80082E80_initial __asm__("D_80082E80");
extern s16 actor_turn_angle_offsets[];
s32 check_entity_relation();
s32 update_actor_proximity_flag(void *source, void *state, s32 lower_limit, s32 upper_limit, s8 *result);
s32 generate_random_value(void);

struct Dst; struct Elem;
extern void select_record_entry_and_value(void *state, void *entries, short index);
extern s16 sample_terrain_surface_height(s32, s32, s16);
extern void update_actor_status_and_mp(ActorRecord *);
extern void cycle_map_cell_flags(s16, s16, u16);
extern void update_map_cell_flags_with_item_limit(s32, s32, u16);
extern s32 check_movement_clearance_and_height(u32, void *, void *, s16);

/* Functions defined in this translation unit. */
void update_actor_movement_and_contact(S_func_800D8728_0 *entity, S_func_800D8728_1 *motion, SpriteFrameState *monster);
void advance_actor_queued_path(void *action, s32 action_id, void *actor, void *move_state);
void advance_actor_traversable_heading(void *move_state, void *context, S_800D92C0_2 *position, void *actor);


#endif

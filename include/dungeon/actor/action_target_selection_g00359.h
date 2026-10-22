#ifndef DUNGEON_ACTOR_ACTION_TARGET_SELECTION_G00359_H
#define DUNGEON_ACTOR_ACTION_TARGET_SELECTION_G00359_H
/* Action target selection shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800C4A80, CL:dungeon/func_800C4CE4, CL:dungeon/func_800C5028, CL:dungeon/func_800C51DC, CL:dungeon/func_800C5334. */

#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/actor_status.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_links.h"

typedef struct S_800CA1E0_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    u16 unk_88;
} S_800CA1E0_2;

typedef struct S_800CA444_0 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    s8 unk_26;
} S_800CA444_0;

/* arg2 in update_actor_targeting_for_tile */
typedef struct S_800CA444_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    union { u8 u; s8 s; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x16];
    u16 unk_88;
} S_800CA444_1;

/* arg3 in update_actor_targeting_for_tile */
typedef struct S_800CA444_2 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    s8 unk_9C;
} S_800CA444_2;

/* arg0 in update_actor_targeting_for_tile */
typedef struct S_800CA444_3 {
    s16 unk_00;
} S_800CA444_3;

typedef struct S_800CA444_4 {
    u8 pad_00[0x58];
    s32 unk_58;
} S_800CA444_4;

/* *D_800814A8 in update_actor_targeting_for_tile */
/* (arg3 + (((S_800CA444_1 *)arg3)->unk_71 & 0x7F)) in update_actor_targeting_for_tile */
typedef struct {
    u8 pad_00[0xC];
    u16 flags;
    u8 pad_0E[6];
} DungeonTableEntry;

typedef struct S_800CA788_0 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800CA788_0;

/* global_base in select_target_tile_for_actor_action */
typedef struct S_800CA788_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_800CA788_1;

/* actor in select_target_tile_for_actor_action */
/* held_arg2 in select_target_tile_for_actor_action */
typedef struct S_800CA788_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
} S_800CA788_3;

typedef struct S_800CA93C_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
} S_800CA93C_0;

/* object in get_adjacent_tile_for_action */
extern u16 direction_x_offsets[];
extern u16 direction_y_offsets[];
s16 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);
s32 check_diagonal_side_height(s32 direction, s16 tile_x, s16 tile_y, s16 height);
s32 find_active_rect_containing_point(s32 point_x, s32 point_y);
extern s16 actor_turn_angle_offsets[];
s32 select_actor_route_target();
s32 update_actor_proximity_flag();
void update_actor_status_and_mp();
s32 check_entity_relation();
/* object in select_target_tile_for_actor_action */
extern s32 find_eligible_entry_at_coordinates(u8 *entry, s16 x, s16 y);
extern void prepare_directional_attack(void *, void *, s32, s32, s32);
extern s32 get_actor_height_difference(s32, void *);
extern s32 try_claim_dungeon_action_slot(void *);
extern void apply_camera_offset_and_select_target(void *, void *, s32, s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void *choose_best_eligible_entry();

extern s16 sample_terrain_surface_height(s32 x, s32 y, s16 min_height);

/* Functions defined in this translation unit. */
s32 get_adjacent_tile_for_action(u32 action_flags, EntityRec *position, S_800CA1E0_2 *object, u16 height_offset);
void update_actor_targeting_for_tile(void *motion, s32 unused, S_800CA444_0 *tile, void *actor);
s32 select_target_tile_for_actor_action(void *object_ptr, void *action_context, void *target_ptr, void *actor_ptr);

#endif

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


/* state in advance_actor_queued_path */

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
extern u8 actor_action_resume_address;
extern u8 actor_movement_frames[];
extern Callback actor_contact_callbacks[];
extern s32 find_active_rect_containing_point(s32, s32);


extern void *actor_action_frames[];
/* Load-bearing second view of D_80082E80: the asm label gives cc1 a distinct SYMBOL_REF ("*D_80082E80") so cse
 * does not share the base register with the plain D_80082E80 uses (retail rebuilds the address after the calls). */
extern TileObject D_80082E80_initial __asm__("D_80082E80");
extern s16 actor_turn_angle_offsets[];
s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
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
void update_actor_movement_and_contact(S_func_800D8728_0 *entity, ObjectPosition *motion, SpriteFrameState *monster);
void advance_actor_queued_path(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
void advance_actor_traversable_heading(ActorRecord *body, ObjectPosition *context, S_800D92C0_2 *position, ActorRecord *actor);

#endif

#ifndef DUNGEON_MONSTER_MANOEVA_KNOCKBACK_TRAVEL_G00260_H
#define DUNGEON_MONSTER_MANOEVA_KNOCKBACK_TRAVEL_G00260_H
#include "dungeon/level.h"
#include "shared/entity.h"
#include "engine/node/allocation.h"
#include "shared/object_node.h"
#include "engine/node.h"

struct ObjectPosition;
/* Knockback travel shared declarations (G00260). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00260 - CL:dungeon/func_80E3B86C@dungeon/bank_e56c58, CL:dungeon/func_80E3B86C@dungeon/bank_e5d000, CL:dungeon/func_80E3B86C@dungeon/bank_e63000, CL:dungeon/func_80E3B86C@dungeon/bank_e69000, CL:dungeon/func_80E3B86C@dungeon/bank_e6f000, CL:dungeon/func_80E3B86C@dungeon/bank_e75000. */

#include "common.h"
#include "shared/dir_step.h"
#include "shared/sprite_frame_state.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;









typedef struct {
    u8 pad0[0xC];
    u32 color;
    u8 pad10[2];
    u16 f12;
    u8 pad14[8];
    s16 f1C;
    s16 f1E;
    u8 pad20[8];
    s32 f28;
} Display;

typedef struct {
    s16 *facing;
    u8 pad04[8];
    ObjectNodeHeader *actor_node;
    ActorRecord *context;
    SpriteFrameState *source;
    struct ObjectPosition *position;
    u8 pad1C[4];
    s16 f20;
    u8 pad22[0x10];
    s16 x;
    s16 y;
    u16 hit;
    u16 flags;
    u16 source_id;
    u16 owner_byte;
} Work;

typedef struct {
    ObjectNodeHeader node;
    Work work;
} Object;

extern s32 *manoeva_knockback_callback_address;
extern s8 D_801766F0[];
extern u8 *find_or_retain_sprite_resource_slot(s32, s32);

extern void project_vector_by_view_angle(Vec3s *, Vec3s *);
extern void select_sprite_entry(void *, s32, s32);


/* Functions defined in this translation unit. */
s32 check_adjacent_tile_height(s16 tile_x, s16 tile_y, s32 height, s16 direction, s16 *sample_out);
void create_knockback_travel_object(ActorRecord *owner_data,struct ObjectPosition *position_arg, SpriteFrameState *source_arg, ActorRecord *context_arg);

#endif

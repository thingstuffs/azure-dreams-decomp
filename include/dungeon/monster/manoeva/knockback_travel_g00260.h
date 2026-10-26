#ifndef DUNGEON_MONSTER_MANOEVA_KNOCKBACK_TRAVEL_G00260_H
#define DUNGEON_MONSTER_MANOEVA_KNOCKBACK_TRAVEL_G00260_H
#include "dungeon/level.h"

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
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    s16 z;
} Position;

typedef struct {
    u8 pad0[0x12];
    u16 f12;
    u8 pad14[0x10];
    u8 x;
    u8 y;
    u8 pad26[2];
    s32 f28;
} Source;

typedef struct {
    u8 pad0[0x13];
    u8 f13;
    u16 f14;
    u8 pad16[0x14];
    s16 f2A;
    u8 pad2C[0x34];
    void *f60;
} Context;

typedef struct {
    u8 pad0[8];
    Position *position;
    void *display;
    void *callback;
    void *data;
    u8 pad14[8];
    void *field20;
    u8 pad24[4];
} Object;

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
    u8 pad0[0xC];
    void *owner_minus20;
    Context *context;
    Source *source;
    Position *position;
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

extern s32 get_offset_map_cell_value_and_flags(s16, s16, s16, u16 *);
extern s32 *manoeva_knockback_callback_address;
extern s8 D_801766F0[];
extern u8 *find_or_retain_sprite_resource_slot(s32, s32);
extern void *allocate_list_node(s32, void *);
extern void project_vector_by_view_angle(Vec3s *, Vec3s *);
extern void select_sprite_entry(void *, s32, s32);
extern void register_node(Object *, void *);

/* Functions defined in this translation unit. */
s32 check_adjacent_tile_height(s16 tile_x, s16 tile_y, s32 height, s16 direction, s16 *sample_out);
void create_knockback_travel_object(u8 *owner_data,struct ObjectPosition *position_arg, Source *source_arg, Context *context_arg);

#endif

#ifndef DUNGEON_OVL_C4709C_H
#define DUNGEON_OVL_C4709C_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"
#include "shared/entity.h"

typedef unsigned long uptr;

   /* object in func_8015E89C */

typedef struct S_8015E89C_2 {
    u8 pad_00[0x8];
    union { struct { void * v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    void * unk_0C;
} S_8015E89C_2;   /* (void *)temp_t0 in func_8015E89C */

typedef struct S_8015E89C_5 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_8015E89C_5;   /* outer in func_8015E89C */

typedef struct S_8015E89C_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
    s16 unk_06;
    u8 pad_08[0x90];
    void * unk_98;
} S_8015E89C_6;   /* entry in func_8015E89C */

   /* item in func_8015E89C */

typedef struct S_8015E89C_8 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_8015E89C_8;   /* outer_base in func_8015E89C */

extern s32 generate_random_value(void);
extern void select_sprite_entry(void *, s32, s32);
extern void func_80047784(void *, s32, s32);
extern void texture_set_the_active_entries_matching_id_in_type_n_2_table_slots(void *, void *, s32);

#include "slus/view_facing_angle.h"
extern u8 child_texture_entries[];
extern u8 child_object_update_address[];
extern u8 D_8015EBB8[];
extern u8 D_8015F3A8[];
extern u8 D_80162494[];
extern u8 D_801624FC[];

/* Allocates and initializes an object and its child display items. */

void *create_actor_child_display_b(s32 kind, s32 part_x, s32 part_y, s32 initial_value);
#endif

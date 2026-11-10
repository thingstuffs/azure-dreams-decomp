#ifndef DUNGEON_OVL_C3B09C_H
#define DUNGEON_OVL_C3B09C_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"
#include "shared/entity.h"

typedef unsigned long uptr;

   /* object in func_8016A89C */

typedef struct S_8016A89C_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
    s16 unk_06;
    u8 pad_08[0x90];
    void * unk_98;
} S_8016A89C_6;   /* entry in func_8016A89C */

   /* item in func_8016A89C */

typedef struct S_8016A89C_8 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_8016A89C_8;   /* outer_base in func_8016A89C */

extern s32 generate_random_value(void);
extern void select_sprite_entry(void *, s32, s32);
extern void func_80047784(void *, s32, s32);
extern void texture_set_the_active_entries_matching_id_in_type_n_2_table_slots(void *, void *, s32);

extern s16 view_facing_angle_alias;
extern u8 child_texture_entries[];
extern u8 child_object_update_address[];
extern u8 D_8016ABB8[];
extern u8 D_8016B3A8[];
extern u8 D_8016E494[];
extern u8 D_8016E4FC[];

/* Allocates and initializes an object and its child display items. */

void *allocate_object_and_child_display_items(s32 kind, s32 part_x, s32 part_y, s32 copy_value);
#endif

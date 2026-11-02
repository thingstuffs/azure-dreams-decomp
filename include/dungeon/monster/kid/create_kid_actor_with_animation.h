#ifndef DUNGEON_OVL_A130DC_H
#define DUNGEON_OVL_A130DC_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"
#include "shared/entity.h"

typedef unsigned long uptr;

typedef struct S_801708DC_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_801708DC_1;   /* object in func_801708DC */




typedef struct S_801708DC_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
    s16 unk_06;
    u8 pad_08[0x90];
    void * unk_98;
} S_801708DC_6;   /* entry in func_801708DC */

typedef struct S_801708DC_7 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x16];
    s32 unk_28;
} S_801708DC_7;   /* item in func_801708DC */

typedef struct S_801708DC_8 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_801708DC_8;   /* outer_base in func_801708DC */

extern void *func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
extern s32 register_node(ObjectNodeHeader *entry, void *registration_id);
extern s32 func_8004491C(ObjectNodeHeader *entry, void *registration_id);
extern s32 generate_random_value(void);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern void select_sprite_entry(void *, s32, s32);
extern void func_80047784(void *, s32, s32);
extern void texture_set_the_active_entries_matching_id_in_type_n_2_table_slots(void *, void *, s32);

extern s16 view_facing_angle_alias;
extern u8 child_texture_entries[];
extern u8 child_object_update_address[];
extern u8 D_80170BF8[];
extern u8 kid_action_resume_address[];
extern u8 kid_direction_frames[];
extern u8 kid_alt_spawn_direction_frames[];

/* Allocate and initialize an object and its child entries. */

void *create_actor_with_child_sprites(s32 kind, s32 part_x, s32 part_y, s32 copy_value);
#endif

#ifndef DUNGEON_OVL_A190DC_H
#define DUNGEON_OVL_A190DC_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"
#include "shared/entity.h"

typedef unsigned long uptr;

   /* object in func_8016A8DC */

typedef struct S_8016A8DC_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
    s16 unk_06;
    u8 pad_08[0x90];
    void * unk_98;
} S_8016A8DC_6;   /* entry in func_8016A8DC */

   /* item in func_8016A8DC */

typedef struct S_8016A8DC_8 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_8016A8DC_8;   /* outer_base in func_8016A8DC */

extern void *func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
extern s32 register_node(ObjectNodeHeader *entry, void *registration_id);
extern s32 func_8004491C(ObjectNodeHeader *entry, void *registration_id);
extern s32 generate_random_value(void);
extern s32 try_move_actor_to_valid_position(void *, void *, void *, void *);
extern void select_sprite_entry(void *, s32, s32);
extern void func_80047784(void *, s32, s32);
extern void texture_set_the_active_entries_matching_id_in_type_n_2_table_slots(void *, void *, s32);

extern s16 view_facing_angle_alias;
extern u8 child_texture_entries[];
extern u8 child_object_update_address[];
extern u8 D_8016ABF8[];
extern u8 D_8016B400[];
extern u8 D_8016F140[];
extern u8 D_8016F188[];

/* Allocate and initialize an object and its child rendering data. */

void *allocate_object_with_child_render_data(s32 kind, s32 part_x, s32 part_y, s32 copy_value);
#endif

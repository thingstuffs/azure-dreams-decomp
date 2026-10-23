#ifndef DUNGEON_OVL_C4D09C_H
#define DUNGEON_OVL_C4D09C_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef unsigned long uptr;

typedef struct S_8015889C_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_8015889C_1;   /* object in func_8015889C */

typedef struct S_8015889C_2 {
    u8 pad_00[0x8];
    union { struct { void * v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    void * unk_0C;
} S_8015889C_2;   /* (void *)temp_t0 in func_8015889C */

typedef struct S_8015889C_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x1];
    s16 unk_9E;
    u8 pad_A0[0x8];
    s16 unk_A8;
} S_8015889C_4;   /* stable_object in func_8015889C */

typedef struct S_8015889C_5 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_8015889C_5;   /* outer in func_8015889C */

typedef struct S_8015889C_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
    s16 unk_06;
    u8 pad_08[0x90];
    void * unk_98;
} S_8015889C_6;   /* entry in func_8015889C */

typedef struct S_8015889C_7 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x16];
    s32 unk_28;
} S_8015889C_7;   /* item in func_8015889C */

typedef struct S_8015889C_8 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_8015889C_8;   /* outer_base in func_8015889C */

extern void *allocate_list_node(s32, void *);
extern void *func_8003FD64(s32, void *);
extern void register_node(void *, void *);
extern void func_8004491C(void *, void *);
extern s32 generate_random_value();
extern void set_or_clear_actor_status_slot(void *, s32, s32);
extern void initialize_actor_sprite_and_animation(void *, void *, void *, s16);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern void select_sprite_entry(void *, s32, s32);
extern void func_80047784(void *, s32, s32);
extern void texture_set_the_active_entries_matching_id_in_type_n_2_table_slots(void *, void *, s32);

extern s16 view_facing_angle_alias;
extern u8 child_texture_entries[];
extern u8 child_object_update_address[];
extern u8 D_80158BB8[];
extern u8 D_801593A8[];
extern u8 D_8015C494[];
extern u8 D_8015C4FC[];

/* Allocates and initializes an object and its child display items. */

void *allocate_object_with_child_displays(s32 kind, s32 part_value_24, s32 part_value_25, s32 copy_value);
#endif

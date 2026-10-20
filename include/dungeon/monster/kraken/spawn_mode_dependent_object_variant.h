#ifndef DUNGEON_OVL_EED06C_H
#define DUNGEON_OVL_EED06C_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_8015886C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8015886C_0;   /* obj in func_8015886C */

typedef struct S_8015886C_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8015886C_1;   /* work in func_8015886C */

typedef struct S_8015886C_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8015886C_2;   /* part_a in func_8015886C */

typedef struct S_8015886C_4 {
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
    u16 unk_A8;
} S_8015886C_4;   /* actor in func_8015886C */

typedef struct S_8015886C_5 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_8015886C_5;   /* current in func_8015886C */

typedef struct S_8015886C_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u8 pad_08[0x90];
    u32 unk_98;
} S_8015886C_6;   /* child in func_8015886C */

typedef struct S_8015886C_7 {
    u8 pad_00[0xC];
    u32 unk_0C;
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x12];
    u32 unk_28;
} S_8015886C_7;   /* elem in func_8015886C */

typedef struct S_8015886C_8 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_8015886C_8;   /* base in func_8015886C */

typedef struct S_8015886C_9 {
    u8 pad_00[0x10];
    void * unk_10;
} S_8015886C_9;   /* ((S_8015886C_8 *)base)->unk_A4 in func_8015886C */

extern void *allocate_list_node();
extern void *func_8003FD64();
extern void register_node();
extern void func_8004491C();
extern s32 generate_random_value();
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern void select_sprite_entry();
extern void func_80047784();
extern void texture_set_the_active_entries_matching_id_in_type_n_2_table_slots();
extern void try_move_actor_to_valid_position();

extern void process_effect_block_entries();
extern void func_80158B64();
extern void func_801591A4();
extern u8 D_8015C18C[];
extern u8 D_8015C1CC[];

void * spawn_mode_dependent_112_object_variant(s16 spawn_flags, s16 kind_id, s16 variant, s16 spawn_value);
extern void * draw_sprite_effect_quads();
#endif

#ifndef DUNGEON_OVL_7F23B800_H
#define DUNGEON_OVL_7F23B800_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef s32 M2C_UNK;

typedef struct S_8016A854_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8016A854_1;   /* work in func_8016A854 */

typedef struct S_8016A854_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8016A854_2;   /* part_a in func_8016A854 */

typedef struct S_8016A854_3 {
    u8 pad_00[0x10];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8016A854_3;   /* part_b in func_8016A854 */

typedef struct S_8016A854_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x7];
    s16 unk_A4;
    s16 unk_A6;
} S_8016A854_4;   /* work_copy in func_8016A854 */

extern void func_8016AA8C();
extern u8 D_8016DD30[];
extern u8 D_8016DD78[];
extern void func_8016AF74();

extern void *allocate_list_node();
extern void *func_8003FD64();
extern s32 register_node();
extern s32 func_8004491C();
extern s32 generate_random_value();
extern s16 set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern s32 try_move_actor_to_valid_position();
extern void unlink_node();
extern void func_80044A50();
extern void retire_tracked_effect_by_id();

void * create_mode_configured_actor_object(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c);
#endif

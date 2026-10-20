#ifndef DUNGEON_OVL_F95070_H
#define DUNGEON_OVL_F95070_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"


typedef s32 M2C_UNK;

typedef struct S_80158870_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80158870_0;   /* obj in func_80158870 */

typedef struct S_80158870_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80158870_1;   /* work in func_80158870 */

typedef struct S_80158870_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80158870_2;   /* part_a in func_80158870 */

typedef struct S_80158870_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80158870_3;   /* part_b in func_80158870 */

typedef struct S_80158870_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80158870_4;   /* actor in func_80158870 */


extern void *allocate_list_node();
extern void *func_8003FD64();
extern void register_node();
extern void func_8004491C();
extern s32 generate_random_value();
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();
extern void func_80158A3C();
extern void dispatch_ability_action();
extern u8 D_8015C194[];
extern u8 D_8015C1DC[];

void * create_kind_actor(s16 kind_flags, s16 part_value_24, s16 part_value_25, s16 part_value_0a);
#endif

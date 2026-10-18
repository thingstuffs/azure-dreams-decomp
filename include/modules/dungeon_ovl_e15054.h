#ifndef DUNGEON_OVL_E15054_H
#define DUNGEON_OVL_E15054_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"


typedef s32 M2C_UNK;

typedef struct S_8015E854_0 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x6C];
    void * unk_8C;
} S_8015E854_0;   /* work in func_8015E854 */

typedef struct S_8015E854_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8015E854_1;   /* obj in func_8015E854 */

typedef struct S_8015E854_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8015E854_2;   /* part_a in func_8015E854 */

typedef struct S_8015E854_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8015E854_3;   /* part_b in func_8015E854 */

typedef struct S_8015E854_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8015E854_4;   /* actor in func_8015E854 */


extern void func_8015EA58();
extern void func_8015EE5C();
extern u8 D_80162510[];
extern u8 D_80162538[];

extern void *func_8003FD64();
extern s32 func_8004491C();
extern s32 generate_random_value();
extern s16 set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern s32 try_move_actor_to_valid_position();

void * create_tracked_effect_object(s16 flags, s16 kind_id, s16 variant, s16 spawn_value);
#endif

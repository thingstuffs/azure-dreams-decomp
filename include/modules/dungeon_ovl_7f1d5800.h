#ifndef DUNGEON_OVL_7F1D5800_H
#define DUNGEON_OVL_7F1D5800_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef s32 M2C_UNK;

typedef struct S_8014C894_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8014C894_0;   /* obj in func_8014C894 */

typedef struct S_8014C894_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8014C894_1;   /* work in func_8014C894 */

typedef struct S_8014C894_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8014C894_2;   /* part_a in func_8014C894 */

typedef struct S_8014C894_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8014C894_4;   /* actor in func_8014C894 */

extern void *allocate_list_node();
extern void *func_8003FD64();
extern void register_node();
extern void func_8004491C();
extern s32 generate_random_value();
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();
extern void func_8014CA68();
extern void func_8014CE94();
extern u8 D_80150A7C[];
extern u8 D_80150AD4[];

void * func_8014C894(s16 flags, s16 kind_id, s16 variant, s16 spawn_value);
#endif

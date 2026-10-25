#ifndef DUNGEON_OVL_FA1070_H
#define DUNGEON_OVL_FA1070_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/sprite_frame_state.h"
struct R03_80170A28_S_80170A28_2;

typedef s32 M2C_UNK;

typedef struct S_8014C870_1 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_8014C870_1;   /* work in func_8014C870 */

typedef struct S_8014C870_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8014C870_2;   /* part_a in func_8014C870 */

typedef struct S_8014C870_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8014C870_4;   /* actor in func_8014C870 */

typedef struct Work {
    u8 pad14[0x14];
    s32 flags14;
    u8 pad18[4];
    s32 flags1c;
} Work;

extern void *allocate_list_node(s32, void *);
extern void *func_8003FD64(s32, void *);
extern void register_node(void *, void *);
extern void func_8004491C(void *, void *);
extern s32 generate_random_value(void);
extern void set_or_clear_actor_status_slot(void *, s32, s32);
extern void initialize_actor_sprite_and_animation(void *, void *, void *, s16);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern void func_8014CA3C(void *entity, struct R03_80170A28_S_80170A28_2 *motion, void *part);
extern void dispatch_dungeon_actor_behavior_and_facing(void *actor_in, void *actor_data_in, SpriteFrameState *sprite_in, void *status_in);
extern u8 D_80150194[];
extern u8 D_801501DC[];

void * create_actor_with_kind_parts(s16 kind_flags, s16 grid_x, s16 grid_y, s16 part_value);
#endif

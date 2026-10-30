#ifndef DUNGEON_OVL_7F217800_H
#define DUNGEON_OVL_7F217800_H
#include "common.h"
#include "engine/node.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
struct ObjectNodeHeader;
struct ObjectNodeHeader;



typedef struct S_80158854_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80158854_1;   /* result in func_80158854 */

typedef struct S_80158854_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80158854_2;   /* part0 in func_80158854 */

typedef struct S_80158854_3 {
    u8 pad_00[0x10];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80158854_3;   /* part1 in func_80158854 */

typedef struct S_80158854_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x7];
    s16 unk_A4;
    s16 unk_A6;
} S_80158854_4;   /* actor in func_80158854 */

extern void func_80158A8C(void *entity_state, void *entity_motion, SpriteFrameState *entity_part);
extern u8 D_8015BD30[];
extern u8 D_8015BD78[];
extern void func_80158F74(void *actor_in, void *actor_data_in, SpriteFrameState *sprite_in, void *status_in);

extern void *allocate_list_node(s32 flags, ObjectNodeHeader **list_head);
extern void *func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
extern s32 func_8004491C(struct ObjectNodeHeader *entry, void *registration_id);
extern s32 generate_random_value(); /* Unprototyped: zero or one ignored argument; retail overwrites a0. */
extern s16 set_or_clear_actor_status_slot();
extern void unlink_node(struct ObjectNodeHeader *node);
extern void func_80044A50(struct ObjectNodeHeader *node);

void * func_80158854(s16 flags, s16 kind_id, s16 variant, s16 spawn_value);
#endif

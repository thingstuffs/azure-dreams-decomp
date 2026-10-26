#ifndef DUNGEON_OVL_E15054_H
#define DUNGEON_OVL_E15054_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "dungeon/actor/status.h"
struct RegistrationNode;
struct S_80170A98_2;

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

extern void func_8015EA58(void *entity, struct S_80170A98_2 *motion, SpriteFrameState *monster);
extern void func_8015EE5C(void *actor_in, void *context_in, void *sprite_in, void *status_in);
extern u8 volcano_frame_set_4[];
extern u8 D_80162538[];

extern void *allocate_list_node();
extern void *func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 func_8004491C(struct RegistrationNode *entry, void *registration_id);
extern s32 generate_random_value(); /* Unprototyped: zero or one ignored argument; retail overwrites a0. */

void * create_tracked_effect_object(s16 flags, s16 kind_id, s16 variant, s16 spawn_value);
#endif

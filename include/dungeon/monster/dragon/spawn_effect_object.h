#ifndef DUNGEON_OVL_A0D054_H
#define DUNGEON_OVL_A0D054_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"
#include "dungeon/actor/status.h"
#include "engine/node.h"
struct ObjectNodeHeader;

typedef s32 M2C_UNK;

   /* work in func_8014C854 */

   /* part_a in func_8014C854 */

   /* part_b in func_8014C854 */

typedef struct S_8014C854_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8014C854_4;   /* actor in func_8014C854 */

extern void *func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
extern s32 func_8004491C(struct ObjectNodeHeader *entry, void *registration_id);
extern s32 generate_random_value(void);
extern u8 D_8014CA28[];
extern u8 dragon_slot_a_action_callback;
extern u8 D_8014FC7C[];
extern u8 D_8014FCDC[];

/* Create an actor and initialize its parts, placement, and kind flags. */

void *spawn_effect_object(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 part_id);
#endif

#ifndef DUNGEON_OVL_9FB054_H
#define DUNGEON_OVL_9FB054_H
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

   /* work in func_8015E854 */

   /* part_a in func_8015E854 */

   /* part_b in func_8015E854 */

typedef struct S_8015E854_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8015E854_4;   /* actor in func_8015E854 */

extern s32 generate_random_value(void);
extern u8 D_8015EA28[];
extern u8 dragon_slot_d_action_callback;
extern u8 D_80161C7C[];
extern u8 D_80161CDC[];

/* Creates an actor, configures its parts and flags, and returns its work data. */

void *create_tracked_effect_object(s16 flags, s16 x, s16 y, s16 part_id);
#endif

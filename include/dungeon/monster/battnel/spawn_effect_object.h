#ifndef DUNGEON_OVL_BB1054_H
#define DUNGEON_OVL_BB1054_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"
#include "engine/node.h"
#include "dungeon/actor/status.h"
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
    u8 pad_9D[0x7];
    s16 unk_A4;
} S_8014C854_4;   /* actor in func_8014C854 */

extern s32 generate_random_value(void);
extern u8 D_8014CA30[];
extern M2C_UNK D_8014CE5C;
extern u8 D_8014FD0C[];
extern u8 D_8014FD4C[];

void *spawn_effect_object(s16 flags, s16 value_24, s16 value_25, s16 value_0A);
#endif

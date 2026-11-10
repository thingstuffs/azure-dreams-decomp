#ifndef DUNGEON_OVL_9EF054_H
#define DUNGEON_OVL_9EF054_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_projectile_views.h"
#include "shared/position_views.h"
#include "dungeon/actor.h"
#include "engine/node/allocation.h"
#include "dungeon/actor/animation.h"
#include "dungeon/actor/status.h"
#include "engine/node.h"
struct ObjectNodeHeader;

typedef s32 M2C_UNK;

   /* obj in func_8016A854 */

   /* work in func_8016A854 */

   /* part_a in func_8016A854 */

   /* part_b in func_8016A854 */

typedef struct S_8016A854_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8016A854_4;   /* actor in func_8016A854 */

extern s32 generate_random_value(void);
extern u8 D_8016AA28[];
extern u8 dragon_slot_f_action_callback;
extern u8 D_8016DC7C[];
extern u8 D_8016DCDC[];

/* Allocates an actor object and initializes its parts and flags for the requested kind. */

void *create_mode_configured_actor_object(s16 kind_flags, s16 byte_24, s16 byte_25, s16 value_0a);
#endif

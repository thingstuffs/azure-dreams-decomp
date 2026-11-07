#ifndef DUNGEON_OVL_7F23B800_H
#define DUNGEON_OVL_7F23B800_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"
#include "engine/node.h"
#include "dungeon/actor/status.h"
struct ObjectNodeHeader;
struct ObjectNodeHeader;

typedef s32 M2C_UNK;

   /* work in func_8016A854 */

   /* part_b in func_8016A854 */

typedef struct S_8016A854_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x7];
    s16 unk_A4;
    s16 unk_A6;
} S_8016A854_4;   /* work_copy in func_8016A854 */

extern void func_8016AA8C(void *entity_state, void *entity_motion, SpriteFrameState *entity_part);
extern u8 D_8016DD30[];
extern u8 D_8016DD78[];
extern void func_8016AF74(ActorRecord *actor_in, ObjectPosition *actor_data_in, SpriteFrameState *sprite_in, ActorRecord *status_in);

extern void *func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
extern s32 func_8004491C(struct ObjectNodeHeader *entry, void *registration_id);
extern s32 generate_random_value(void);
extern void func_80044A50(struct ObjectNodeHeader *node);

void * create_mode_configured_actor_object(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c);
#endif

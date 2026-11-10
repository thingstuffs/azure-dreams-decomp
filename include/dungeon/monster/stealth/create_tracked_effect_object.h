#ifndef DUNGEON_OVL_7F223800_H
#define DUNGEON_OVL_7F223800_H
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

   /* result in func_8015E854 */

   /* data08 in func_8015E854 */

   /* data0C in func_8015E854 */

typedef struct S_8015E854_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x7];
    s16 unk_A4;
    s16 unk_A6;
} S_8015E854_4;   /* objectState in func_8015E854 */

extern void func_8015EA8C(void *entity_state, void *entity_motion, SpriteFrameState *entity_part);
extern u8 D_80161D30[];
extern u8 D_80161D78[];
extern void func_8015EF74(ActorRecord *actor_in, ObjectPosition *actor_data_in, SpriteFrameState *sprite_in, ActorRecord *status_in);

extern void *func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
extern s32 generate_random_value(void);

void * create_tracked_effect_object(s16 mode, s16 value24, s16 value25, s16 value0A);
#endif

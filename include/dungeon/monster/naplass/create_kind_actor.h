#ifndef DUNGEON_OVL_F95070_H
#define DUNGEON_OVL_F95070_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"
#include "dungeon/actor/status.h"
#include "engine/node.h"
struct R03_80170A28_S_80170A28_2;
struct ObjectNodeHeader;

typedef s32 M2C_UNK;




extern void *func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
extern s32 func_8004491C(struct ObjectNodeHeader *entry, void *registration_id);
extern s32 generate_random_value(void);
extern void func_80158A3C(void *entity, struct R03_80170A28_S_80170A28_2 *motion, void *part);
extern void dispatch_ability_action(ActorRecord *actor_in, ObjectPosition *actor_data_in, SpriteFrameState *sprite_in, ActorRecord *status_in);
extern u8 D_8015C194[];
extern u8 D_8015C1DC[];

void * create_kind_actor(s16 kind_flags, s16 part_value_24, s16 part_value_25, s16 part_value_0a);
#endif

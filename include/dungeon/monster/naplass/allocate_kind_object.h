#ifndef DUNGEON_OVL_F8F070_H
#define DUNGEON_OVL_F8F070_H
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
extern void func_8015EA3C(void *entity, struct R03_80170A28_S_80170A28_2 *motion, void *part);
extern void func_8015EE68(void *actor_in, void *actor_data_in, SpriteFrameState *sprite_in, void *status_in);
extern u8 D_80162194[];
extern u8 D_801621DC[];

void * allocate_kind_object(s16 spawn_flags, s16 value_24, s16 value_25, s16 value_0a);
#endif

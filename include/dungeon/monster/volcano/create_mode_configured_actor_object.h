#ifndef DUNGEON_OVL_E09000_CODE_H
#define DUNGEON_OVL_E09000_CODE_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor/animation.h"
#include "engine/node.h"
#include "engine/node/allocation.h"
#include "shared/entity.h"
struct S_80170A98_2;

#ifndef NULL
#define NULL 0
#endif



extern s32 generate_random_value(void);

extern void func_8016AA58(void *entity, struct S_80170A98_2 *motion, SpriteFrameState *monster);
extern void func_8016AE5C(ActorRecord *actor_in, ObjectPosition *context_in, SpriteFrameState *sprite_in, ActorRecord *status_in);
extern u8 volcano_frame_set_5[];
extern u8 D_8016E538[];

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
void *create_mode_configured_actor_object(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c);
#endif

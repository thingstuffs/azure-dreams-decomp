#ifndef DUNGEON_OVL_E27054_H
#define DUNGEON_OVL_E27054_H
#include "engine/node/registration.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "shared/object_node.h"
#include "engine/node/allocation.h"

typedef void (*Callback)(void);


extern s32 generate_random_value(void);
extern void set_or_clear_actor_status_slot(void *object, s32 attr_a, s16 attr_b);
extern void initialize_actor_sprite_and_animation(void *object, void *attr_a, void *attr_b, s32 attr_c);

extern void func_8014CE5C(ActorRecord *actor_in, ObjectPosition *context_in, SpriteFrameState *sprite_in, ActorRecord *status_in);
extern u8 volcano_frame_set[];
extern u8 D_80150538[];
extern void func_8014CA58(void);

void * spawn_effect_object(s32 spawn_flags, s16 attr_a, s16 attr_b, s32 attr_c);
#endif

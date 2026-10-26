#ifndef DUNGEON_EFFECT_STATE_H
#define DUNGEON_EFFECT_STATE_H

#include "common.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"




void dispatch_actor_state_handler(Rec_func_8008ACDC_arg0 *actor, void *context, SpriteFrameState *object, EntityRec *state);



void advance_effect_fade_and_flag(void *effect, ObjectPosition *motion, SpriteFrameState *primitive);

void forward_actor_effect_state(void *state, void *context, SpriteFrameState *data, void *render);

#endif

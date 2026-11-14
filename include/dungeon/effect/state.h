#ifndef DUNGEON_EFFECT_STATE_H
#define DUNGEON_EFFECT_STATE_H
struct ObjectPosition;

#include "common.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

typedef struct {
    s32 acceleration_x;
    s32 acceleration_y;
    s32 acceleration_z;
    u8 pad_0C[2];
    union { u16 remaining_frames; s16 radial_lifetime; } lifetime;
    s16 acceleration_step;
    u8 pad_12[2];
    union { u8 decrement; s16 initial_value; } red;
    union { u8 decrement; s16 initial_value; } green;
    union { u8 decrement; s16 initial_value; } blue;
} OppositeOffsetEffectBody;




void advance_linked_actor_motion(ActorRecord *state, ObjectPosition *context, SpriteFrameState *data, ActorRecord *extra_data);
void dispatch_actor_state_handler(Rec_func_8008ACDC_arg0 *actor, ObjectPosition *position, SpriteFrameState *object, ActorRecord *state);



void advance_effect_fade_and_flag(OppositeOffsetEffectBody *effect, ObjectPosition *motion, SpriteFrameState *primitive);

s32 update_hop_and_shrink_callback(ActorRecord *state, ObjectPosition *context, SpriteFrameState *data, ActorRecord *render);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct Context800B4194;
struct Entity800B4194;
s32 update_attached_effect_state(s16 tile_index, struct Entity800B4194 *entityp, struct Context800B4194 *contextp);

#endif

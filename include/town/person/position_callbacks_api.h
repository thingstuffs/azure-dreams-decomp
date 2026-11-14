#ifndef TOWN_PERSON_POSITION_CALLBACKS_API_H
#define TOWN_PERSON_POSITION_CALLBACKS_API_H
#include "common.h"
struct ObjectPosition;

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "shared/sprite_frame_state.h"
#include "shared/vector.h"
struct S_800C52D0_0;
void place_at_owner_sprite_offset(struct S_800C52D0_0 *object, struct ObjectPosition *out_pos, SpriteFrameState *state);
struct town_offset_actor;
struct town_offset_actor_position;
void move_toward_offset_town_position(struct town_offset_actor *actor, struct town_offset_actor_position *position, void *completion_arg);

#endif

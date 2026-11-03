#ifndef TOWN_PERSON_POSITION_CALLBACKS_API_H
#define TOWN_PERSON_POSITION_CALLBACKS_API_H
#include "common.h"

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "shared/sprite_frame_state.h"
#include "shared/vector.h"
struct S_800C52D0_0;
void compute_offset_position(struct S_800C52D0_0 *object, IntVector3 *out_pos, SpriteFrameState *state);

#endif

#ifndef TOWN_PERSON_POSITION_H
#define TOWN_PERSON_POSITION_H

short query_lowered_transform_position(void *position);
unsigned int get_facing_sector(int angle);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "shared/vector.h"
void compute_offset_position_linked_object(void *object, IntVector3 *out_pos);

void move_position_toward_target(void *work_data, void *position_data, void *completion_arg);

s16 clamp_transform_coordinate_deltas(s32 x, s32 y, void *origin);

#endif

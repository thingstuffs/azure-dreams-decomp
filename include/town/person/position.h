#ifndef TOWN_PERSON_POSITION_H
#define TOWN_PERSON_POSITION_H

#include "common.h"

/* Body of the owner-following sprite; the linked object is stored at +0x9C. */
typedef struct OwnerFollowingSpriteBody {
    /* 0x00 */ u8 pad_00[0x9C];
    /* 0x9C */ void *linked_object;
} OwnerFollowingSpriteBody;

short query_lowered_transform_position(void *position);
unsigned int get_facing_sector(int angle);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "shared/vector.h"
void compute_offset_position_linked_object(OwnerFollowingSpriteBody *object, IntVector3 *out_pos);

void move_position_toward_target(void *work_data, void *position_data, void *completion_arg);

s16 clamp_transform_coordinate_deltas(s32 x, s32 y, void *origin);

#endif

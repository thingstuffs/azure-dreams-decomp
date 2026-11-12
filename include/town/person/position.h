#ifndef TOWN_PERSON_POSITION_H
#define TOWN_PERSON_POSITION_H

#include "common.h"
struct ObjectPosition;

/* Body of the owner-following sprite; the linked object is stored at +0x9C. */
typedef struct OwnerFollowingSpriteBody {
    /* 0x00 */ u8 pad_00[0x9C];
    /* 0x9C */ void *linked_object;
} OwnerFollowingSpriteBody;

short query_lowered_transform_position(void *position);
unsigned int get_facing_sector(int angle);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "shared/vector.h"
void compute_offset_position_linked_object(OwnerFollowingSpriteBody *object, struct ObjectPosition *out_pos);

void move_position_toward_target(void *work_data, struct ObjectPosition *position_data, void *completion_arg);

struct TownObjectRecord;
/* ease_reaction_position_with_vertical_offset.c */
void ease_reaction_position_with_vertical_offset(struct TownObjectRecord *state_arg, void *position_arg);

s16 clamp_transform_coordinate_deltas(s32 x, s32 y, void *origin);

#include "shared/entity.h"
#include "shared/town_object.h"
void ease_reaction_position_to_target(TownObjectRecord *state, ObjectPosition *position, void *update_arg);

#endif

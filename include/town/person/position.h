#ifndef TOWN_PERSON_POSITION_H
#define TOWN_PERSON_POSITION_H

#include "common.h"
struct ObjectPosition;
struct TownObjectRecord;
struct SpriteFrameState;

/* Body of the owner-following sprite; the linked object is stored at +0x9C. */
typedef struct OwnerFollowingSpriteBody {
    /* 0x00 */ u8 pad_00[0x9C];
    /* 0x9C */ struct TownObjectRecord *linked_object;
} OwnerFollowingSpriteBody;

short query_lowered_transform_position(void *position);
unsigned int get_facing_sector(int angle);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "shared/vector.h"
void place_at_linked_object_offset(OwnerFollowingSpriteBody *object, struct ObjectPosition *out_pos);

void move_position_toward_target(struct TownObjectRecord *work, struct ObjectPosition *position_data, struct SpriteFrameState *sprite);

/* ease_reaction_position_with_vertical_offset.c */
void ease_reaction_position_with_vertical_offset(struct TownObjectRecord *state, struct ObjectPosition *position);

s16 clamp_transform_coordinate_deltas(s32 x, s32 y, struct ObjectPosition *origin);

#include "shared/entity.h"
#include "shared/town_object.h"
void ease_reaction_position_to_target(TownObjectRecord *state, ObjectPosition *position, struct SpriteFrameState *sprite);
void copy_view_position_with_height(TownObjectRecord *unused_object, ObjectPosition *position_out);

void update_sprite_offset_and_position(struct TownObjectRecord *object, struct ObjectPosition *position, struct SpriteFrameState *sprite);

#endif

#ifndef TOWN_PERSON_OBJECT_INITIALIZE_OBJECT_ENTRIES_API_H
#define TOWN_PERSON_OBJECT_INITIALIZE_OBJECT_ENTRIES_API_H

#include "common.h"
#include "shared/town_object.h"
#include "shared/sprite_frame_state.h"

/* Directional entry-selection state inside a town object.
 * initialize_object_entries stores the list, counts it and selects output by heading. */

void initialize_object_entries(TownObjectRecord *state, SpriteFrameState *output, s32 *entries);

#endif

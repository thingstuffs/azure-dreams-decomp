#ifndef DUNGEON_EFFECT_OBJECT_H
#define DUNGEON_EFFECT_OBJECT_H

/* Function contracts owned by src/dungeon/effect/object/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/object_node.h"
void allocate_payload_object(ObjectNodeHeader *owner, s32 payloadValue, s16 payloadShortValue);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void *allocate_object_at_coordinates(void *source, s32 *init_value);

#endif

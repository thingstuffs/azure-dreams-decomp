#ifndef DUNGEON_EFFECT_OBJECT_H
#define DUNGEON_EFFECT_OBJECT_H

/* Function contracts owned by src/dungeon/effect/object/ (decision 74; maintained by tools/headers). */
#include "common.h"
struct ObjectNodeHeader;

/* Payload body shared by its allocator and positioned-effect updater. */
typedef struct PayloadObjectBody {
    struct ObjectNodeHeader *owner;
    s32 unk_04;
    u8 pad_08[0x84];
    s16 unk_8C;
    union { u16 u; s16 s; } unk_8E;
} PayloadObjectBody;
#include "shared/object_node.h"
void allocate_payload_object(ObjectNodeHeader *owner, s32 payloadValue, s16 payloadShortValue);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void *allocate_object_at_coordinates(void *source, s32 *init_value, s16 unused_dispatch_mode);

#endif

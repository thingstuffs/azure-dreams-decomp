#ifndef TOWN_PERSON_OBJECT_INITIALIZE_OBJECT_ENTRIES_API_H
#define TOWN_PERSON_OBJECT_INITIALIZE_OBJECT_ENTRIES_API_H

#include "common.h"

/* Directional entry-selection state inside a town object.
 * initialize_object_entries stores the list, counts it and selects output by heading. */
typedef struct {
    /* 0x64 */ char pad0[0x64];
    /* 0x64 */ s16 unk64; /* number of entries before the zero terminator */
    /* 0x66 */ char pad1[0x0C];
    /* 0x72 */ s16 unk72; /* heading passed to quantize_heading_to_sector to choose a list entry */
    /* 0x74 */ char pad2[0x02];
    /* 0x78 */ s32 *unk78; /* zero-terminated array of entry words supplied by the initializer caller */
} Struct800C5724;

void initialize_object_entries(Struct800C5724 *, s8 *, s32 *);

#endif

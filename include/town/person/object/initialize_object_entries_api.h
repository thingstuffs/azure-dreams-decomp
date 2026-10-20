#ifndef TOWN_PERSON_OBJECT_INITIALIZE_OBJECT_ENTRIES_API_H
#define TOWN_PERSON_OBJECT_INITIALIZE_OBJECT_ENTRIES_API_H

#include "common.h"

typedef struct {
    /* 0x64 */ char pad0[0x64];
    /* 0x64 */ s16 unk64;
    /* 0x66 */ char pad1[0x0C];
    /* 0x72 */ s16 unk72;
    /* 0x74 */ char pad2[0x02];
    /* 0x78 */ s32 *unk78;
} Struct800C5724;

void initialize_object_entries(Struct800C5724 *, s8 *, s32 *);

#endif

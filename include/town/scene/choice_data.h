#ifndef TOWN_SCENE_CHOICE_DATA_H
#define TOWN_SCENE_CHOICE_DATA_H

#include "common.h"

/* Selected town scene choice at 0x80019BB4. */
extern s32 scene_choice_index;

typedef struct Destination {
    s32 unk0[8];
    s32 value;
} Destination;

Destination *copy_indexed_entry_value(s32 index);

#endif

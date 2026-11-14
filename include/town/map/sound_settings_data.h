#ifndef TOWN_MAP_SOUND_SETTINGS_DATA_H
#define TOWN_MAP_SOUND_SETTINGS_DATA_H

#include "common.h"

/* Ten-byte records terminated by a zero key; upper bound is not inferred. */
typedef struct {
    s16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    s16 unk8;
} TownEntry;

extern TownEntry map_sound_settings[];

#endif

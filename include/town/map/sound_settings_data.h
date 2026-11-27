#ifndef TOWN_MAP_SOUND_SETTINGS_DATA_H
#define TOWN_MAP_SOUND_SETTINGS_DATA_H

#include "common.h"

/* Ten-byte records terminated by a zero key; upper bound is not inferred. */
typedef struct {
    s16 map_index;
    u16 sound_effect_bank;
    u16 sound_command;
    u16 stream_index;
    s16 sequence_command;
} TownEntry;

extern TownEntry map_sound_settings[];

#endif

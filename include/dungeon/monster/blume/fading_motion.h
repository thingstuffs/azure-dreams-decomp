#ifndef DUNGEON_MONSTER_BLUME_FADING_MOTION_H
#define DUNGEON_MONSTER_BLUME_FADING_MOTION_H

#include "common.h"

/* Created during Blume's item visual action and consumed by its fading-motion callback. */
typedef struct BlumeFadingMotionBody {
    u16 unk_00;
    u8 initial_red;
    u8 initial_green;
    u8 initial_blue;
    u8 pad_05[0x1F];
    u16 ticks_left;
    u8 pad_26[0x4];
    u16 late_step;
    u16 vertical_drop_step;
    u8 pad_2E[0x6];
    u8 sprite_entries[12];
    u8 pad_40[0xE];
    u16 late_countdown;
    u16 accumulated_step;
} BlumeFadingMotionBody;

#endif

#ifndef DUNGEON_EFFECT_PARTICLE_BRIGHTENING_FADE_H
#define DUNGEON_EFFECT_PARTICLE_BRIGHTENING_FADE_H

#include "common.h"

/* Body allocated by create_brightening_fading_effect and updated by
 * update_brightening_fading_effect. The creator stores an integer node address
 * at body offset 0x0C. */
typedef struct BrighteningFadeBody {
    u8 pad_00[0x0C];
    s32 source_node_address;
    u8 pad_10[0x30];
    u16 offset_x;
    u16 offset_y;
    s16 offset_z;
    u8 pad_46[0x2];
    s16 phase;
    s16 initialized;
} BrighteningFadeBody;

#endif

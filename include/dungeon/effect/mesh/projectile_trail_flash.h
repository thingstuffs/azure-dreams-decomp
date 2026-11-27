#ifndef DUNGEON_EFFECT_MESH_PROJECTILE_TRAIL_FLASH_H
#define DUNGEON_EFFECT_MESH_PROJECTILE_TRAIL_FLASH_H

#include "common.h"

/* Body of a trail flash node allocated by update_projectile_trail_and_hit_effect. */
typedef struct ProjectileTrailFlashBody {
    u8 pad_00[0x2];
    s16 remaining_ticks;
    s16 duration;
    u8 pad_06[0x30];
    u8 base_red;
    u8 base_green;
    u8 base_blue;
    u8 pad_39[0x9];
    s16 flicker_phase;
    u8 pad_44[0x8];
    u8 texture_u;
} ProjectileTrailFlashBody;

#endif

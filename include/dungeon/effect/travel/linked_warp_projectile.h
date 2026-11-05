#ifndef DUNGEON_EFFECT_TRAVEL_LINKED_WARP_PROJECTILE_H
#define DUNGEON_EFFECT_TRAVEL_LINKED_WARP_PROJECTILE_H

#include "common.h"

/* The body installed by create_linked_sprite_pieces and updated by
 * update_warp_camera_and_effects. The first 0x20 bytes are animation state. */
typedef struct LinkedWarpProjectileBody {
    u8 animation_state[0x20];
    void *linked_node;
    u8 pad_24[0x8];
    s16 phase;
    u8 pad_2E[0x2];
    s16 fade_ticks;
    s16 animation_index;
    s16 heading;
    s16 animation_end;
    s16 animation_start;
    u8 pad_3A[0x2];
    /* UNION: warp.c:update_warp_camera_and_effects writes current_tile.tile.x/y
     * and compares current_tile.packed at the same site; warp.c:create_linked_sprite_pieces
     * initializes this body and installs that updater on the node. */
    union {
        s32 packed;
        struct { s16 x; s16 y; } tile;
    } current_tile;
    /* Unproven view (tracked): warp.c:update_warp_camera_and_effects compares previous_tile.packed
     * and writes previous_tile.tile.x/y on the same body; warp.c:create_linked_sprite_pieces
     * initializes both halves and installs that updater. */
    union {
        s32 packed;
        struct { u16 x; u16 y; } tile;
    } previous_tile;
    u16 damage_power;
    s16 hits_left;
    s16 piece_index;
} LinkedWarpProjectileBody;

#endif

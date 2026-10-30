#ifndef TOWN_MINIGAME_PICKUP_DATA_H
#define TOWN_MINIGAME_PICKUP_DATA_H

#include "common.h"

/* Bouncing coin pickup body.  update_betting_effect fills one as a message and
 * initialize_source_and_initial_data copies it whole into the payload of a 0x136
 * node (after its ObjectNodeHeader), installs update_bouncing_pickup and draws it
 * with project_sprite_chain; the callback then receives the same record as arg0.
 * The source x halfword at +0x54 is signed.  This record does not describe the
 * ObjectNodeHeader or the separate SpriteFrameState rendering subrecord. */
typedef struct minigame_pickup_source {
    /* 0x00 */ s16 kind; /* update_bouncing_pickup state: 0 waits, 1 launches, 2-5 bounce, 6 retires */
    /* 0x02 */ u16 timer; /* frames left in the current bounce/idle state */
    /* 0x04 */ void *owner; /* betting effect that spawned the pickup; its flag 8 retires every pickup */
    /* 0x08 */ u8 pad08[0x15]; /* scene collision record (configure_the_set_mode_n_1, unlink_scene_list_node) */
    /* 0x1D */ u8 unk_1D;
    /* 0x1E */ u8 pad1E[0x32];
    /* 0x50 */ void *unk_50; /* sprite table stored by the creator */
    /* 0x54 */ s16 x; /* grid column: also the coin denomination (0, 1, 2 = 1, 10, 100) */
    /* 0x56 */ s16 y; /* grid row: the sprite shows while it is below the matching payout digit */
} minigame_pickup_source;

typedef struct minigame_pickup_initial {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 e;
    s32 f;
} minigame_pickup_initial;

void initialize_source_and_initial_data(minigame_pickup_source *, minigame_pickup_initial *);

#endif

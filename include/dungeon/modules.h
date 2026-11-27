#ifndef DUNGEON_MODULES_H
#define DUNGEON_MODULES_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Body of the gray fading sprite node: each module's create_gray_fading_sprite allocates it, sets a 0x30 gray and a
 * five-update lifetime and installs spin_and_fade_gray_sprite, which scales the gray into the sprite color by
 * ticks_left / 5 each update and removes the node when ticks_left reaches zero. */
typedef struct GrayFadeSpriteBody {
    /* 0x00 */ u8 base_r; /* red level before fading */
    /* 0x01 */ u8 base_g; /* green level before fading */
    /* 0x02 */ u8 base_b; /* blue level before fading */
    u8 pad_03[0x21];
    /* 0x24 */ s16 ticks_left; /* updates left before removal */
} GrayFadeSpriteBody;

/* Body of one segment of the radial effect bands (the block's effect, also placed in the module images):
 * create_radial_effect_bands allocates the node with flags 0x12, which puts the node's position record 0xC8
 * bytes after the body's start, installs update_radial_effect_band as its update callback and registers it under
 * project_linked_effect_quads, which draws the four vertices with their four colors as one shaded quad. */
typedef struct RadialBandSegment {
    /* 0x00 */ u8 base_r; /* red level the fade in reaches and phase 1 holds; phase 2 fades all three channels from it */
    /* 0x01 */ u8 base_g; /* green level the fade in reaches and phase 1 holds */
    /* 0x02 */ u8 base_b; /* blue level the fade in reaches and phase 1 holds */
    u8 pad_03;
    /* 0x04 */ SpriteColor vertex_colors[4]; /* color words copied into the shaded quad */
    u8 pad_14[0x08];
    /* 0x1C */ s16 phase; /* 0 fades in, 1 holds and starts the burst, 2 drifts and fades out */
    u8 pad_1E[0x06];
    /* 0x24 */ s16 ticks_left; /* updates left before removal */
    /* 0x26 */ s16 age; /* updates counted in phase 0, and in phase 1 by segments 0 to 3 */
    u8 pad_28[0x02];
    /* 0x2A */ s16 segment; /* index of the segment in its band, 0 to 7 */
    /* 0x2C */ s16 fade_in_delay; /* age at which the fade in starts, staggered by creation order */
    u8 pad_2E[0x16];
    /* 0x44 */ struct { s16 x; s16 y; s16 z; } vertices[4]; /* quad corners relative to the position */
    u8 pad_5C[0x1E];
    /* 0x7A */ u8 sprite_source[12]; /* copied from a template; the creator points the sprite's source at it */
    u8 pad_86[0x0E];
    /* 0x94 */ s32 velocity_x; /* added to the position each update in phase 2 */
    /* 0x98 */ s32 velocity_y;
    /* 0x9C */ s32 velocity_z;
} RadialBandSegment;



void func_8014E9A8(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_block_attack_slot_c(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_block_attack_slot_d(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_block_attack_slot_f(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/tile_object.h"
void choose_block_move_slot_a(Rec_func_800A9E70_arg0 *move_data, void *context, TileObject *position_data, ActorRecord *actor_data);

#endif

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



void func_8014E9A8(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);
void func_8015A9A8(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);
void func_801609A8(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);
void func_8016C9A8(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/tile_object.h"
void choose_block_move_slot_a(Rec_func_800A9E70_arg0 *move_data, void *context, TileObject *position_data, ActorRecord *actor_data);

#endif

#ifndef DUNGEON_EFFECT_SPRITE_LINKED_OBJECT_CHAIN_H
#define DUNGEON_EFFECT_SPRITE_LINKED_OBJECT_CHAIN_H

#include "common.h"
#include "shared/object_node.h"
#include "shared/vector.h"

/* Each of the 18 sprite sources selects its own 16 transform frames. */
typedef struct LinkedSpriteFrame {
    SVECTOR rotation;
    SVECTOR translation;
    SVECTOR scale;
} LinkedSpriteFrame;

typedef struct LinkedSpriteSource {
    void *data[3];
    LinkedSpriteFrame *frames;
} LinkedSpriteSource;

/* Body of a node allocated by create_linked_object_chain. */
typedef struct LinkedObjectChainBody {
    MATRIX transform;
    ObjectNodeHeader *head;
    SVECTOR position_offset; /* orientation result; added to the reference position */
    s16 phase;
    s16 draw_registered;
    s16 ticks_left;
    s16 frame_step;
    s16 start_angle;
    s16 last_frame;
    s16 first_frame;
    u16 ground_height;
    s16 tile_x;
    s16 tile_y;
    s16 direction;
    u16 steps_left;
} LinkedObjectChainBody;

struct SpriteFrameState;
void step_entry_index_within_bounds(struct SpriteFrameState *sprite, s16 *step, s32 lower, s32 upper);

/* Attack option supplied when the linked effect chain is created. */
extern u8 linked_effect_chain_attack_option;

#endif

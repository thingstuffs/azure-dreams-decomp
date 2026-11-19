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
    s16 unk_2C;
    s16 unk_2E;
    s16 unk_30;
    s16 unk_32;
    s16 unk_34;
    s16 unk_36;
    s16 unk_38;
    u16 unk_3A;
    s16 unk_3C;
    s16 unk_3E;
    s16 unk_40;
    u16 unk_42;
} LinkedObjectChainBody;

struct SpriteFrameState;
void step_entry_index_within_bounds(struct SpriteFrameState *sprite, s16 *step, s32 lower, s32 upper);

/* Attack option supplied when the linked effect chain is created. */
extern u8 linked_effect_chain_attack_option;

#endif

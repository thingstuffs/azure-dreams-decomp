#ifndef DUNGEON_TRACKED_SPRITE_EFFECT_H
#define DUNGEON_TRACKED_SPRITE_EFFECT_H

#include "common.h"
#include "shared/object_node.h"

/* The registered draw callback renders the owner's position and sprite.
 * The update callback tests the borrowed frame-table slot for completion. */
typedef struct TrackedSpriteEffect {
    ObjectNodeHeader *owner;
    void *const *frame_table_slot;
    u8 pad_08[4];
    u16 mode_value;
    s16 mode;
} TrackedSpriteEffect;

ObjectNodeHeader *create_tracked_effect(ObjectNodeHeader *owner, s16 mode, void *frame_table_slot, void *unused);
void retire_effect_when_owner_or_value_ends(TrackedSpriteEffect *effect);
void retire_tracked_effect_by_id(ObjectNodeHeader *owner);

#endif

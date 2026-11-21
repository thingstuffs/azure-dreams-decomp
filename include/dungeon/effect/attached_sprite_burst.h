#ifndef DUNGEON_EFFECT_ATTACHED_SPRITE_BURST_H
#define DUNGEON_EFFECT_ATTACHED_SPRITE_BURST_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* The selector-52 creator stores its action in the new body and initializes
 * these three fixed-point coordinates from the caster's attachment. */
typedef struct BurstParent {
    u8 reserved[0x52];
    u16 flags;
} BurstParent;

typedef struct AttachedSpriteBurst {
    BurstParent *parent;
    u8 reserved_04[8];
    s16 origin_x, origin_y, origin_z;
    u8 reserved_12[0x0a];
    Fixed1616 x, y, z;
    u8 reserved_28[0x20];
    s16 ticks;
    s16 reserved_4a;
    s16 phase;
} AttachedSpriteBurst;

typedef struct DriftingEffect {
    BurstParent *parent;
} DriftingEffect;

void update_attached_sprite_burst(AttachedSpriteBurst *effect, ObjectPosition *position, SpriteFrameState *sprite);
void update_drifting_effect(DriftingEffect *effect, ObjectPosition *position, SpriteFrameState *sprite);

#endif

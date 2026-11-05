#ifndef DUNGEON_PLAYER_FAMILIAR_DEPLOYMENT_OVERLAY_H
#define DUNGEON_PLAYER_FAMILIAR_DEPLOYMENT_OVERLAY_H

#include "common.h"
#include "shared/sprite_frame_state.h"

/* Body initialized by the owner-state creator and advanced by the shared familiar callback. */
typedef struct FamiliarDeploymentOverlayBody {
    SpriteFrameState *owner_sprite;
    u16 mode;
    u16 ticks_left;
    s16 animation_index;
} FamiliarDeploymentOverlayBody;

#endif

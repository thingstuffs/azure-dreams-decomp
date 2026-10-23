#include "common.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "records/Rec_D_80082E80.h"

typedef struct EffectScaleState {
    u8 pad_00[8];
    s16 scale_enabled;
} EffectScaleState;
extern s32 D_800814A0;
/* Fades the sprite, optionally enlarges it, and marks it for removal when the red channel reaches zero. */
void fade_and_scale_sprite(void *actor, void *unused, SpriteFrameState *packet) {
    u16 depth;
    u16 *flags;
    packet->color.word += 0xFFEFEFF0U;
    if (((EffectScaleState *)actor)->scale_enabled != 0) {
        depth = (u16)(packet->scale_y + 0x120);
        depth -= packet->color.c.r >> 3;
        packet->scale_y = depth;
        packet->scale_x = depth;
    }
    if (packet->color.c.r == 0) {
        flags = &((ObjectNodeHeader *)actor)[-1].flags;
        *flags |= 0x8000;
        D_800814A0 |= OBJECT_REMOVE_PENDING;
    }
}

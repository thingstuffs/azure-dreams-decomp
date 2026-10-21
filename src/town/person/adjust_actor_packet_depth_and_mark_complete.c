#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "records/Rec_D_80082E80.h"

typedef struct EffectScaleState {
    u8 pad_00[8];
    s16 scale_enabled;
} EffectScaleState;
extern s32 D_800814A0;
void fade_and_scale_sprite(void *actor, void *unused, void *packet) {
    u16 depth;
    u16 *flags;
    ((SpriteFrameState *)packet)->color.word += 0xFFEFEFF0U;
    if (((EffectScaleState *)actor)->scale_enabled != 0) {
        depth = (u16)(((SpriteFrameState *)packet)->scale_y + 0x120);
        depth -= ((SpriteFrameState *)packet)->color.c.r >> 3;
        ((SpriteFrameState *)packet)->scale_y = depth;
        ((SpriteFrameState *)packet)->scale_x = depth;
    }
    if (((SpriteFrameState *)packet)->color.c.r == 0) {
        flags = &((ObjectNodeHeader *)actor)[-1].flags;
        *flags |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

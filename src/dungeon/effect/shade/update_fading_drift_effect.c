#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"

typedef struct {
    void *unk0;
    u16 unk4;
} State;

extern void advance_sprite_animation_and_textures(void *);

/* Updates effect motion and fading, marking completion when the timer expires. */
void update_fading_drift_effect(State *state, void *position, SpriteFrameState *visual) {
    void *owner;
    u8 color;

    owner = state->unk0;
    *(u16 *)((u8 *)owner + 0xC) += 1;
    state->unk4 += 1;
    visual->angle_z += 0x480;
    *(s32 *)((u8 *)position + 8) += 0xFFF60000;
    advance_sprite_animation_and_textures(visual);

    if ((s16)state->unk4 < 0x11) {
        color = visual->color.c.r;
        if (color != 0) {
            visual->color.c.r = color - 0xC;
        }
        color = visual->color.c.g;
        if (color != 0) {
            visual->color.c.g = color - 0xC;
        }
        color = visual->color.c.b;
        if (color != 0) {
            visual->color.c.b = color - 0xC;
            return;
        }
        return;
    }

    *(u16 *)((u8 *)state - 2) |= NODE_REMOVE;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    return;
}

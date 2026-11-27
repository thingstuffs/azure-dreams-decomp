#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "slus.h"
#include "shared/dungeon_effect_state.h"

typedef struct {
    void *owner;
    u16 elapsed_ticks;
} State;

/* Updates effect motion and fading, marking completion when the timer expires. */
void update_fading_drift_effect(State *state, ObjectPosition *position, SpriteFrameState *visual) {
    B22_81893474_EffectState *owner;
    u8 color;

    owner = state->owner;
    owner->unkC.u += 1;
    state->elapsed_ticks += 1;
    visual->angle_z += 0x480;
    position->z.v += 0xFFF60000;
    advance_sprite_animation_and_textures(visual);

    if ((s16)state->elapsed_ticks < 0x11) {
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

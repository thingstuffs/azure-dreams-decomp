#include "frontend/settings/controller_body.h"
#include "frontend/settings.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
extern void advance_sprite_animation_and_textures(void *);
extern int abs(int);

/* Updates phased motion and marks completion when stopped or out of bounds. */
void update_settings_phase_motion(SettingsEffectObjectBody *state, ObjectPosition *motion, SpriteFrameState *update_data)
{
    SettingsMenuBody *owner;
    s16 step;
    s32 x_velocity;
    s32 horizontal_value;
    s32 previous_y;

    owner = state->owner;
    advance_sprite_animation_and_textures(update_data);
    if (owner->flags & 1)
        state->state = 255;

    step = state->state;
    switch (step) {
    case 0:
        return;

    case 1:
        motion->x.v += motion->velocity_x;
        motion->y.v += motion->velocity_y;
        motion->velocity_x += state->index != 0 ? -0x10000 : 0x10000;
        motion->velocity_y += 0x8000;
        if (motion->velocity_x != 0)
            return;
        state->state++;
        return;

    case 2:
        horizontal_value = 232;
        if (state->index != 0)
            horizontal_value = 88;
        motion->x.w.i = horizontal_value;
        motion->y.w.i = owner->selected_item * 16 + 168;
        if (owner->state != 32)
            return;
        horizontal_value = -0x20000;
        if (state->index != 0)
            horizontal_value = 0x20000;
        motion->velocity_x = horizontal_value;
        motion->velocity_y = -0x40000;
        state->state++;
        return;

    case 3:
        previous_y = motion->y.v;
        motion->x.v += motion->velocity_x;
        motion->y.v += motion->velocity_y;
        x_velocity = motion->velocity_x;
        motion->velocity_x = x_velocity + (x_velocity >> 3);
        if (abs(motion->x.w.i) < 361)
            return;
        state->state = 255;
        return;

    case 255:
        NODE_HEADER(state)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;

    default:
        return;
    }
}

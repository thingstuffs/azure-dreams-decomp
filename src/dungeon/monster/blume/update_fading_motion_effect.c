#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/object_flags.h"
#include "dungeon/monster/blume.h"
#include "dungeon/monster/blume/fading_motion.h"
#include "shared/object_node.h"

/* Update the effect countdown and motion, fade its color, and flag expiration. */
void update_fading_motion_effect(BlumeFadingMotionBody *effect, ObjectPosition *transform, SpriteFrameState *color) {
    u16 next_value;
    u16 next_total;
    s16 ticks_left;

    next_value = effect->ticks_left - 1;
    effect->ticks_left = next_value;
    if ((s16)next_value < 8) {
        effect->late_countdown = effect->late_countdown - 1;
    }

    if ((s16)effect->late_countdown < 2) {
        effect->late_countdown = 2;
    }

    if ((s16)effect->ticks_left < 10) {
        next_value = effect->late_step + 1;
        next_total = effect->accumulated_step + next_value;
        effect->late_step = next_value;
        effect->accumulated_step = next_total;
    } else {
        effect->accumulated_step = effect->accumulated_step + 1;
    }

    if ((s16)effect->ticks_left < 11) {
        next_value = effect->vertical_drop_step + 2;
        effect->vertical_drop_step = next_value;
        transform->z.unsigned_parts.integer = transform->z.unsigned_parts.integer - next_value;
    }

    ticks_left = ((s16)effect->ticks_left);
    if (ticks_left < 5) {
        color->color.c.r = (effect->initial_red * ticks_left) / 5;
        color->color.c.g = (effect->initial_green * ((s16)effect->ticks_left)) / 5;
        color->color.c.b = (effect->initial_blue * ((s16)effect->ticks_left)) / 5;
    }

    if (((s16)effect->ticks_left) <= 0) {
        NODE_HEADER(effect)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

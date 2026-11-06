#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/object_flags.h"
#include "dungeon/monster/blume.h"
#include "dungeon/monster/blume/fading_motion.h"
#include "shared/object_node.h"

/* Update the effect countdown and motion, fade its color, and flag expiration. */
void update_fading_motion_effect(void *effect_arg, void *transform_arg, void *color_arg) {
    SpriteFrameState *color = color_arg;
    ObjectPosition *transform = transform_arg;
    BlumeFadingMotionBody *effect = effect_arg;
    u16 next_value;
    u16 next_total;
    s16 ticks_left;

    next_value = effect->ticks_left - 1;
    effect->ticks_left = next_value;
    if ((s16)next_value < 8) {
        effect->unk_4E = effect->unk_4E - 1;
    }

    if ((s16)effect->unk_4E < 2) {
        effect->unk_4E = 2;
    }

    if ((s16)effect->ticks_left < 10) {
        next_value = effect->unk_2A + 1;
        next_total = effect->unk_50 + next_value;
        effect->unk_2A = next_value;
        effect->unk_50 = next_total;
    } else {
        effect->unk_50 = effect->unk_50 + 1;
    }

    if ((s16)effect->ticks_left < 11) {
        next_value = effect->unk_2C + 2;
        effect->unk_2C = next_value;
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

#include "common.h"
#include "dungeon/effect/motion.h"
#include "dungeon/effect/orbit_burst_spell.h"
#include "slus/imports.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"

#include "sdk/rand.h"

/* Advance a random number of flight sprite frames and signal that the parent spell is busy. */
void advance_random_rotation_flight_sprite(LinkedCounterSpriteBody *body, ObjectPosition *unused, SpriteFrameState *target)
{
    s32 random_value;
    s16 update_count;
    s16 update_index;
    s16 next_index;

    body->owner->busy++;
    target->angle_z = 0;

    random_value = rand();
    update_count = (random_value % 4) + 1;

    update_index = 0;
    if (update_count > 0) {
        do {
            advance_sprite_animation_and_textures(target);
            next_index = update_index + 1;
            update_index = next_index;
        } while (next_index < update_count);
    }

    if (target->flags & 0x6000) {
        NODE_HEADER(body)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

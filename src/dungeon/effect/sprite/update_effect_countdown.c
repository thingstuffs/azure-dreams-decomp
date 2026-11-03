#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "slus.h"
#include "dungeon/effect/sprite.h"



   /* arg1 in update_effect_countdown */





/* Copy stored values, run the update, and flag completion when the count reaches zero. */
void update_effect_countdown(AnchoredDirectionalObjectBody *object, MovingPosition *output, void *update_arg) {
    u16 remaining;
    MovingPosition *source;

    source = object->source_position;
    output->x = (u16) source->x;
    output->y = (u16) source->y;
    output->z = (u16) source->z;
    advance_sprite_animation_and_textures(update_arg);
    remaining = object->remaining - 1;
    object->remaining = remaining;
    if ((remaining << 0x10) <= 0) {
        NODE_HEADER(object)->flags = (u16) (NODE_HEADER(object)->flags | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}

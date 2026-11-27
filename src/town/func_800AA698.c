/* Recovered retail twin. */
#include "common.h"
#include "engine/node/registration.h"
#include "slus/imports.h"
#include "shared/town_object.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "town.h"
#include "town/menu.h"


/* Unlinks and marks an object on a nonzero bounds classification; otherwise advances its sprite animation. */
void retire_object_or_animate_sprite(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *sprite)
{
    u8 *status_byte;

    if (classify_object_against_bounds(object, position) != 0) {
        status_byte = object->spawn_active;
        if (status_byte != 0) {
            *status_byte = 0;
        }
        unlink_node_if_registered(object);
        NODE_HEADER(object)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    } else {
        advance_sprite_animation_and_textures(sprite);
    }
}

/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/town_object.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "town.h"
#include "town/menu.h"

extern void unlink_node_if_registered(void *object);
extern void advance_sprite_animation_and_textures(void *fallback_data);

/* Unlinks and marks an object on a nonzero bounds classification; otherwise advances its sprite animation. */
void handle_object_bounds_and_cleanup(TownObjectRecord *object, void *check_data, void *fallback_data)
{
    u8 *status_byte;

    if (classify_object_against_bounds(object, check_data) != 0) {
        status_byte = *(u8 **)((u8 *)object + 0x98);
        if (status_byte != 0) {
            *status_byte = 0;
        }
        unlink_node_if_registered(object);
        ((ObjectNodeHeader *)object - 1)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    } else {
        advance_sprite_animation_and_textures(fallback_data);
    }
}

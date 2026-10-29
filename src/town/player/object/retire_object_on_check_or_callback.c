#include "common.h"
#include "shared/object_flags.h"
#include "engine/node.h"
#include "town/menu.h"
#include "town/player/object.h"
#include "town/scene/object.h"

/* Global 32-bit "used"/flags word, same one touched by func_8004B530 /
 * set_object_cleanup_flag / propagate_scene_flag family. Declared as an array (>8B) so gcc
 * uses %hi/%lo addressing with a SINGLE shared base register across the
 * read and write halves of the |= (see w_800510DC.c), matching retail's
 * one lui reused for both the load and the store. */

typedef void (*S_800A9590_Callback)(void *, void *, void *, void *);

/* Cleans up and flags the object when its check succeeds, otherwise invokes its callback. */
void retire_object_on_check_or_callback(void *object, void *input, void *context)
{
    u8 *status_byte;
    S_800A9590_Callback callback;

    if (classify_object_against_bounds(object, input) != 0) {
        unlink_scene_list_node(object);
        status_byte = *(u8 **)((u8 *)object + 0x98);
        if (status_byte != 0) {
            *status_byte = 0;
        }
        unlink_node_if_registered(object);
        *(u16 *)((u8 *)object - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    callback = *(S_800A9590_Callback *)((u8 *)object + 0x50);
    if (callback != 0) {
        callback(object, object, input, context);
    }
}

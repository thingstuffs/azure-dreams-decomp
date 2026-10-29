#include "common.h"
#include "shared/object_flags.h"
#include "engine/node.h"
#include "town/menu.h"
#include "town/person/object.h"
#include "town/scene/object.h"

typedef void (*Callback)(void *, s32, s32);

/* Clears and flags the object when the check succeeds, or invokes its callback. */
void finalize_transform_object_or_callback(void *object, s32 check_value, s32 callback_value) {
    u16 *object_flags;
    s8 *status_byte;

    if (classify_object_against_bounds(object, check_value) != 0) {
        unlink_scene_list_node(object);
        status_byte = *(s8 **)((u8 *)object + 0x98);
        if (status_byte != 0) {
            *status_byte = 0;
        }
        unlink_node_if_registered(object);
        object_flags = (u16 *)object - 1;
        *object_flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    } else {
        (*(Callback *)((u8 *)object + 0x50))(object, check_value, callback_value);
    }
}

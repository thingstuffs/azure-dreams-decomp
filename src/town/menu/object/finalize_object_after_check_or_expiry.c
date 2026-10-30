#include "common.h"
#include "shared/object_flags.h"
#include "town/menu/object.h"

extern s32 classify_object_against_bounds(void *object, s32 position_data);
extern void unlink_node_if_registered(void *object);


/* Finalizes and flags the object when its check succeeds or its countdown expires. */
void finalize_object_after_check_or_expiry(BoundsExpiryObject *object, s32 check_value)
{
    u8 *linked_flag;
    u16 ticks_left;

    if (classify_object_against_bounds(object, check_value) != 0) {
        linked_flag = object->linked_flag;
        if (linked_flag != 0) {
            *linked_flag = 0;
        }
    } else {
        ticks_left = object->timer - 1;
        object->timer = ticks_left;
        if ((s16)ticks_left > 0) {
            return;
        }
    }

    unlink_node_if_registered(object);
    *(u16 *)((u8 *)object - 2) |= NODE_REMOVE;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
}

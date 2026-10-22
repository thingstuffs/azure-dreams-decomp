/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "shared/object_flags.h"
#include "common.h"

extern void unlink_node_if_registered(void *object);

/* Dims the primitive by six per tick, then unlinks and marks the object for removal at zero brightness. */
void decrease_primitive_brightness_and_mark_cleanup(void *object, void *unusedContext, u8 *primitive)
{
    s32 brightness;

    brightness = primitive[0xE] - 6;
    if (brightness < 0) {
        brightness = 0;
    }
    primitive[0xE] = brightness;
    primitive[0xD] = brightness;
    primitive[0xC] = brightness;
    if (brightness != 0) {
        return;
    }
    unlink_node_if_registered(object);
    *(u16 *)((u8 *)object - 2) |= NODE_REMOVE;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
}

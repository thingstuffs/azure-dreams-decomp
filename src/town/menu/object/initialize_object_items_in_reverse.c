#include "common.h"

#include "town/menu/motion.h"
#include "town/menu/object.h"

/* Initializes the object's items in reverse order and sets its default fields. */
s32 initialize_object_items_in_reverse(struct DoorTransitionEffect *object, struct ObjectPosition *origin, s32 item_count) {
    struct ObjectNodeHeader **items;
    s32 remaining;

    remaining = item_count;
    items = object->children;
    while (remaining > 0) {
        remaining--;
        items[remaining] = create_shaded_primitive_object(object, remaining, origin);
        if (items == 0) {
            return remaining + 1;
        }
    }

    object->angle_x = 0;
    object->angle_y = 0x800;
    object->angle_z = 0;
    object->extent = 0x180;
    object->intensity = 0;
    object->timer = 0;
    object->brightness = 0xFF;
    object->texture_x = 0x340;
    object->texture_y = 0;
    object->texture_width = 0x80;
    object->texture_height = 0x80;
    object->half_width = 0x80;
    object->half_height = 0xA0;
    object->finished = 0;
    return 0;
}

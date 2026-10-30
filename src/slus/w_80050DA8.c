#include "slus/saved_value_b98.h"
#include "shared/object_node.h"
#include "slus.h"
#include "engine/effect.h"

extern s32 D_800814A0_abs __attribute__((section(".data")));
/* Starts the fade callback, releases the attachment, and sets global and child flags. */
void begin_selection_menu_teardown_and_fade(u8 *object)
{
    u8 *object_data = object + 0x20;
    s32 saved_value;
    struct S_8004FE78_a0 *attachment;
    ObjectNodeHeader *child;
    if (object != 0) {
        *((s32 *) (object_data + 0x08)) = 2;
        saved_value = *((s32 *) (object_data + 0x1C));
        attachment = *((void **) (object_data + 0x28));
        *((void (**)(void)) (object_data - 0x10)) = fade_effect_parts;
        selection_menu_saved_value = saved_value;
        destroy_animated_selection_menu(attachment);
        child = *((ObjectNodeHeader **) (object_data + 0xA0));
        D_800814A0_abs |= 0x8000;
        child->flags |= 0x8000;
        *((void **) (object_data + 0x28)) = 0;
    }
}

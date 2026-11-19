#include "common.h"
#include "engine/menu.h"
#include "slus.h"
#include "shared/menu_display.h"

/* Assign evenly spaced list values and increase spacing, switching callbacks at the limit. */
void animate_selection_menu_entry_spacing(AnimatedSelectionMenuBody *obj)
{
    s32 spacing = obj->spacing;
    s32 value;
    s32 index;
    AnimatedSelectionEntry **entry;
    MenuDisplayNode *display;
    if (spacing >= 0x21) {
        spacing = 0x20;
        obj->animate = noop_selection_menu_animation_idle;
        index = 0;
    } else {
        index = 0;
    }
    if (obj->count > 0) {
        value = 0x18;
        entry = (AnimatedSelectionEntry **)obj;
        do {
            display = entry[1]->display;
            display->block->fields.x = value;
            entry++;
            index++;
            value += spacing;
        }
        while (index < obj->count);
    }
    obj->spacing = spacing + ((0x28 - spacing) >> 3);
}

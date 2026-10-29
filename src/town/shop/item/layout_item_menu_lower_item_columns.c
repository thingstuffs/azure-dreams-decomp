#include "common.h"
#include "shared/item_menu.h"
#include "town/shop/item.h"

/* Arrange the ten objects in two columns of five. */
void layout_item_menu_lower_item_columns(ItemMenuPart **parts)
{
    s32 layoutIndex;

    for (layoutIndex = 16; layoutIndex < 26; layoutIndex++) {
        parts[layoutIndex]->position->x = ((layoutIndex - 16) / 5) * 128 + 96;
        parts[layoutIndex]->position->y = ((layoutIndex - 16) % 5) * 16 + 136;
    }
}

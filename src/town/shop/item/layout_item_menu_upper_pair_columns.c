#include "common.h"
#include "shared/item_menu.h"

// Arrange ten objects in two columns of five rows.
void layout_item_menu_upper_pair_columns(ItemMenuPart **parts)
{
    s32 layoutIndex;

    for (layoutIndex = 6; layoutIndex < 16; layoutIndex++) {
        parts[layoutIndex]->position->x = ((layoutIndex - 6) / 5) * 128 + -48;
        parts[layoutIndex]->position->y = ((layoutIndex - 6) % 5) * 16 + 22;
    }
}

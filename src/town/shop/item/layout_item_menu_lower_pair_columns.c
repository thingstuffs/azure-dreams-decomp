#include "common.h"
#include "shared/item_menu.h"

// Position ten objects in two columns of five rows.
void layout_item_menu_lower_pair_columns(ItemMenuPart **parts)
{
    s32 objectIndex;

    for (objectIndex = 26; objectIndex < 36; objectIndex++) {
        parts[objectIndex]->position->x = ((objectIndex - 26) / 5) * 128 + 88;
        parts[objectIndex]->position->y = ((objectIndex - 26) % 5) * 16 + 136;
    }
}

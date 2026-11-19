#include "common.h"
#include "engine/menu.h"

extern s32 card_boot_timeout_operation(void *a0);

/* Finds the resolved target ID's index, returning the count if absent or zero if empty. */
s32 find_resolved_selection_menu_index(AnimatedSelectionMenuBody *menu, void *object)
{
    s32 target_id = card_boot_timeout_operation(object);
    s32 id_count = menu->count;
    s32 id_index;

    for (id_index = 0; id_index < id_count; id_index++) {
        if (menu->entry_ids[id_index] == target_id) {
            return id_index;
        }
    }
    return id_index;
}

#include "common.h"
#include "engine/effect.h"
#include "engine/menu.h"
#include "slus.h"

extern int compare_selection_menu_entry_order(void *a0, void *a1);

/* Sorts and relinks the list entries, then runs the list update hooks. */
void reorder_selection_menu_entries(AnimatedSelectionMenuBody *list) {
    void *sorted[4];
    s32 index;
    void **dest;
    void **pair;

    index = 0;
    if (list->count > 0) {
        dest = sorted;
        do {
            AnimatedSelectionEntry *entry = list->entries[index];
            index++;
            *dest = entry;
            dest++;
        } while (index < list->count);
    }

    sort_with_comparator(sorted, list->count, 4, compare_selection_menu_entry_order);

    index = 0;
    if (list->count - 1 > 0) {
        pair = sorted;
        do {
            void *current = pair[0];
            void *next = pair[1];
            pair++;
            link_typed_list_node(current, next);
            index++;
        } while (index < list->count - 1);
    }

    interpolate_selection_menu_entry_coordinates(list);
    interpolate_selection_menu_entry_shade(list);
}

#include "common.h"
#include "engine/effect.h"
#include "engine/menu.h"
#include "slus.h"

typedef struct S_8004F884_arg {
    u8 pad00[4];
    void *arr[8];  /* array of pointers starting at offset 0x04; only entries 0..count-1 used */
    s32 count;     /* 0x24 */
} S_8004F884_arg;

extern int compare_selection_menu_entry_order(void *a0, void *a1);

/* Sorts and relinks the list entries, then runs the list update hooks. */
void reorder_and_interpolate_selection_menu_entries(S_8004F884_arg *list) {
    void *sorted[4];
    s32 index;
    void **dest;
    u8 *source;
    void **pair;

    index = 0;
    if (list->count > 0) {
        dest = sorted;
        source = (u8 *)list;
        do {
            void *entry = *(void **)(source + 4);
            source += 4;
            index++;
            *dest = entry;
            dest++;
        } while (index < list->count);
    }

    forward_selection_sort_request(sorted, list->count, 4, compare_selection_menu_entry_order);

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

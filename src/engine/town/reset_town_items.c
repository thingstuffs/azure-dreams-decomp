#include "common.h"

#include "common.h"
void clear_town_item_entries(void);                            /* extern */
void delete_all_town_items(void);                            /* extern */
void reset_entry_flags();                            /* extern */

/* Runs the three runtime routines in sequence. */
void reset_town_items(void) {
    reset_entry_flags();
    clear_town_item_entries();
    delete_all_town_items();
}

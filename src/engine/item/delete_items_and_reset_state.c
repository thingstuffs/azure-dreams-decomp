#include "common.h"

#include "common.h"

void clear_selected_scene_entry_flags(void);
void delete_all_town_items(void);
void reset_entry_flags();                            /* extern */

/* Runs the three Konami runtime routines in sequence. */
void delete_items_and_reset_state(void) {
    reset_entry_flags();
    delete_all_town_items();
    clear_selected_scene_entry_flags();
}

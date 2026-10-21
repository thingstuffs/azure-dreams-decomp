#include "common.h"

#include "common.h"
#include "engine/entity.h"
#include "engine/town.h"

/* Runs the three runtime routines in sequence. */
void reset_town_items(void) {
    reset_entry_flags();
    clear_town_item_entries();
    delete_all_town_items();
}

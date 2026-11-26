#include "common.h"
#include "m2c_compat.h"
#include "town.h"
#include "town/shop.h"


/*
 * Processes the entry lookup and expired resource countdowns, then updates paired entry brightness
 * for the same entry ID.
 */
void update_entry_resources_and_brightness(s32 entry_id) {
    apply_input_choice_value(entry_id);
    fade_choice_slot_colors(entry_id);
    set_paired_entry_brightness(entry_id);
}

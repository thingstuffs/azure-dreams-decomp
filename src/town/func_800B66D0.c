#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void process_valid_entry_lookup(s32);                            /* extern */
void set_paired_entry_brightness();                         /* extern */

/*
 * Processes the entry lookup and expired resource countdowns, then updates paired entry brightness
 * for the same entry ID.
 */
void run_entry_update_steps(s32 entry_id) {
    process_valid_entry_lookup(entry_id);
    process_resources_for_expired_slot_countdowns(entry_id);
    set_paired_entry_brightness(entry_id);
}

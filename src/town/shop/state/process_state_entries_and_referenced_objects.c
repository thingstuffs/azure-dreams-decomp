#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void process_entries_in_state_n_19_triggers_associated_sounds(void);                            /* extern */
void process_table_entries_referenced_objects_type_hex_13(void);                            /* extern */

/* Calls process_entries_in_state_n_19_triggers_associated_sounds followed by process_table_entries_referenced_objects_type_hex_13. */
void process_state_entries_and_referenced_objects(void) {
    process_entries_in_state_n_19_triggers_associated_sounds();
    process_table_entries_referenced_objects_type_hex_13();
}

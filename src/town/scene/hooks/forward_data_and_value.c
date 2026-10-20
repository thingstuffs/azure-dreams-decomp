#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */

extern void apply_selected_entry_values(void *, s32);
/* Pass data and its accompanying value to apply_selected_entry_values. */
void forward_data_and_value(void *data, s32 value) {
    apply_selected_entry_values(data, value);
}

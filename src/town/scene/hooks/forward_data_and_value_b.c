#include "common.h"
#include "town/scene/record_actions.h"
#include "town/scene/hooks.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Pass data and its accompanying value to apply_selected_entry_values. */
void forward_data_and_value_b(void *data, s32 value) {
    apply_selected_entry_values(data, value);
}

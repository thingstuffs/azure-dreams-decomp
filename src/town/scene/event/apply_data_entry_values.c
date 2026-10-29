#include "common.h"
#include "town/scene/entry_requests.h"
#include "town/scene/record_actions.h"
#include "town/scene/event.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Pass data and its accompanying value to apply_selected_entry_values. */
void apply_scene_entry_values(void *data, s32 value) {
    apply_selected_entry_values(data, value);
}

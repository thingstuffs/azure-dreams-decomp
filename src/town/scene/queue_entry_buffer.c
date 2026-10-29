#include "common.h"
#include "shared/town_event_buffer.h"
#include "town/scene/value_handler_modes_g00712.h"
#include "town/scene.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Calls call_value_handler_index_plus_4 with town_event_records. */
void queue_entry_buffer(void) {
    call_value_handler_index_plus_4(town_event_records);
}

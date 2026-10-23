#include "common.h"
#include "shared/town_event_buffer.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void call_value_handler_index_plus_4();                       /* extern */

/* Calls call_value_handler_index_plus_4 with town_event_records. */
void queue_entry_buffer(void) {
    call_value_handler_index_plus_4(town_event_records);
}

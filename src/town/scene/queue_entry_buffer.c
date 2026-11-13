#include "common.h"
#include "shared/town_event_buffer.h"
#include "town/scene/value_handler_modes_g00712.h"
#include "town/scene.h"


/* Calls process_lshop_entries_after_header with town_event_records. */
void queue_entry_buffer(void) {
    process_lshop_entries_after_header(town_event_records);
}

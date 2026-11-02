#include "common.h"
#include "shared/town_event_buffer.h"
#include "town/scene.h"
#include "town/shop.h"

/* Calls func_80018824 with town_event_records, 0x100. */
void clear_entry_buffer(void) {
    clear_bytes(town_event_records, 0x100);
}

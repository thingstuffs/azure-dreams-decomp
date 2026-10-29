#include "common.h"
#include "shared/town_event_buffer.h"
#include "town/scene.h"

s32 func_80018824(void *, s32);

/* Calls func_80018824 with town_event_records, 0x100. */
void clear_entry_buffer(void) {
    func_80018824(town_event_records, 0x100);
}

#include "common.h"
#include "shared/town_event_buffer.h"

s32 func_80018824(void *, s32);

/* Passes D_8001B218 to func_80018824 with parameter 0x100. */
void clear_entry_buffer(void) {
    func_80018824(town_event_records, 0x100);
}

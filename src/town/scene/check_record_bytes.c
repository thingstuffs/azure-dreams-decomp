#include "common.h"
#include "shared/town_event_buffer.h"
#include "town/scene.h"


/* Check for record bytes 13 and 4 with flag 0x20 set. */
s32 check_record_bytes_13(void) {
    if (town_event_records[5] != 13) {
        return 0;
    }
    if (town_event_records[4] == 4) {
        if (town_event_records[7] & 0x20) {
            return 1;
        }
    }
    return 0;
}

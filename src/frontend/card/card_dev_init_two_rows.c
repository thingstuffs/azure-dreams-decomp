#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"


/* Advance the two timed streams embedded in the card slot body. */
void card_dev_advance_slot_stream_pair(s32 record_addr) {
    advance_timed_tagged_stream_8004DCCC(record_addr + 4);
    advance_timed_tagged_stream_8004DCCC(record_addr + 0x10);
}

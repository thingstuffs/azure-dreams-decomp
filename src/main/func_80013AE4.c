#include "common.h"
#include "m2c_compat.h"

s32 advance_timed_tagged_stream();                         /* extern */

/* Process the embedded records at offsets 4 and 0x10. */
void advance_card_boot_stream_pair(s32 record_addr) {
    advance_timed_tagged_stream(record_addr + 4);
    advance_timed_tagged_stream(record_addr + 0x10);
}

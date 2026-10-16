#include "common.h"
#include "m2c_compat.h"

s32 advanceTimedTaggedStream();                         /* extern */

/* Process the embedded records at offsets 4 and 0x10. */
void advanceCardBootStreamPair(s32 record_addr) {
    advanceTimedTaggedStream(record_addr + 4);
    advanceTimedTaggedStream(record_addr + 0x10);
}

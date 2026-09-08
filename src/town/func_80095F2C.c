#include "common.h"

/* Return the linked record data when its type or data tag qualifies, or zero. */
s32 func_8009368C(void *record) {
    u8 *linked_record = *(u8 **)((u8 *)record + 0x2C);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

    if (linked_record != 0) {
        s32 type = 4;

        if ((linked_record[0x14] == type) || (linked_record[0x4D] == 0xD)) {
            return (s32)(linked_record + 0x4C);
        }
    }
    return 0;
}

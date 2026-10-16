#include "common.h"

s32 townShopTestIndexedFlag();                             /* extern */

/* Return 2 when the selected flag is set and flag 0x1F9 is clear. */
s32 townShopCheckSelectedEntryState(void) {
    s32 result;

    result = 0;
    if (townShopTestIndexedFlag(*(u16 *)0x80701DCE) != 0) {
        result = (townShopTestIndexedFlag(0x1F9U) == 0) * 2;
    }
    return result;
}

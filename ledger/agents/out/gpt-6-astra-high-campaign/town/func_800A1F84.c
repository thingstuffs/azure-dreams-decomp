#include "common.h"

extern s32 func_800B29A4(void *arg0);

/* get_item_chk: Return the item index, or -1 when it is at least 20. */
s32 func_8009F6E4(void) {
    s32 item_index;
    s32 invalid_index;

    item_index = func_800B29A4((void *)0x8001029C);
    invalid_index = -1;
    if (item_index >= 20) {
        return invalid_index;
    }
    return item_index;
}

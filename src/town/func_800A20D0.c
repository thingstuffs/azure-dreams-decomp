/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"

#ifndef NULL
#define NULL 0
#endif

void *func_8009F830(s32 item_kind, s32 item_type) {
    void **slots;
    void *item;
    s32 i;

    slots = (void **)0x80010000;
    for (i = 0; slots[167 + i] != NULL; i++) {
        item = slots[167 + i];
        if ((((u8 *)item)[0] == item_kind) && (((u8 *)item)[1] == item_type)) {
            return item;
        }
    }
    return NULL;
}

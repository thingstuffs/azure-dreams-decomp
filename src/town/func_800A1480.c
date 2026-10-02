#include "common.h"

#ifndef NULL
#define NULL 0
#endif

/* serch_item_kt: Find the first item matching the requested kind and type. */
void *serch_item_kt(s32 item_kind, s32 item_type) {
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

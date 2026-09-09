#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern void *D_8001029C;
__asm__(".set D_8001029C, 0x8001029C");

/* serch_item_kt: Find the first item matching the requested kind and type. */
void *serch_item_kt(s32 item_kind, s32 item_type) {
    void **item_slot;
    void *item;

    if (D_8001029C != NULL) {
        item_slot = &D_8001029C;
        do {
            item = *item_slot;
            if ((((u8 *)item)[0] == item_kind) && (((u8 *)item)[1] == item_type)) {
                return item;
            }
            item_slot += 1;
        } while (*item_slot != NULL);
    }
    return NULL;
}

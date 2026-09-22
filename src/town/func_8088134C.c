#include "common.h"

typedef void (*Callback)(s32);

extern s32 func_80700D74(u16 value);
extern u8 D_80700000[];

/* Scan the table for the first entry the query rejects and dispatch that index's callback. */
void func_8088134C(void) {
    s32 index = 0;
    s32 offset = 0;
    s32 result;

scan_entry:
    result = func_80700D74(*(u16 *)(D_80700000 + offset + 0x650));
    if (result != 0) {
        offset += 4;
        index++;
        goto scan_entry;
    }
    ((Callback *)(D_80700000 + 0x6DC))
        [((s8 *)(D_80700000 + 0x6E4))[index]](index);
}

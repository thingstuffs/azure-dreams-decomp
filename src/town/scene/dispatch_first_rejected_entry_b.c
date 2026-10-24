/* Relinked copy of town/dispatch_first_rejected_entry (dispatch_first_rejected_entry.c); retail differs only at relocation sites. */
#include "town/scene.h"

typedef s32 (*Callback)(s32);

extern s32 func_80000C6C(u16 value);
extern u8 D_000008D8[];

/* Scan the table for the first entry the query rejects and dispatch that index's callback. */
s32 dispatch_first_rejected_entry_b(void) {
    s32 index = 0;
    s32 offset = 0;

    while (func_80000C6C(*(u16 *)(D_000008D8 + offset + 0x650)) != 0) {
        offset += 4;
        index++;
    }
    return ((Callback *)(D_000008D8 + 0x6DC))
    [((s8 *)(D_000008D8 + 0x6E4))[index]](index);
}

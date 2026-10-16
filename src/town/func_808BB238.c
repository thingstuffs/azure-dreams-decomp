/* Relinked copy of town/func_8088134C (func_8088134C.c); retail differs only at relocation sites. */
#include "common.h"

typedef void (*Callback)(s32);

extern s32 func_80000C6C(u16 value);
extern u8 D_000008D8[];

/* Scan the table for the first entry the query rejects and dispatch that index's callback. */
void func_80000A38(void) {
    s32 index = 0;
    s32 offset = 0;

    while (func_80000C6C(*(u16 *)(D_000008D8 + offset + 0x650)) != 0) {
        offset += 4;
        index++;
    }
    ((Callback *)(D_000008D8 + 0x6DC))
    [((s8 *)(D_000008D8 + 0x6E4))[index]](index);
}

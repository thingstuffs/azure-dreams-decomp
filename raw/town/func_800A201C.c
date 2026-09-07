#include "common.h"

extern s32 func_800B2834();
extern u8 D_8008910C[];

u8 *func_8009F77C(s32 arg0, s32 arg1) {
    u8 values[4];
    u8 *entry;
    u8 *page;
    s32 index;
    s32 count;

    memcpy(values, D_8008910C, 4);
    count = values[func_800B2834()];
    index = 0;
    if (count <= -1) {
        goto no_match;
    }
    entry = (u8 *) 0x80011F80;
    page = (u8 *) 0x80010000;
loop:
    if ((page[0x1F80] != arg0) || (page[0x1F81] != arg1)) {
        entry += 4;
        index++;
        page += 4;
        if (count < index) {
            goto no_match;
        }
        goto loop;
    }
    return entry;
no_match:
    return 0;
}

/* MECHANISM: A four-byte local array forces the retail unaligned global-to-stack copy.
   The no-argument ABI call keeps both arguments in s0/s1; separate entry/page pointers reproduce
   the two-address loop, with a signed-width count preserving the pre-loop guard. */

#include "common.h"

extern u8 D_800D2644[];

void func_800B8A9C(void) {
    register s32 i ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *state;
    u8 *page;
    u8 *base;
    u8 value;
    s16 one;

    i = 0x42;
    state = D_800D2644;
    state += 0x840;
    do {
        *(s16 *)(state + 0xA) = 0;
        i--;
        state -= 0x20;
    } while (i >= 0);

    i = 0;
    base = D_800D2644;
    one = 1;
    page = (u8 *)0x80010000;
    do {
        value = page[0x33A4];
        if (value != 0) {
            u8 *record = (u8 *)((value << 5) + (u32)base);
            *(s16 *)(record + 0xA) = one;
        }
        i++;
        page += 2;
    } while (i < 0x22);
}

/* MECHANISM: The function is a frameless leaf with one reused signed loop counter.
   Separate base-plus-offset statements preserve the first loop's split address build;
   byte-scaled records and a held 0x80010000 page base preserve the retail widths. */

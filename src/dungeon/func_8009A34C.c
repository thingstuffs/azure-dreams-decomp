#include "common.h"


/* Clears the value at 0x80013718 and increments the counter at 0x8001371A. */
void func_8009FAAC(void) {
    u8 *page_base;
    u16 counter;

    page_base = (u8 *)0x80010000;
    counter = *(u16 *)(page_base + 0x371A);
    *(s16 *)(page_base + 0x3718) = 0;
    *(s16 *)(page_base + 0x371A) = (s16)(counter + 1);
}

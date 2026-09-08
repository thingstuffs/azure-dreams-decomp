#include "common.h"

/* Clears the table byte selected by the record's five-bit index. */
void func_800B2164(void *record) {
    u8 *page = (u8 *)0x80010000;
    page[((((u8 *)record)[3] & 0x1F) * 0x54) + 0x303] = 0;
}

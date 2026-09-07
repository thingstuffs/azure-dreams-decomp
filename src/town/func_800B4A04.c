#include "common.h"

void func_800B2164(void *arg0) {
    u8 *page = (u8 *)0x80010000;
    page[((((u8 *)arg0)[3] & 0x1F) * 0x54) + 0x303] = 0;
}

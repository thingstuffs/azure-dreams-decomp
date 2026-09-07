#include "common.h"

void func_80024160(void *arg0) {
    s32 i;
    u8 *ptr;
    s32 *out;

    ptr = arg0;
    i = 0;
    do {
        out = *(s32 **)(ptr + 0x25C);
        asm volatile("" : : "r"(out));
        *out = 0;
        i++;
        ptr += 4;
    } while (i < 10);
}

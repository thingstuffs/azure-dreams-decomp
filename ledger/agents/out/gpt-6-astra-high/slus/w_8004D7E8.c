#include "common.h"

extern void func_8004D75C(void *dst, void *src);

/* Copies a 0x44-byte record within D_80083178: F8 to B4, or 180 to 13C if selected. */
void func_8004D7E8(void *record_selector)
{
    char *base = (char *) &D_80083178;
    void *dst;
    void *src;

    if (record_selector == 0) {
        dst = base + 0xB4;
        src = base + 0xF8;
    } else {
        dst = base + 0x13C;
        src = base + 0x180;
    }
    func_8004D75C(dst, src);
}

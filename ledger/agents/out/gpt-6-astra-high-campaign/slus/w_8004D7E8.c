#include "common.h"

extern void func_8004D75C(void *dst, void *src);

/* Moves the selected 0x44-byte dispatch record back to its callback slot and clears the source callback. */
void func_8004D7E8(void *record_selector)
{
    char *dispatch_table = (char *) &D_80083178;
    void *dst;
    void *src;

    if (record_selector == 0) {
        dst = dispatch_table + 0xB4;
        src = dispatch_table + 0xF8;
    } else {
        dst = dispatch_table + 0x13C;
        src = dispatch_table + 0x180;
    }
    func_8004D75C(dst, src);
}

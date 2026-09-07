#include "common.h"

extern void func_8004D75C(void *dst, void *src);

/* Moves the selected dispatch table slot to its destination slot. */
void func_8004D7A8(int slot_selector)
{
    char *dispatch_table = (char *) &D_80083178;

    if (slot_selector == 0) {
        func_8004D75C(dispatch_table + 0xF8, dispatch_table + 0xB4);
    } else {
        func_8004D75C(dispatch_table + 0x180, dispatch_table + 0x13C);
    }
}

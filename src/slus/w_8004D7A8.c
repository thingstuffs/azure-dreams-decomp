#include "common.h"

/* func_8004D7A8 -- moves a slot of the D_80083178 dispatch table (B4/13C -> F8/180)
 * based on a0, via func_8004D75C. Uses the canonical game.h S_80083178. */
extern void func_8004D75C(void *dst, void *src);

void func_8004D7A8(int a0)
{
    char *base = (char *) &D_80083178;

    if (a0 == 0) {
        func_8004D75C(base + 0xF8, base + 0xB4);
    } else {
        func_8004D75C(base + 0x180, base + 0x13C);
    }
}

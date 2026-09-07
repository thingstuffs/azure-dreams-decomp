#include "common.h"

/* func_8004D7E8 -- copies a 0x44-byte record within D_80083178 (F8->B4 or 180->13C)
 * via func_8004D75C. Uses the canonical game.h S_80083178. */
extern void func_8004D75C(void *dst, void *src);

void func_8004D7E8(void *a0)
{
    char *base = (char *) &D_80083178;
    void *dst;
    void *src;

    if (a0 == 0) {
        dst = base + 0xB4;
        src = base + 0xF8;
    } else {
        dst = base + 0x13C;
        src = base + 0x180;
    }
    func_8004D75C(dst, src);
}

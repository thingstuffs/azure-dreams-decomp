#include "common.h"

/* Walks a nul-terminated byte string in place; for each char c, if D_800714B0[c] has bit 0x10 set, rewrites that char to (c + 0x31). Returns the original pointer. */
extern u8 D_800714B0[0x100];

u8 *func_8004E69C(u8 *arg0) {
    u8 *p = arg0;
    u8 *base;
    u8 c;

    if (*arg0 == 0) {
        return arg0;
    }
    base = D_800714B0;
    do {
        c = *p;
        if (base[c] & 0x10) {
            *p = c + 0x31;
        }
        p++;
    } while (*p != 0);
    return arg0;
}

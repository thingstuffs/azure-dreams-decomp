#include "common.h"

extern u8 D_80028020[];

/* Shared-page absolute-address idiom (cf. func_8003D468): D_800133A4 lives at
 * offset 0x33A4 within the 0x80010000 page, walked two bytes per iteration. The
 * byte read there indexes the D_80028020 lookup table. The lookup base is bound
 * to a live pointer first so it is materialized ahead of the page base, and the
 * index is added as the first operand so the sum lands in retail's addu order. */
s32 func_80025ECC(void) {
    s32 sum = 0;
    s32 i = 0;
    u8 *b = D_80028020;
    u8 *p = (u8 *)0x80010000;

    for (; i < 0x22; i++) {
        sum += *(u8 *)((s32)p[0x33A4] + (s32)b);
        p += 2;
    }
    return sum;
}

#include "common.h"

extern u8 D_80028020[];

/* Shared-page absolute-address idiom (cf. func_8003D468): D_800133A4 lives at
 * offset 0x33A4 within the 0x80010000 page, walked two bytes per iteration. The
 * byte read there indexes the D_80028020 lookup table. The lookup base is bound
 * to a live pointer first so it is materialized ahead of the page base, and the
 * index is added as the first operand so the sum lands in retail's addu order. */
/* Sums lookup values for 34 indices stored at two-byte intervals. */
s32 func_80025ECC(void) {
    s32 sum = 0;
    s32 entry_index = 0;
    u8 *lookup_table = D_80028020;
    u8 *page_cursor = (u8 *)0x80010000;

    for (; entry_index < 0x22; entry_index++) {
        sum += *(u8 *)((s32)page_cursor[0x33A4] + (s32)lookup_table);
        page_cursor += 2;
    }
    return sum;
}

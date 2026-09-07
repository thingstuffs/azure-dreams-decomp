#include "common.h"

/* arg0 is a sub-object pointer into a larger entity struct; the callback
 * function pointer lives at absolute offset 0x10 (== arg0 - 0x10), matching
 * the sibling install-callback idiom (w_8004ED5C.c, w_80048D60.c). Field
 * accesses stay offsets off arg0 directly (no separate base pointer) so the
 * compiler doesn't materialize an extra address-computation instruction. */
extern void func_800B3AE4(void *a0);
extern void func_800B3E30(void *a0);

void func_800B3E68(void *arg0)
{
    u8 *s0 = (u8 *)arg0;

    func_800B3AE4(arg0);
    if (*(u8 *)(s0 + 0x24) >= 0x7D) {
        *(u8 *)(s0 + 0x24) = 0x80;
        *(u8 *)(s0 + 0x25) = 0x80;
        *(u8 *)(s0 + 0x26) = 0x80;
        *(void (**)(void *))(s0 - 0x10) = func_800B3E30;
    }
    func_800B3E30(arg0);
}

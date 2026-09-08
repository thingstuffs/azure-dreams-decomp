#include "common.h"

/* arg0 is a sub-object pointer into a larger entity struct; the callback
 * function pointer lives at absolute offset 0x10 (== arg0 - 0x10), matching
 * the sibling install-callback idiom (w_8004ED5C.c, w_80048D60.c). Field
 * accesses stay offsets off arg0 directly (no separate base pointer) so the
 * compiler doesn't materialize an extra address-computation instruction. */
extern void func_800B3AE4(void *a0);
extern void func_800B3E30(void *a0);

/* Update the sub-object, clamp its color channels to neutral, and switch callbacks at the threshold. */
void func_800B3E68(void *sub_object)
{
    u8 *sub_object_bytes = (u8 *)sub_object;

    func_800B3AE4(sub_object);
    if (*(u8 *)(sub_object_bytes + 0x24) >= 0x7D) {
        *(u8 *)(sub_object_bytes + 0x24) = 0x80;
        *(u8 *)(sub_object_bytes + 0x25) = 0x80;
        *(u8 *)(sub_object_bytes + 0x26) = 0x80;
        *(void (**)(void *))(sub_object_bytes - 0x10) = func_800B3E30;
    }
    func_800B3E30(sub_object);
}

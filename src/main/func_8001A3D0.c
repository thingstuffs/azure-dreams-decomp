#include "common.h"

/* D_804094E8 is a dynamic/overlay-local flag word far outside this overlay's own
 * vram window and is not present in config/generated/slus_006.14.undefined_syms.txt,
 * so the generic ld -T script cannot resolve it; bind it explicitly at its real
 * linked address (narrow absolute symbol form).
 *
 * The target recomputes the address separately for the load (into v0) and the
 * store (into at) rather than caching one base register across the branch. A
 * single C reference to one symbol lets gcc's RTL CSE merge those into one
 * cached-register access, which does not match. Declaring a second alias bound
 * to the SAME real address (also via the narrow absolute-symbol form) for the
 * store gives gcc two textually distinct expressions, so it emits the two
 * separate lui/lw + lui/sw pairs the target uses. Both names resolve to the
 * identical linked address 0x804094E8; nothing is locally defined/faked. */
extern s32 D_804094E8[4];
extern s32 D_804094E8_2[4];
__asm__(".set D_804094E8, 0x804094E8");
__asm__(".set D_804094E8_2, 0x804094E8");

/* Clears the flag and returns 5 if it was set, or 0 otherwise. */
s32 func_8001A3D0(void) {
    s32 result;

    result = 0;
    if (D_804094E8[0] != 0) {
        result = 5;
        D_804094E8_2[0] = 0;
    }
    return result;
}

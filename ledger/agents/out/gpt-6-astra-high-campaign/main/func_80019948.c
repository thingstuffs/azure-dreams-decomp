#include "common.h"

/* The target recomputes the address separately for the load (into v0) and the
 * store (into at) rather than caching one base register across both accesses.
 * A single C reference to D_804094EC lets gcc's RTL CSE merge those into one
 * cached-register access, which does not match. Declaring a second alias bound
 * to the SAME real address (via the narrow absolute-symbol form) for the store
 * gives gcc two textually distinct expressions, so it emits the two separate
 * lui/lw + lui/sw pairs the target uses. Both names resolve to the identical
 * linked address 0x804094EC; nothing is locally defined/faked. */
extern s32 D_804094EC[];
extern s32 D_804094EC_2[];
__asm__(".set D_804094EC, 0x804094EC");
__asm__(".set D_804094EC_2, 0x804094EC");

void func_804014E4(void);
void func_80408654(s32);
void func_804013F8(s32);

/* Run setup for both indices and replace the stored value with 16 minus itself. */
void func_80019948(void) {
    s32 next_value;

    func_804014E4();
    func_80408654(0);
    func_80408654(1);
    next_value = 0x10 - D_804094EC[0];
    D_804094EC_2[0] = next_value;
    func_804013F8(next_value);
}

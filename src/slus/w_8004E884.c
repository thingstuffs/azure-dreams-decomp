#include "common.h"

extern void func_8004E264(void *a0, s32 a1);

/* Walk a linked array of 12-byte entries starting at a0, calling func_8004E264 on
 * each entry with a1, stopping when an entry's first byte has bit 0x80 set. */
void func_8004E884(u8 *a0, s32 a1)
{
    u8 *s0 = a0;
    s32 s1 = a1;

    if (s0 != 0) {
        do {
            func_8004E264(s0, s1);
            if (*s0 & 0x80) {
                break;
            }
            s0 = s0 + 0xC;
        } while (1);
    }
}

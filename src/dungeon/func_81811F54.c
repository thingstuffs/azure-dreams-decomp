#include "common.h"

#ifdef NON_MATCHING
#define LEGACY_ASM_KEEP(value) ((void)0)
#else
#define LEGACY_ASM_KEEP(value) \
    __asm__ __volatile__("" : "=r"(value) : "0"(value))
#endif

extern u8 D_800157D2[9];

s32 func_80026F54(s32 arg0, s32 arg1, s32 arg2)
{
    u8 *entry;
    register s32 occurrence ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 index;
    s32 result;

    occurrence = 0;
    LEGACY_ASM_KEEP(occurrence);
    index = occurrence;
    entry = D_800157D2;

loop:
    if ((entry[0] == arg0) && (entry[-1] == arg1)) {
        result = index;
        if (occurrence == arg2) {
            return result;
        }
        occurrence++;
    }

    index++;
    entry += 0x13;
    if (index < 0x40) {
        goto loop;
    }
    return -1;
}

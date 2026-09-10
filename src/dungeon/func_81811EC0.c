#include "common.h"

#if !defined(NON_MATCHING) && __GNUC__ < 3
#define ASM_KEEP(value) __asm__ __volatile__("" : "=r"(value) : "0"(value))
#else
#define KEEP_VALUE(value) ASM_KEEP(value)
#endif

extern u8 D_800157D2;

/* Return the index of the requested zero-based matching occurrence, or -1. */
s32 func_80026EC0(s32 target_value, s32 target_occurrence) {
    register s32 occurrence ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 result;
    s32 index;
    u8 *entry;

    occurrence = 0;
    ASM_KEEP(occurrence);
    index = occurrence;
    entry = &D_800157D2;
loop_1:
    if (*entry == target_value) {
        result = index;
        if (occurrence != target_occurrence) {
            occurrence += 1;
            goto block_4;
        }
    } else {
block_4:
        index += 1;
        entry += 0x13;
        if (index >= 0x40) {
            result = -1;
        } else {
            goto loop_1;
        }
    }
    return result;
}

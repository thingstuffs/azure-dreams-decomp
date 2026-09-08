#include "common.h"

#ifdef NON_MATCHING
#define LEGACY_ASM_KEEP(value) ((void)0)
#else
#define LEGACY_ASM_KEEP(value) \
    __asm__ __volatile__("" : "=r"(value) : "0"(value))
#endif

extern u8 D_800157D2[9];

/* Return the index of the requested zero-based occurrence matching both bytes, or -1. */
s32 func_80026F54(s32 target_value, s32 prefix_value, s32 target_occurrence)
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
    if ((entry[0] == target_value) && (entry[-1] == prefix_value)) {
        result = index;
        if (occurrence == target_occurrence) {
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

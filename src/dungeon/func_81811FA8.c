#include "common.h"

#define FIELD(ptr, type, offset) (*(type)((u8 *)(ptr) + (offset)))

#if !defined(NON_MATCHING) && __GNUC__ < 3
#define KEEP_INDEX(value) __asm__ __volatile__("" : "=r"(value) : "0"(value))
#else
#define KEEP_INDEX(value) ASM_KEEP(value)
#endif

s32 func_80026FA8(s32 arg0, s32 arg1, s32 arg2)
{
    register s32 index ASM_REG("$7") = arg2;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    void *entry;

    KEEP_INDEX(index);
    if (index < 0x40) {
        entry = (void *)0x80010000;
        entry += ((index * 4 + arg2) * 4) - arg2;
loop:
        if ((FIELD(entry, u8 *, 0x57D2) == arg0) &&
            (FIELD(entry, u8 *, 0x57D1) == arg1)) {
            return index;
        }
        index++;
        entry += 0x13;
        if (index < 0x40) {
            goto loop;
        }
    }
    return -1;
}

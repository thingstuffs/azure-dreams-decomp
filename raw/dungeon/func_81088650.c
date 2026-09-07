#include "common.h"

extern s32 rand(void);

s32 func_81088650(s32 arg0)
{
    s32 random;
    register s32 work ASM_REG("$16");
    register s32 value ASM_REG("$17");

    work = arg0;
    random = rand();
    value = (random % 9) + ((work << 16) >> 15);
    work = value;
    if (rand() & 1) {
        ASM_USE2(value, work);
        work = -value;
    }
    return (work << 16) >> 16;
}

/* MECHANISM: A pinned s0 work web carries arg0 through the first call, then the result.
   Pinned s1 preserves the unnegated value across the second call; branch-local
   ASM_USE2 prevents coalescing and yields the exact sll/negu/sll merge. */

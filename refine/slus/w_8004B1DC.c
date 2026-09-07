#include "common.h"

extern void func_8004B1A4(u16 *a0);

/* Call func_8004B1A4 on each non-null entry, then clear its pointer. */
void func_8004B1DC(u16 **entries, s32 count)
{
    s32 index;

    for (index = 0; index < count; index++) {
        if (entries[index] != 0) {
            func_8004B1A4(entries[index]);
            entries[index] = 0;
        }
    }
}

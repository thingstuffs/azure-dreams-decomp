#include "common.h"

#include "common.h"

extern s8 D_8006B1EC[];

/* Returns the index of a value in the sentinel-terminated table, or -1 if absent. */
u32 func_8003C5A4(s32 value)
{
    s32 index;

    for (index = 0; D_8006B1EC[index] != -1; index++) {
        if (D_8006B1EC[index] == value) {
            return index;
        }
    }

    return -1;
}

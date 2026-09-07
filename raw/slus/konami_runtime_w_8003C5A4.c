#include "common.h"

#include "common.h"

extern s8 D_8006B1EC[];

u32 func_8003C5A4(s32 value)
{
    s32 i;

    for (i = 0; D_8006B1EC[i] != -1; i++) {
        if (D_8006B1EC[i] == value) {
            return i;
        }
    }

    return -1;
}

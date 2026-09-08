#include "common.h"

extern u8 D_80700000[];
extern s32 D_80701DC8[3];

/* Return the value at 0x1FC0 selected by the current unsigned index at 0x1FC8. */
s32 func_80702610(void) {
    return *(s32 *)((u8 *)D_80700000 +
                    (*(u8 *)((u8 *)D_80700000 + D_80701DC8[0] + 0x1FC8) << 2) +
                    0x1FC0);
}

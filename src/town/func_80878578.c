#include "common.h"

extern u8 D_80700000[];
extern s32 D_80701DC8[3];

/* Return the value at 0x1F98 selected by the current signed index at 0x1FA4. */
s32 func_80702578(void) {
    return *(s32 *)((u8 *)D_80700000 +
                    (*(s8 *)((u8 *)D_80700000 + D_80701DC8[0] + 0x1FA4) << 2) +
                    0x1F98);
}

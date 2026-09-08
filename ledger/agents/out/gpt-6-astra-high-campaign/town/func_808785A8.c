#include "common.h"

extern u8 D_80700000[];
extern s32 D_80701DC8[3];

/* Return the value at 0x1FA8 selected by the current signed index at 0x1FB4. */
s32 func_807025A8(void) {
    return *(s32 *)((u8 *)D_80700000 +
                    (*(s8 *)((u8 *)D_80700000 + D_80701DC8[0] + 0x1FB4) << 2) +
                    0x1FA8);
}

#include "common.h"

extern u8 D_80700000[];
extern s32 D_80701DC8[3];

/* Return the table value indexed by the current signed byte entry. */
s32 func_80702548(void) {
    return *(s32 *)((u8 *)D_80700000 +
                    (*(s8 *)((u8 *)D_80700000 + D_80701DC8[0] + 0x1F94) << 2) +
                    0x1F88);
}

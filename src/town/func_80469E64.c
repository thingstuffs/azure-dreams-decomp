#include "common.h"

extern s32 D_80017F94[];
extern s32 D_80017FB4[];
extern u8 *D_8001E950;

extern void func_8001E578(s32 id);

/* Return the indexed value from the mode-selected table, signaling mode 1. */
s32 func_8001AE64(s32 unused_0, s32 unused_1, s32 mode)
{
    if (mode == 1) {
        func_8001E578(0x400);
        return D_80017F94[D_8001E950[3]];
    }
    return D_80017FB4[D_8001E950[3]];
}

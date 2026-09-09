#include "common.h"
#include "m2c_compat.h"

extern s32 D_80700000[];
extern s32 D_807014C8[];
extern s32 D_80701DC4[];
extern s32 D_80701DC8[];

extern void func_80702180(s32 index, s32 arg1);

/* Returns the current entry value or fallback address after calling func_80702180. */
s32 func_80702444(void) {
    s32 selected_value;
    if (D_80701DC8[0] == 0) {
        selected_value = *(s32 *)((u8 *)D_80700000 + (D_80701DC4[0] << 5) + 0x1E30);
    } else {
        selected_value = (s32)D_807014C8;
    }
    func_80702180(D_80701DC4[0], 1);
    return selected_value;
}

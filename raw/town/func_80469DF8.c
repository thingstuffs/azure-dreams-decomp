#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_8001A6D0();
extern s32 func_8001AE4C();
extern void *D_8001E950;

s32 func_8001ADF8(void *arg0, s32 arg1) {
    if (M2C_FIELD(D_8001E950, u8 *, 5) == 7) {
        M2C_FIELD(((arg1 * 0x10) + M2C_FIELD(arg0, s32 *, 0x10)), s32 *, 8) =
            func_8001A6D0(M2C_FIELD(D_8001E950, u8 *, 3));
        return 0;
    }
    func_8001AE4C(D_8001E950);
    return 1;
}

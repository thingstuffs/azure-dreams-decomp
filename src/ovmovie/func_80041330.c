#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80177C58();                            /* extern */
extern s32 *D_80178358;
extern s32 *D_8017835C;
extern s32 *D_80178360;
extern s32 *D_80178384;

void func_80041330(s32 arg0, u32 arg1) {
    func_80177C58();
    *D_80178384 |= 0x88;
    *D_80178360 = 0;
    *D_80178358 = arg0;
    *D_8017835C = ((arg1 >> 5) << 0x10) | 0x20;
    *D_80178360 = 0x01000200;
}

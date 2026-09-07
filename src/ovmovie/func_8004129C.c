#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80177BC0();                            /* extern */
extern s32 *D_8017834C;
extern s32 *D_80178350;
extern s32 *D_80178354;
extern s32 *D_8017837C;
extern s32 *D_80178384;

void func_8004129C(s32 *arg0, u32 arg1) {
    func_80177BC0();
    *D_80178384 |= 0x88;
    *D_8017834C = arg0 + 1;
    *D_80178350 = ((arg1 >> 5) << 0x10) | 0x20;
    *D_8017837C = *arg0;
    *D_80178354 = 0x01000201;
}

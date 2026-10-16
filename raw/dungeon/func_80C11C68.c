#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s32 func_800AC82C();                                /* extern */
s32 func_800AD9B4(void *, void *);                  /* extern */
extern M2C_UNK D_8014D014;
extern M2C_UNK D_8015020C;
extern M2C_UNK D_8015025C;

void func_8014F468(void *arg0, void *arg2, void *arg3) {
    if (func_800AC82C() != 0) {
        if ((func_800AD9B4(arg2, arg3) << 0x10) > 0) {
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8014D014;
        }
    } else if ((M2C_FIELD(arg2, M2C_UNK **, 0x2C) == &D_8015025C) && !(M2C_FIELD(arg3, s32 *, 0x1C) & 0x208)) {
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8015020C;
        func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8015020C), 0);
    }
}

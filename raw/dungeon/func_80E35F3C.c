#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_800478B8(void *);                      /* extern */
extern M2C_UNK D_80152460;

void func_8015173C(void *arg0, void *arg2) {
    s16 temp_v1;
    u16 temp_v0;

    M2C_FIELD(arg0, u16 *, 2) = (u16) (M2C_FIELD(arg0, u16 *, 2) + 1);
    func_800478B8(arg2);
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
        func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg0, s16 *, 4) + 0x100) >> 9) & 7) + &D_80152460), 0);
    }
    temp_v1 = M2C_FIELD(arg0, s16 *, 0);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if ((s16) M2C_FIELD(arg0, u16 *, 2) >= 8) {
            M2C_FIELD(arg0, s16 *, 0) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0) + 1);
            return;
        }
        return;
    case 1:
        temp_v0 = M2C_FIELD(arg2, u16 *, 0x1E) + 0x100;
        M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0;
        M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0;
        if (((u32) (temp_v0 & 0xFFFF) >= 0x1000U) || ((u16) M2C_FIELD(arg2, u16 *, 0x1E) >= 0x1000U)) {
            M2C_FIELD(arg2, u16 *, 0x1E) = 0x1000U;
            M2C_FIELD(arg2, u16 *, 0x1C) = 0x1000U;
            M2C_FIELD(arg0, s16 *, 0) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0) + 1);
        }
        break;
    }
}

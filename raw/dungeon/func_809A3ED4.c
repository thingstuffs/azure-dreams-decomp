#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
s32 func_80069EF8();                                /* extern */
extern M2C_UNK D_80175378;

void func_801756D4(void *arg0) {
    s16 temp_v0;
    s16 temp_v1;
    s16 var_s0;
    u16 temp_v0_2;
    u8 temp_v0_3;

    temp_v1 = M2C_FIELD(arg0, s16 *, 8);
    switch (temp_v1) {                              /* irregular */
    case 0:
        var_s0 = 0;
        do {
            M2C_FIELD((arg0 + var_s0), s8 *, 0x10) = (s8) (func_80069EF8() & 0x1F);
            temp_v0 = var_s0 + 1;
            var_s0 = temp_v0;
        } while (temp_v0 < 0x40);
        M2C_FIELD(arg0, u16 *, 0xC) = 0U;
        M2C_FIELD(arg0, s8 *, 0xE) = 0;
        M2C_FIELD(arg0, u8 *, 0x30) = 0U;
        M2C_FIELD(arg0, u8 *, 0xF) = 1U;
        func_8004491C(arg0 - 0x20, &D_80175378);
        M2C_FIELD(arg0, s16 *, 8) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 8) + 1);
        /* fallthrough */
    case 1:
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0xC) + 1;
        M2C_FIELD(arg0, u16 *, 0xC) = temp_v0_2;
        if ((s16) temp_v0_2 >= 0x11) {
            M2C_FIELD(arg0, u16 *, 0xC) = 0U;
        }
        temp_v0_3 = M2C_FIELD(arg0, u8 *, 0x30) + 1;
        M2C_FIELD(arg0, u8 *, 0x30) = temp_v0_3;
        if ((s8) temp_v0_3 >= 0x41) {
            M2C_FIELD(arg0, u8 *, 0x30) = 0x40U;
            M2C_FIELD(arg0, s8 *, 0xE) = 1;
        }
        if (M2C_FIELD(arg0, u8 *, 0xF) == 0) {
            M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
            *(s32 *)0x800814A0 |= 0x8000;
        }
        return;
    }
}

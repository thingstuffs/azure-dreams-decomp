#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A7A7C(s16, s16, s16, s32, void *);  /* extern */

void func_8014F770(void *arg0, void *arg1, void *arg2) {
    s32 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
            M2C_FIELD(arg0, u8 *, 0x9B) = 2U;
            return;
        }
        M2C_FIELD(arg0, u16 *, 0x96) = 0xCU;
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    case 1:
        M2C_FIELD(arg1, s16 *, 2) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 2) + ((s32) ((M2C_FIELD(arg0, s16 *, 0xA8) << 6) - (M2C_FIELD(arg1, s16 *, 2) - 0x20)) >> 1));
        temp_v0 = M2C_FIELD(arg1, s32 *, 0x14) + 0x30000;
        M2C_FIELD(arg1, s32 *, 0x14) = temp_v0;
        M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + temp_v0);
        M2C_FIELD(arg1, s16 *, 6) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 6) + ((s32) ((M2C_FIELD(arg0, s16 *, 0xAA) << 6) - (M2C_FIELD(arg1, s16 *, 6) - 0x20)) >> 1));
        if ((u16) M2C_FIELD(arg2, u16 *, 0x1C) < 0x1000U) {
            temp_v0_2 = M2C_FIELD(arg2, u16 *, 0x1E) + 0x50;
            M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0_2;
            M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0_2;
        }
        temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_3;
        if ((temp_v0_3 << 0x10) == 0) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            return;
        }
        return;
    case 2:
        func_800A7A7C(M2C_FIELD(arg0, s16 *, 0xA8), M2C_FIELD(arg0, s16 *, 0xAA), (s16) (M2C_FIELD(arg1, u16 *, 0xA) - 0x20), M2C_FIELD(arg2, s32 *, 8), arg0 + 0x48);
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
        break;
    }
}

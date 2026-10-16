#include "common.h"
#include "m2c_compat.h"

void func_801503E8(void *arg0, void *arg1, void *arg2) {
    u16 temp_v0;
    u16 temp_v0_2;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) (M2C_FIELD(arg0, u16 *, 0x96) - 1);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
            M2C_FIELD(arg0, u8 *, 0x9B) = 3U;
            return;
        }
        M2C_FIELD(arg0, u16 *, 0x96) = 3U;
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    case 1:
        temp_v0 = M2C_FIELD(arg2, u16 *, 0x1E) - 0x50;
        M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0;
        M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0;
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) < 0) {
            M2C_FIELD(arg0, u16 *, 0x96) = 2U;
block_14:
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            return;
        }
        return;
    case 2:
        M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + 0x28000);
        temp_v0_2 = M2C_FIELD(arg2, u16 *, 0x1E) - 0x80;
        M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0_2;
        M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0_2;
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) < 0) {
            goto block_14;
        }
        break;
    case 3:
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
        break;
    }
}

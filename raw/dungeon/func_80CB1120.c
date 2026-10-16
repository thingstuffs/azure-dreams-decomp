#include "common.h"
#include "m2c_compat.h"

void func_80152920(void *arg0, void *arg2) {
    s16 temp_v1;
    s32 temp_lo;
    u8 temp_v0;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0x1C);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg2, u16 *, 0x1C) = (u16) (M2C_FIELD(arg2, u16 *, 0x1C) + 0x258);
        M2C_FIELD(arg2, u16 *, 0x1E) = (u16) (M2C_FIELD(arg2, u16 *, 0x1E) + 0x258);
        temp_v0 = M2C_FIELD(arg2, u8 *, 0xE) + 0xC;
        M2C_FIELD(arg2, u8 *, 0xE) = temp_v0;
        M2C_FIELD(arg2, u8 *, 0xD) = temp_v0;
        M2C_FIELD(arg2, u8 *, 0xC) = temp_v0;
        if ((u16) M2C_FIELD(arg2, u16 *, 0x1C) >= 0x1770U) {
block_9:
            M2C_FIELD(arg0, s16 *, 0x1C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x1C) + 1);
        }
        break;
    case 1:
        M2C_FIELD(arg2, s16 *, 0x10) = 0x20;
        M2C_FIELD(arg2, u8 *, 0xE) = 0x50U;
        M2C_FIELD(arg2, u8 *, 0xD) = 0x50U;
        M2C_FIELD(arg2, u8 *, 0xC) = 0x50U;
        goto block_9;
    case 2:
        M2C_FIELD(arg2, s16 *, 0x10) = 0x60;
        M2C_FIELD(arg0, u16 *, 0x24) = (u16) (M2C_FIELD(arg0, u16 *, 0x24) - 1);
        M2C_FIELD(arg2, u16 *, 0x1C) = (u16) (M2C_FIELD(arg2, u16 *, 0x1C) - 0x190);
        M2C_FIELD(arg2, u16 *, 0x1E) = (u16) (M2C_FIELD(arg2, u16 *, 0x1E) - 0x190);
        temp_lo = (s32) ((s16) M2C_FIELD(arg0, u16 *, 0x24) << 7) / (s16) M2C_FIELD(arg0, s16 *, 0x26);
        M2C_FIELD(arg2, u8 *, 0xE) = (u8) temp_lo;
        M2C_FIELD(arg2, u8 *, 0xD) = (u8) temp_lo;
        M2C_FIELD(arg2, u8 *, 0xC) = (u8) temp_lo;
        break;
    }
    M2C_FIELD(arg2, u16 *, 0x1A) = (u16) (M2C_FIELD(arg2, u16 *, 0x1A) + 0x190);
    if ((s16) M2C_FIELD(arg0, u16 *, 0x24) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}

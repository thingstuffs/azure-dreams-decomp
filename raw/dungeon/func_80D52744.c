#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A4ACC(void *, s16, s32);            /* extern */
extern M2C_UNK D_80083460;

void func_80163F44(void *arg0, s32 arg4) {
    M2C_FIELD(arg0, u8 *, 0x71) = (u8) (M2C_FIELD(arg0, u8 *, 0x71) & 0x7F);
    if ((s16) arg4 != 2) {
        if (!(M2C_FIELD(&D_80083460, u16 *, 2) & 0x2000)) {
            if ((M2C_FIELD(&D_80083460, s32 *, 0xC) != arg0) && ((M2C_FIELD(&D_80083460, s32 *, 0xC) != 0) || (M2C_FIELD(&D_80083460, s32 *, 0x10) != 0) || (M2C_FIELD(&D_80083460, u16 *, 2) & 8))) {
                M2C_FIELD(arg0, s8 *, 0x9A) = 0xE;
                return;
            }
            goto block_11;
        }
        goto block_9;
    }
    if ((M2C_FIELD(&D_80083460, u16 *, 2) & 0x2000) || (M2C_FIELD(&D_80083460, s16 *, 0xA) != 0)) {
block_9:
        M2C_FIELD(arg0, s8 *, 0x9A) = 0xE;
        return;
    }
    M2C_FIELD(&D_80083460, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(&D_80083460, s16 *, 0xA) + 1);
block_11:
    if ((s16) arg4 == 0) {
        M2C_FIELD(&D_80083460, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(&D_80083460, s16 *, 0xA) + 1);
    }
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    M2C_FIELD(arg0, s8 *, 0x9A) = 0x19;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    M2C_FIELD(arg0, s16 *, 0x96) = 0;
    M2C_FIELD(arg0, s8 *, 0xB3) = 0;
    M2C_FIELD(arg0, s8 *, 0xB1) = 0;
    M2C_FIELD(arg0, s8 *, 0xB2) = 0;
    M2C_FIELD(arg0, s8 *, 0xB4) = (s8) arg4;
    if ((s16) arg4 == 0) {
        func_800A4ACC(arg0, (s16) arg4, arg4);
        M2C_FIELD(arg0, u8 *, 0x6D) = (u8) (M2C_FIELD(arg0, u8 *, 0x6D) - 1);
    }
}

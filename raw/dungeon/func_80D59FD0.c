#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s32 func_800A05A4(void *, u8, u8, s16, s32);        /* extern */
s32 func_800A2B5C(void *);                          /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
s32 func_800A6D30();                                /* extern */
M2C_UNK func_800C77D0(void *, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
extern M2C_UNK D_8006DE24;
extern M2C_UNK D_80083460;

void func_801537D0(void *arg0, M2C_UNK arg1, void *arg2, s32 arg3, s32 arg4) {
    s32 temp_v0;
    s32 var_s1;
    void *temp_a0;
    void *temp_t0;

    var_s1 = 0;
    M2C_FIELD(arg0, u8 *, 0x71) = (u8) (M2C_FIELD(arg0, u8 *, 0x71) & 0x7F);
    if (M2C_FIELD(arg0, s32 *, 0x1C) & 0x2000) {
        if ((M2C_FIELD(arg0, u16 *, 0x46) & 0x3FFF) >= 5) {
            var_s1 = 1;
            if (M2C_FIELD(*(void **)0x800E3D7C, u16 *, 0xA6) == 2) {
                M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
            }
            temp_a0 = *(void **)0x800E3D7C;
            if (((M2C_FIELD(temp_a0, s32 *, 0x98) & 0x3000) == 0x2000) && (M2C_FIELD(temp_a0, u16 *, 0xA6) != 1)) {
                M2C_FIELD(temp_a0, u16 *, 0xA6) = 1U;
                M2C_FIELD(temp_a0, s32 *, 0x98) = (s16) ((u16) M2C_FIELD(temp_a0, s32 *, 0x98) | 0x1000);
                M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) + 1);
                goto block_12;
            }
            func_800A4ACC(arg0);
            M2C_FIELD(arg0, u8 *, 0x6D) = (u8) (M2C_FIELD(arg0, u8 *, 0x6D) - 1);
            M2C_FIELD(arg0, s32 *, 0x8C) = arg4;
            return;
        }
        goto block_9;
    }
block_9:
    if (!(*(u16 *)0x80083462 & 8) && ((func_800A2B5C(arg0) << 0x10) == 0)) {
        func_800C77D0(arg0 - 0x20, arg1, 8, 0x300);
        if ((func_800A2B5C(arg0) << 0x10) == 0) {
block_12:
            if (var_s1 == 0) {
                if (M2C_FIELD(arg0, s32 *, 0x1C) & 0x400) {
                    temp_v0 = M2C_FIELD(arg0, s32 *, 0x14);
                    if (temp_v0 >= 0) {
                        M2C_FIELD(arg0, s32 *, 0x14) = (s32) (temp_v0 | 0x80000000);
                        M2C_FIELD(arg0, u16 *, 0x2A) = (u16) (M2C_FIELD(arg0, u16 *, 0x2A) + ((func_800A6D30() & 7) << 9));
                    }
                }
                if (!(M2C_FIELD(arg0, u16 *, 0x46) & 0x4000)) {
                    temp_t0 = (M2C_FIELD((arg0 + (((M2C_FIELD(arg0, u16 *, 0x46) & 0x3FFF) - 1) * 3)), u8 *, 8) * 0x14) + &D_8006DE24;
                    if (M2C_FIELD(temp_t0, u8 *, 0x12) == 2) {
                        M2C_FIELD(arg0, s32 *, 0x60) = func_800A05A4(arg0, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16) M2C_FIELD(arg0, u16 *, 0x2A), (s32) M2C_FIELD(temp_t0, u8 *, 0x13));
                    }
                }
            }
            M2C_FIELD(arg0, s8 *, 0x9A) = 0x12;
            M2C_FIELD(arg0, s8 *, 0x9B) = 0;
            M2C_FIELD(arg0, s32 *, 0x8C) = 0;
            if (arg3 != 0) {
                M2C_FIELD(arg2, s32 *, 0x2C) = arg3;
                func_80047784(arg2, *(arg3 + (((s32) (*(s16 *)0x80083228 + (s16) M2C_FIELD(arg0, u16 *, 0x2A) + 0x100) >> 9) & 7)), 0);
            }
            M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) + 1);
        }
    }
}

#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s32 func_800990FC();                                /* extern */
s32 func_80099194(M2C_UNK *, s32);                  /* extern */
M2C_UNK func_80099290(s32);                         /* extern */
s32 func_80099734(void *, s32);                     /* extern */
M2C_UNK func_8009C12C(void *, void *, s16, M2C_UNK); /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800A5720(s32);                         /* extern */
M2C_UNK func_800AD594(void *, M2C_UNK);             /* extern */
extern M2C_UNK D_8015E854;
extern M2C_UNK D_8015E874;
extern M2C_UNK D_8015EEA8;
extern M2C_UNK D_80162090;
extern M2C_UNK D_80162098;
extern M2C_UNK D_801620A0;

void func_80161C20(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK *var_a0;
    s32 temp_s1;
    s32 temp_v1_2;
    s32 var_v0;
    s32 var_v0_2;
    u16 temp_v0;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_s1 = func_800990FC();
        if (((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 9) & 1) {
            var_v0 = func_80099734(arg3, temp_s1);
            var_a0 = &D_8015E854;
        } else {
            var_v0 = func_80099734(arg3, temp_s1);
            var_a0 = &D_8015E874;
        }
        func_80099290(func_80099194(var_a0, var_v0));
        func_800A5720(temp_s1);
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
            M2C_FIELD(arg0, u8 *, 0x9B) = 3U;
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x6000);
            func_8009C12C(arg3, arg2, (s16) M2C_FIELD(arg3, u16 *, 0x2A), 1);
            return;
        }
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80162090;
        func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80162090), 0);
        M2C_FIELD(arg0, s32 *, 0x90) = 0;
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
        M2C_FIELD(arg1, s32 *, 0x14) = 0xFFF00000;
block_20:
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        return;
    case 1:
        temp_v1_2 = M2C_FIELD(arg1, s32 *, 0x14) + 0x20000;
        M2C_FIELD(arg1, s32 *, 0x14) = temp_v1_2;
        M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) + temp_v1_2);
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80162098;
            func_80047784(arg2, *((((s32) (*(void *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80162098), 0);
            M2C_FIELD(arg0, u16 *, 0x96) = 8U;
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            return;
        }
        return;
    case 2:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
        if (((temp_v0 << 0x10) == 0) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            func_8009C12C(arg3, arg2, (s16) M2C_FIELD(arg3, u16 *, 0x2A), 1);
        }
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_801620A0;
            func_80047784(arg2, *((((s32) (*(void *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_801620A0), 0);
            goto block_20;
        }
        break;
    case 3:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_800AD594(arg3, 0x1000);
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8015EEA8;
            *(s32 *)0x8008346C = 0;
            func_800A4ACC(arg3);
            if (M2C_FIELD(arg0, u16 *, 0x98) & 0x4000) {
                var_v0_2 = M2C_FIELD(arg3, s32 *, 0x1C) | 0x1000;
            } else {
                var_v0_2 = M2C_FIELD(arg3, s32 *, 0x1C) & ~0x1000;
            }
            M2C_FIELD(arg3, s32 *, 0x1C) = var_v0_2;
            M2C_FIELD(arg3, u8 *, 3) = (u8) M2C_FIELD(arg0, u8 *, 0xAC);
            if (M2C_FIELD(arg3, s8 *, 0x6D) == 0) {
                M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
                return;
            }
            *(void **)0x800E3DE8 = arg3 - 0x20;
        }
        break;
    }
}

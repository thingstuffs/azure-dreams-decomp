#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_800A2B04(void *, u8, u8);              /* extern */
M2C_UNK func_800AAA54(void *, void *, void *, M2C_UNK *); /* extern */
M2C_UNK func_800AD4D0(void *);                      /* extern */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_80083460;
extern M2C_UNK D_8015F760;
extern M2C_UNK D_80162E88;
extern M2C_UNK D_80162E98;
extern M2C_UNK D_80162ED8;

void func_80161B4C(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 temp_a0;
    s16 temp_v0;
    u16 temp_v0_2;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_800AD4D0(arg3);
        M2C_FIELD(arg0, s16 *, 0x96) = 4;
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        if (M2C_FIELD(arg3, u8 *, 0x28) != 0) {
            if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
                M2C_FIELD(arg0, s16 *, 0x96) = 0;
                M2C_FIELD(arg0, u8 *, 0x9B) = 3U;
                return;
            }
            return;
        }
block_15:
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800AAA54(arg0, arg1, arg2, &D_80162ED8);
        return;
    case 1:
        temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
        M2C_FIELD(arg0, s16 *, 0x96) = temp_v0;
        if (temp_v0 > 0) {
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (*((((u16) M2C_FIELD(arg3, u16 *, 0x6A) >> 8) & 0xE) + &D_8006CCD8) << 0x13);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (*((((u16) M2C_FIELD(arg3, u16 *, 0x6A) >> 8) & 0xE) + &D_8006CCE8) << 0x13);
            return;
        }
        if (temp_v0 == 0) {
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (*((((u16) M2C_FIELD(arg3, u16 *, 0x6A) >> 8) & 0xE) + &D_8006CCD8) << 0x12);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (*((((u16) M2C_FIELD(arg3, u16 *, 0x6A) >> 8) & 0xE) + &D_8006CCE8) << 0x12);
            M2C_FIELD(arg0, s16 *, 0x96) = 6;
block_20:
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            return;
        }
        break;
    case 2:
        if (M2C_FIELD(arg3, u8 *, 0x28) == 0) {
            goto block_15;
        }
        temp_a0 = M2C_FIELD(arg0, s16 *, 0x96);
        if (temp_a0 != 0) {
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (((M2C_FIELD(arg2, u8 *, 0x24) << 6) - (M2C_FIELD(arg1, s16 *, 2) - 0x20)) << 0x10) / temp_a0);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (((M2C_FIELD(arg2, u8 *, 0x25) << 6) - (M2C_FIELD(arg1, s16 *, 6) - 0x20)) << 0x10) / (s16) M2C_FIELD(arg0, s16 *, 0x96));
        }
        temp_v0_2 = (u16) M2C_FIELD(arg0, s16 *, 0x96);
        M2C_FIELD(arg0, s16 *, 0x96) = (s16) (temp_v0_2 - 1);
        if ((temp_v0_2 << 0x10) <= 0) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            goto block_20;
        }
        break;
    case 3:
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
        if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == &D_80162E98) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80162E88;
            func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80162E88), 0);
        }
        if (M2C_FIELD(&D_80083460, s32 *, 0x10) == (arg3 - 0x20)) {
            M2C_FIELD(&D_80083460, s32 *, 0x10) = (s32) (M2C_FIELD(&D_80083460, s32 *, 0x10) & 0x7FFFFFFF);
        }
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8015F760;
        break;
    }
}

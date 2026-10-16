#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s16 func_800A0818(u8, u8, u8, u8, M2C_UNK *);       /* extern */
M2C_UNK func_800A2B04(void *, u8, u8);              /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800A9A04(void *);                      /* extern */
M2C_UNK func_800AD594(void *, M2C_UNK);             /* extern */
s32 func_800AD9B4(void *, void *);                  /* extern */
extern M2C_UNK D_80082E80;
extern M2C_UNK D_80083460;
extern M2C_UNK D_80158E7C;
extern M2C_UNK D_8015CD6C;
extern M2C_UNK D_8015CD74;

void func_8015A29C(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK sp18;
    s16 temp_a0;
    s16 temp_v0;
    s32 temp_v1_2;
    u16 temp_v1_3;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8015CD6C;
            func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8015CD6C), 0);
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
            M2C_FIELD(arg1, s32 *, 0x14) = 0xFFEE0000;
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xF7FFFFFF);
            M2C_FIELD(arg0, s32 *, 0xA8) = 0;
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        case 1:
            temp_a0 = M2C_FIELD(arg0, s16 *, 0x96);
            M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) - M2C_FIELD(arg0, s32 *, 0xA8));
            if (temp_a0 != 0) {
                M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (((M2C_FIELD(arg2, u8 *, 0x24) << 6) - (M2C_FIELD(arg1, s16 *, 2) - 0x20)) << 0x10) / temp_a0);
                M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (((M2C_FIELD(arg2, u8 *, 0x25) << 6) - (M2C_FIELD(arg1, s16 *, 6) - 0x20)) << 0x10) / (s16) M2C_FIELD(arg0, s16 *, 0x96));
                M2C_FIELD(arg0, s32 *, 0xA8) = (s32) (M2C_FIELD(arg0, s32 *, 0xA8) + M2C_FIELD(arg1, s32 *, 0x14));
                M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + 0x40000);
            }
            M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) + M2C_FIELD(arg0, s32 *, 0xA8));
            if (M2C_FIELD(arg0, s16 *, 0x96) < 2) {
                M2C_FIELD(arg0, s32 *, 0x90) = 0;
                M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
                M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x08000000);
                M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            }
        case 2:
            if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x08000000) {
                M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
                M2C_FIELD(arg1, s32 *, 0x14) = 0;
                M2C_FIELD(arg1, s32 *, 0x10) = 0;
                M2C_FIELD(arg1, s32 *, 0xC) = 0;
                func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
                M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8015CD74;
                func_80047784(arg2, *((((s32) (*(void *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8015CD74), 0);
                M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            }
        }
        break;
    }
    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
    M2C_FIELD(arg0, s16 *, 0x96) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);
        if (M2C_FIELD(&D_80083460, s16 *, 8) != 0) {
            M2C_FIELD(&D_80083460, s16 *, 8) = (s16) ((u16) M2C_FIELD(&D_80083460, s16 *, 8) - 1);
        }
        temp_v1_2 = M2C_FIELD(arg3, s32 *, 0x1C);
        if (temp_v1_2 & 0x2000) {
            temp_v1_3 = M2C_FIELD(arg3, u16 *, 0x46);
            if (temp_v1_3 & 0x8000) {
                M2C_FIELD(arg3, u16 *, 0x46) = (u16) (temp_v1_3 & 0x7FFF);
            }
        } else if (!(temp_v1_2 & 0x410) && (temp_v1_2 & 0x20000)) {
            M2C_FIELD(arg3, s16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(&D_80082E80, u8 *, 0x24), M2C_FIELD(&D_80082E80, u8 *, 0x25), &sp18);
        }
        if ((func_800AD9B4(arg2, arg3) << 0x10) > 0) {
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80158E7C;
            func_800A9A04(arg3);
        }
    }
}

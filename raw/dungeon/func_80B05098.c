#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_800A2B04(void *, u8, u8);              /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
M2C_UNK func_800AD594(void *, M2C_UNK, M2C_UNK *);  /* extern */
M2C_UNK func_8016242C(void *, s32, s32, s16);       /* extern */
M2C_UNK func_80162670(void *, s32, s32, s16);       /* extern */
extern M2C_UNK D_8015E854;
extern M2C_UNK D_8015F7F4;
extern M2C_UNK D_80163988;

void func_80162898(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK sp10;
    M2C_UNK sp14;
    M2C_UNK sp18;
    M2C_UNK sp1C;
    M2C_UNK sp20;
    M2C_UNK sp24;
    M2C_UNK sp28;
    M2C_UNK sp2C;
    u16 temp_v0;
    u8 temp_v1;
    void *temp_v0_2;
    void *temp_v0_3;

    sp10 = M2C_UNALIGNED32(M2C_FIELD(&D_8015E854, M2C_UNK *, 0));
    sp14 = M2C_UNALIGNED32(M2C_FIELD(&D_8015E854, M2C_UNK *, 4));
    sp18 = M2C_UNALIGNED32(M2C_FIELD(&D_8015E854, M2C_UNK *, 8));
    sp1C = M2C_UNALIGNED32(M2C_FIELD(&D_8015E854, M2C_UNK *, 0xC));
    sp20 = M2C_UNALIGNED32(M2C_FIELD(&D_8015E854, M2C_UNK *, 0x10));
    sp24 = M2C_UNALIGNED32(M2C_FIELD(&D_8015E854, M2C_UNK *, 0x14));
    sp28 = M2C_UNALIGNED32(M2C_FIELD(&D_8015E854, M2C_UNK *, 0x18));
    sp2C = M2C_UNALIGNED32(M2C_FIELD(&D_8015E854, M2C_UNK *, 0x1C));
    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        M2C_FIELD(arg0, u16 *, 0x96) = 0x14U;
block_23:
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        return;
    case 1:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
        if (((s16) temp_v0 == 0x11) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
            temp_v0_2 = &sp10 + (((u16) M2C_FIELD(arg3, s16 *, 0x2A) >> 7) & 0x1C);
            func_80162670(arg3, (M2C_FIELD(arg2, u8 *, 0x24) + M2C_FIELD(temp_v0_2, s16 *, 0)) & 0xFFFF, (M2C_FIELD(arg2, u8 *, 0x25) + (s16) M2C_FIELD(temp_v0_2, u16 *, 2)) & 0xFFFF, M2C_FIELD(arg1, s16 *, 0xA));
        }
        if (((s16) M2C_FIELD(arg0, u16 *, 0x96) == 0xA) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
            func_800A56E0(0x606);
        }
        if (((s16) M2C_FIELD(arg0, u16 *, 0x96) == 9) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            temp_v0_3 = &sp10 + (((u16) M2C_FIELD(arg3, s16 *, 0x2A) >> 7) & 0x1C);
            func_8016242C(arg3, (M2C_FIELD(arg2, u8 *, 0x24) + M2C_FIELD(temp_v0_3, s16 *, 0)) & 0xFFFF, (M2C_FIELD(arg2, u8 *, 0x25) + (s16) M2C_FIELD(temp_v0_3, u16 *, 2)) & 0xFFFF, M2C_FIELD(arg1, s16 *, 0xA));
        }
        if (((s16) M2C_FIELD(arg0, u16 *, 0x96) <= 0) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            goto block_23;
        }
        return;
    case 2:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_80163988) {
                M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80163988;
                M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
                func_80047784(arg2, *(M2C_FIELD(arg2, M2C_UNK **, 0x2C) + (((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7)), 0);
                goto block_23;
            }
        }
        break;
    case 3:
        func_800AD594(arg3, 0x400, &D_8015E854);
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8015F7F4;
        *(s32 *)0x8008346C = 0;
        M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
        break;
    }
}

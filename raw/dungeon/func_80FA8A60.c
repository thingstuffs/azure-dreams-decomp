#include "common.h"
#include "m2c_compat.h"

s32 func_8003DE58(s32, void *, u16 *, M2C_UNK);     /* extern */
void *func_8003FD64(M2C_UNK, M2C_UNK *);            /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
M2C_UNK func_800AD594(void *, M2C_UNK, M2C_UNK *);  /* extern */
M2C_UNK func_800C8150(s32, M2C_UNK, M2C_UNK);       /* extern */
extern M2C_UNK D_80083460;
extern M2C_UNK D_80083498;
extern M2C_UNK D_80152868;
extern M2C_UNK D_80152874;
extern M2C_UNK D_80153138;
extern M2C_UNK D_801565E0;
extern M2C_UNK D_80156688;
extern M2C_UNK D_80156ACC;
extern M2C_UNK D_80156B14;

void func_80156260(void *arg0, void *arg1, void *arg2, void *arg3) {
    u16 sp10;
    u16 sp12;
    u16 sp14;
    M2C_UNK sp18;
    M2C_UNK sp1C;
    s16 sp20;
    M2C_UNK sp28;
    M2C_UNK sp2C;
    s16 sp30;
    s16 temp_v0_2;
    s16 temp_v1_3;
    s32 temp_a0;
    s32 temp_a0_3;
    s32 temp_a0_4;
    u16 temp_v1_2;
    u8 temp_v1;
    void *temp_a0_2;
    void *temp_s0;
    void *temp_v0;

    sp18 = M2C_UNALIGNED32(M2C_FIELD(&D_80152868, M2C_UNK *, 0));
    sp1C = M2C_UNALIGNED32(M2C_FIELD(&D_80152868, M2C_UNK *, 4));
    sp20 = M2C_FIELD(&D_80152868, s16 *, 8);
    sp28 = M2C_UNALIGNED32(M2C_FIELD(&D_80152874, M2C_UNK *, 0));
    sp2C = M2C_UNALIGNED32(M2C_FIELD(&D_80152874, M2C_UNK *, 4));
    sp30 = M2C_FIELD(&D_80152874, s16 *, 8);
    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    M2C_FIELD(arg0, u16 *, 0xA0) = (u16) (M2C_FIELD(arg0, u16 *, 0xA0) - 1);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v1_2 = M2C_FIELD(arg2, u16 *, 0x14);
        if (temp_v1_2 & 0x8000) {
            temp_a0 = M2C_FIELD(arg3, s32 *, 0x60);
            if (temp_a0 != 0) {
                func_800C8150(temp_a0, 0x10, 0x10);
            }
            M2C_FIELD(arg0, u8 *, 0x9B) = 2U;
            return;
        }
        if (temp_v1_2 & 0x6000) {
            if (func_8003DE58(M2C_FIELD(arg2, s32 *, 8), arg2, &sp10, 0) == 0) {
                sp14 = 0;
                sp12 = 0;
                sp10 = 0;
            }
            temp_v0 = func_8003FD64(0x201, &D_80083498);
            if (temp_v0 != NULL) {
                func_8004491C(temp_v0, &D_80156688);
                M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_801565E0;
                temp_a0_2 = temp_v0 + 0x20;
                M2C_FIELD(temp_a0_2, s16 *, 0xC) = (s16) (M2C_FIELD(arg1, u16 *, 2) + sp10);
                M2C_FIELD(temp_a0_2, s16 *, 0xE) = (s16) (M2C_FIELD(arg1, u16 *, 6) + sp12);
                M2C_FIELD(temp_a0_2, s32 *, 0x58) = 0x80;
                M2C_FIELD(temp_a0_2, s16 *, 0x48) = 1;
                M2C_FIELD(temp_a0_2, s16 *, 0x10) = (s16) (M2C_FIELD(arg1, u16 *, 0xA) + sp14);
            }
            func_800A56E0(0x815);
            M2C_FIELD(arg0, s16 *, 0x96) = 0x1E;
block_27:
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            return;
        }
        return;
    case 1:
        temp_a0_3 = M2C_FIELD(arg3, s32 *, 0x60);
        if (temp_a0_3 != 0) {
            temp_v1_3 = M2C_FIELD(arg0, s16 *, 0x96);
            if (temp_v1_3 >= 0x12) {
                temp_s0 = temp_a0_3 - 0x20;
                if (temp_v1_3 < 0x17) {
                    M2C_FIELD(M2C_FIELD(temp_s0, void **, 0xC), u16 *, 0x1C) = (u16) M2C_FIELD((sp + (temp_v1_3 * 2)), u16 *, -0xC);
                    M2C_FIELD(M2C_FIELD(temp_s0, void **, 0xC), u16 *, 0x1E) = (u16) (&sp4[0])[M2C_FIELD(arg0, s16 *, 0x96)];
                }
            }
        }
        if (M2C_FIELD(arg0, s16 *, 0x96) == 0x14) {
            temp_a0_4 = M2C_FIELD(arg3, s32 *, 0x60);
            if (temp_a0_4 != 0) {
                func_800C8150(temp_a0_4, 0x10, 0x10);
            }
        }
        temp_v0_2 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
        M2C_FIELD(arg0, s16 *, 0x96) = temp_v0_2;
        if ((temp_v0_2 << 0x10) <= 0) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80156B14;
            func_80047784(arg2, *((((s32) (*(void *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80156B14), 0);
            goto block_27;
        }
        break;
    case 2:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_800AD594(arg3, 0x800, &D_80152874);
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80156ACC;
            func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80156ACC), 0);
            M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
            func_800A4ACC(arg3);
            M2C_FIELD(arg3, s8 *, 0x6D) = 0;
            M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80153138;
        }
        break;
    }
}

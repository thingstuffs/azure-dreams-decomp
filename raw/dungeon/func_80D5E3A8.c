#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64(M2C_UNK, void *);               /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
s32 func_800BCB04(u16, u16, s16);                   /* extern */
extern M2C_UNK D_80045C34;
extern M2C_UNK D_800E2438;
extern M2C_UNK D_800E2440;
extern M2C_UNK D_800E2488;
extern M2C_UNK D_80152CEC;
extern M2C_UNK D_80153A80;

void func_80157BA8(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 temp_a1;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u8 temp_v1;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        temp_a1 = func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20)) - M2C_FIELD(arg3, u16 *, 0x88);
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x92) + 0xC;
        if (((s16) M2C_FIELD(arg0, u16 *, 0x92) >= temp_a1) || (M2C_FIELD(arg0, u16 *, 0x92) = temp_v0, ((temp_a1 < (s16) temp_v0) != 0))) {
            M2C_FIELD(arg0, u16 *, 0x92) = (u16) temp_a1;
        }
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
            M2C_FIELD(arg0, u16 *, 0x92) = 0U;
        }
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_2;
        if (((s16) temp_v0_2 == 1) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            M2C_FIELD(arg0, s8 *, 0xB5) = 1;
            temp_v0_3 = func_8003FD64(0x12, arg0 - 0x20);
            if (temp_v0_3 != NULL) {
                M2C_FIELD(arg0, void **, 0xAC) = temp_v0_3;
                M2C_FIELD(temp_v0_3, M2C_UNK **, 0x10) = &D_80152CEC;
                func_8004491C(temp_v0_3, &D_80045C34);
                temp_v0_4 = temp_v0_3 + 0x20;
                M2C_FIELD(temp_v0_4, s16 *, 0x38) = 5;
                M2C_FIELD(temp_v0_4, void **, 0x40) = arg0;
                M2C_FIELD(temp_v0_4, void **, 0x44) = arg1;
                temp_a0 = M2C_FIELD(temp_v0_3, void **, 0xC);
                M2C_FIELD(temp_a0, s16 *, 0x10) = 0x40;
                M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x14) | 0xC);
                temp_v1_2 = M2C_FIELD(temp_v0_3, void **, 8);
                M2C_FIELD(temp_v1_2, u16 *, 2) = (u16) M2C_FIELD(arg1, u16 *, 2);
                M2C_FIELD(temp_v1_2, u16 *, 6) = (u16) M2C_FIELD(arg1, u16 *, 6);
                M2C_FIELD(temp_v1_2, u16 *, 0xA) = (u16) M2C_FIELD(arg3, u16 *, 0x88);
                temp_a0_2 = M2C_FIELD(temp_v0_3, void **, 0xC);
                M2C_FIELD(temp_a0_2, s16 *, 0x1E) = 0xA00;
                M2C_FIELD(temp_a0_2, s16 *, 0x1C) = 0xA00;
                M2C_FIELD(temp_a0_2, s8 *, 0xE) = 0;
                M2C_FIELD(temp_a0_2, s8 *, 0xD) = 0;
                M2C_FIELD(temp_a0_2, s8 *, 0xC) = 0;
                M2C_FIELD(temp_a0_2, M2C_UNK **, 8) = &D_800E2488;
            }
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x92) == 0) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_800E2438;
            func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_800E2438), 0);
            M2C_FIELD(arg0, u16 *, 0x96) = 2U;
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
                func_800A56E0(0x800);
                goto block_18;
            }
            goto block_19;
        }
block_18:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
        case 1:
block_19:
            temp_v0_5 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
            M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_5;
            if (((temp_v0_5 << 0x10) <= 0) || (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
                M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_800E2440;
                func_80047784(arg2, *((((s32) (*(void *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_800E2440), 0);
                M2C_FIELD(arg0, u16 *, 0x96) = 3U;
                M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            }
            if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
            case 2:
                temp_v0_6 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
                M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_6;
                if (((temp_v0_6 << 0x10) <= 0) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
                    M2C_FIELD(arg0, u16 *, 0x96) = 0x1EU;
                    M2C_FIELD(arg0, s16 *, 0xA8) = 0;
                    M2C_FIELD(arg0, s8 *, 0xB1) = 0;
                    M2C_FIELD(arg0, s8 *, 0xB2) = 0;
                    M2C_FIELD(arg0, s8 *, 0xB4) = 0;
                    M2C_FIELD(arg0, s8 *, 0xB3) = 0;
                    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
                    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
                    M2C_FIELD(arg2, s16 *, 6) = 0;
                    M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80153A80;
                    *(s32 *)0x8008346C = 0;
                    M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
                }
            }
        }
        return;
    }
}

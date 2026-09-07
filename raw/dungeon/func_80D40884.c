#include "common.h"

typedef s32 M2C_UNK;

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern M2C_UNK func_80042B68();
extern M2C_UNK func_80047784();
extern M2C_UNK func_800A2B04();
extern M2C_UNK func_800A56E0();
extern M2C_UNK func_800AA36C();
extern M2C_UNK func_801708B8();
extern void func_80176240(void) __attribute__((noreturn));
extern void func_801762E4(void) __attribute__((noreturn));

extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_800E23E0[];
extern u8 D_800E2448[];
extern u8 D_80171A80[];

void func_80176084(void *arg0, void *arg1, void *arg2, void *arg3) {
    u16 temp_v0;
    u16 temp_v0_2;
    u8 temp_v1;
    u8 temp_v1_2;
    register u32 one ASM_REG("$2");

    temp_v1 = FIELD(arg0, u8, 0x9B);
    if (temp_v1 != 0) {
        if (temp_v1 != 1) {
            return func_801762E4();
        }
        goto block_15;
    }
    temp_v1_2 = FIELD(arg0, u8, 0xB1);
    one = 1;
    if (temp_v1_2 != 0) {
        if (temp_v1_2 != one) {
            return func_80176240();
        }
        goto block_10;
    }
    FIELD(arg0, u8, 0xB1) = one;
    ASM_KEEP(one);
    FIELD(arg0, u16, 0x96) = 4U;
    FIELD(arg2, M2C_UNK *, 0x2C) = (M2C_UNK *)D_800E2448;
    func_80047784(arg2, D_800E2448[((s32)(D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7], 0);
    if ((FIELD(arg2, u16, 0x14) & 0x8000) ||
        (func_800A56E0(0x801), ((FIELD(arg2, u16, 0x14) & 0x8000) != 0))) {
block_10:
        temp_v0 = FIELD(arg0, u16, 0x96);
        FIELD(arg0, u16, 0x96) = (u16)(temp_v0 - 1);
        if (((temp_v0 << 0x10) <= 0) || (FIELD(arg2, u16, 0x14) & 0xE000)) {
            FIELD(arg1, s32, 0x14) = 0;
            FIELD(arg1, s32, 0x10) = 0;
            FIELD(arg1, s32, 0xC) = 0;
            func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
            FIELD(arg3, s32, 0x1C) |= 0x40000;
            FIELD(arg0, s8, 0xB5) = 0;
            FIELD(arg0, u16, 0x98) |= 8;
            FIELD(arg2, M2C_UNK *, 0x2C) = (M2C_UNK *)D_800E23E0;
            func_80047784(arg2, D_800E23E0[((s32)(D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7], 0);
            FIELD(arg0, u16, 0x96) = 5U;
            FIELD(arg0, u8, 0x9B)++;
            FIELD(arg0, u8, 0xB1)++;
            if (FIELD(arg0, u8, 0xB0) == 0) {
                func_801708B8(arg0, arg1, arg2);
            }
        }
        if (FIELD(arg2, u16, 0x14) & 0x8000) {
block_15:
            temp_v0_2 = FIELD(arg0, u16, 0x96);
            FIELD(arg0, u16, 0x96) = (u16)(temp_v0_2 - 1);
            if (((temp_v0_2 << 0x10) <= 0) || (FIELD(arg2, u16, 0x14) & 0xE000)) {
                FIELD(arg2, s16, 6) = 0;
                FIELD(arg0, M2C_UNK *, 0x8C) = (M2C_UNK *)D_80171A80;
                func_80042B68(arg3, 0x1B);
                if (FIELD(arg0, u8, 0xB4) == 0) {
                    u8 *global = (u8 *)&D_80083460;
                    FIELD(global, s32, 0xC) = 0;
                    FIELD(global, u16, 0xA)--;
                    FIELD(arg3, u16, 0x46) &= 0x7FFF;
                }
                func_800AA36C(arg0, arg1, arg2, arg3);
            }
        }
    }
}

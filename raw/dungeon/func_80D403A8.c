#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void *func_8003FD64();
extern void func_8004491C();
extern void func_80047784();
extern void func_800A56E0();
extern s32 func_800BCB04();

extern u8 D_80045C34[];
extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_800E2438[];
extern u8 D_800E2440[];
extern u8 D_800E2488[];
extern u8 D_80170CEC[];
extern u8 D_80171A80[];

void func_80175BA8(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 temp_a1;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_5;
    u16 temp_v0_6;
    s32 temp_v1;
    void *temp_a0;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v1_2;

    temp_v1 = FIELD(arg0, u8, 0x9B);
    switch (temp_v1) {
    case 0:
        goto block_0;
    case 1:
        goto block_21;
    case 2:
        goto block_25;
    default:
        goto block_done;
    }

block_0:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    temp_a1 = func_800BCB04(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                            (s16)(FIELD(arg3, u16, 0x88) - 0x20))
              - FIELD(arg3, u16, 0x88);
    if (FIELD(arg0, s16, 0x92) < temp_a1) {
        temp_v0 = FIELD(arg0, u16, 0x92) + 0xC;
        FIELD(arg0, u16, 0x92) = temp_v0;
        if (temp_a1 >= (s16)temp_v0) {
            goto block_after_92;
        }
    }
    FIELD(arg0, s16, 0x92) = temp_a1;
block_after_92:
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u16, 0x92) = 0;
    }
    temp_v0_2 = FIELD(arg0, u16, 0x96) + 1;
    FIELD(arg0, u16, 0x96) = temp_v0_2;
    if (((s16)temp_v0_2 == 1) || (FIELD(arg2, u16, 0x14) & 0x8000)) {
        FIELD(arg0, s8, 0xB5) = 1;
        temp_v0_3 = func_8003FD64(0x12, (u8 *)arg0 - 0x20);
        if (temp_v0_3 != NULL) {
            FIELD(arg0, void *, 0xAC) = temp_v0_3;
            FIELD(temp_v0_3, void *, 0x10) = D_80170CEC;
            func_8004491C(temp_v0_3, D_80045C34);
            temp_v0_4 = (u8 *)temp_v0_3 + 0x20;
            FIELD(temp_v0_4, s16, 0x38) = 5;
            FIELD(temp_v0_4, void *, 0x40) = arg0;
            FIELD(temp_v0_4, void *, 0x44) = arg1;
            temp_a0 = FIELD(temp_v0_3, void *, 0xC);
            FIELD(temp_a0, s16, 0x10) = 0x40;
            FIELD(temp_a0, u16, 0x14) |= 0xC;
            temp_v1_2 = FIELD(temp_v0_3, void *, 8);
            FIELD(temp_v1_2, u16, 2) = FIELD(arg1, u16, 2);
            FIELD(temp_v1_2, u16, 6) = FIELD(arg1, u16, 6);
            FIELD(temp_v1_2, u16, 0xA) = FIELD(arg3, u16, 0x88);
            temp_a0 = FIELD(temp_v0_3, void *, 0xC);
            FIELD(temp_a0, s16, 0x1E) = 0xA00;
            FIELD(temp_a0, s16, 0x1C) = 0xA00;
            FIELD(temp_a0, s8, 0xE) = 0;
            FIELD(temp_a0, s8, 0xD) = 0;
            FIELD(temp_a0, s8, 0xC) = 0;
            FIELD(temp_a0, void *, 8) = D_800E2488;
        }
    }
    if (FIELD(arg0, s16, 0x92) == 0) {
        FIELD(arg2, void *, 0x2C) = D_800E2438;
        func_80047784(arg2,
                      D_800E2438[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                      0);
        FIELD(arg0, u16, 0x96) = 2;
        FIELD(arg0, u8, 0x9B)++;
        if (!(FIELD(arg2, u16, 0x14) & 0x8000)) {
            func_800A56E0(0x800);
            goto block_20;
        }
        goto block_21;
    }
block_20:
    if (!(FIELD(arg2, u16, 0x14) & 0x8000)) {
        goto block_done;
    }

block_21:
    temp_v0_5 = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = temp_v0_5;
    if (((temp_v0_5 << 0x10) <= 0) || (FIELD(arg2, u16, 0x14) & 0xE000)) {
        FIELD(arg2, void *, 0x2C) = D_800E2440;
        func_80047784(arg2,
                      D_800E2440[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                      0);
        FIELD(arg0, u16, 0x96) = 3;
        FIELD(arg0, u8, 0x9B)++;
    }
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
block_25:
        temp_v0_6 = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = temp_v0_6;
        if (((temp_v0_6 << 0x10) <= 0) || (FIELD(arg2, u16, 0x14) & 0x8000)) {
            FIELD(arg0, u16, 0x96) = 0x1E;
            FIELD(arg0, s16, 0xA8) = 0;
            FIELD(arg0, s8, 0xB1) = 0;
            FIELD(arg0, s8, 0xB2) = 0;
            FIELD(arg0, s8, 0xB4) = 0;
            FIELD(arg0, s8, 0xB3) = 0;
            FIELD(arg0, u8, 0x9B)++;
            FIELD(arg0, u16, 0x98) &= 0xFFF7;
            FIELD(arg2, s16, 6) = 0;
            FIELD(arg0, void *, 0x8C) = D_80171A80;
            D_8008346C = 0;
            FIELD(arg3, u16, 0x46) &= 0x7FFF;
        }
    }
block_done:
    return;
}

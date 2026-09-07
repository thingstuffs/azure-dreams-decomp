#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} LocalVec;

typedef struct {
    void *sp10;
    s32 unused14;
    LocalVec sp18;
} LocalStack;

s16 func_8002458C();
s32 func_8003DB94();
void *func_8003FC64();
s32 func_8004491C();
s32 func_80069EF8();
s32 func_800A48F0();
extern s32 D_800246B0;
extern s16 D_8002992E;
extern s32 D_80045340;
extern s32 D_800814A0;
extern s32 D_80083460;
extern s32 D_800DE870;
extern s32 D_800E3D7C;

void func_800247C0(void *arg0, void *arg1)
{
    void *var_sp10;
    u16 var_x;
    s32 sp20;
    s16 temp_v0_5;
    s16 temp_v1_3;
    s16 var_s3;
    s32 temp_fp;
    s32 temp_s6;
    s32 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u32 temp_v1;
    u16 temp_v1_2;
    u16 temp_v1_4;
    void *temp_a0;
    void *temp_s0;
    void *temp_s1;
    void *temp_s2;
    u8 *global_base;

    D_8002992E = 1;
    var_x = (func_80069EF8() & 0x3F) - 0x20;
    temp_fp = (func_80069EF8() & 0x3F) - 0x20;
    temp_v0 = func_80069EF8();
    temp_s2 = FIELD(arg0, void *, 0x20);
    temp_a0 = FIELD(temp_s2, void *, 8);
    temp_s1 = FIELD(temp_s2, void *, 0xC);
    FIELD(arg1, s32, 0) = FIELD(temp_a0, s32, 0);
    FIELD(arg1, s32, 4) = FIELD(temp_a0, s32, 4);
    temp_s6 = (temp_v0 & 0x3F) - 0x20;
    FIELD(arg1, s32, 8) = FIELD(temp_a0, s32, 8);
    temp_v1 = FIELD(temp_s1, u16, 0x1C);
    temp_s2 += 0x20;
    var_sp10 = temp_s2;
    if (temp_v1 >= 0x801U) {
        temp_v0_2 = temp_v1 - 0x50;
        FIELD(temp_s1, u16, 0x1C) = temp_v0_2;
        if ((u32)(temp_v0_2 & 0xFFFF) < 0x800U) {
            FIELD(temp_s1, u16, 0x1C) = 0x800U;
        }
    }
    temp_v1_2 = FIELD(temp_s1, u16, 0x1E);
    if (temp_v1_2 >= 0x801U) {
        temp_v0_3 = temp_v1_2 - 0x50;
        FIELD(temp_s1, u16, 0x1E) = temp_v0_3;
        if ((u32)(temp_v0_3 & 0xFFFF) < 0x800U) {
            FIELD(temp_s1, u16, 0x1E) = 0x800U;
        }
    }
    if (FIELD(arg0, s16, 0x28) >= 0xB) {
        var_s3 = 0;
        for (; var_s3 < 4; var_s3++) {
            temp_s2 = func_8003FC64(0x212);
            if (temp_s2 == NULL) {
                continue;
            }
            temp_s0 = temp_s2 + 0x20;
            FIELD(temp_s0, s16, 0x28) = 0x14;
            FIELD(temp_s2, void *, 0x10) = &D_800246B0;
            func_8004491C(temp_s2, &D_80045340);
            temp_s1 = FIELD(temp_s2, void *, 0xC);
            FIELD(temp_s1, s16, 0x10) = 0x20;
            FIELD(temp_s1, u16, 0x14) |= 0xC;
            temp_a0 = FIELD(temp_s2, void *, 8);
            FIELD(temp_a0, s16, 2) =
                FIELD(arg1, u16, 2) + var_x;
            FIELD(FIELD(temp_s2, void *, 8), s16, 6) =
                FIELD(arg1, u16, 6) + temp_fp;
            FIELD(FIELD(temp_s2, void *, 8), s16, 0xA) =
                FIELD(arg1, u16, 0xA) + temp_s6 - 0x10;
            sp20 = 0 - ((s32)(var_x << 0x10) >> 7);
            FIELD(temp_s0, s32, 0x88) = sp20;
            FIELD(temp_s0, s32, 0x8C) =
                0 - ((s32)(temp_fp << 0x10) >> 7);
            FIELD(temp_s0, s32, 0x90) =
                0 - ((s32)(temp_s6 << 0x10) >> 7);
            temp_s1 = FIELD(temp_s2, void *, 0xC);
            FIELD(temp_s1, s16, 0x1E) = 0x1000;
            FIELD(temp_s1, s16, 0x1C) = 0x1000;
            temp_v1_3 = func_8002458C(3);
            FIELD(temp_s1, s8, 0xE) = 0;
            FIELD(temp_s1, s8, 0xD) = 0;
            FIELD(temp_s1, s8, 0xC) = 0;
            if (temp_v1_3 == 0) {
                FIELD(temp_s1, s8, 0xC) = 0x10;
            }
            if (temp_v1_3 == 1) {
                FIELD(temp_s1, s8, 0xD) = 0x10;
            }
            if (temp_v1_3 == 2) {
                FIELD(temp_s1, s8, 0xE) = 0x10;
            }
            FIELD(temp_s1, s16, 0x12) = 0x7DCF;
            FIELD(temp_s1, u16, 0x14) |= 0x100;
            func_8003DB94(temp_s1, &D_800DE870, 0);
        }
    }
    temp_v1_4 = FIELD(arg0, s16, 0x28);
    temp_v0_5 = temp_v1_4 - 1;
    FIELD(arg0, s16, 0x28) = temp_v0_5;
    if ((temp_v0_5 << 0x10) <= 0) {
        global_base = (u8 *)&D_80083460;
        FIELD(arg0, s16, 0x28) = temp_v1_4;
        if (FIELD(global_base, void *, 0x10) == NULL) {
            FIELD(global_base, void *, 0x10) = FIELD(arg0, void *, 0x20);
        }
        temp_s2 = FIELD(arg0, void *, 0x20);
        func_800A48F0(temp_s2 + 0x20, 0x18, 0x14);
        FIELD(var_sp10, s8, 0x28) = 0;
        temp_v0 = D_800E3D7C;
        FIELD(var_sp10, s16, 0x64) = -1;
        FIELD(var_sp10, s32, 0x60) = temp_v0;
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

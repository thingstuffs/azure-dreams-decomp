#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern void *func_8003FC64(s32);
extern s32 rand(void);
extern void func_800D4BD4(void *, void *, void *, s32);
extern s32 D_800814A0;
extern u8 D_80083460[];
extern u8 D_800D4CB0[];
extern u8 D_800DDC40[];

void func_800D4DE8(void *arg0, void *arg1, s32 arg2) {
    s32 var_s1;
    u16 temp_v0;
    u16 temp_v0_4;
    void *temp_a0;
    void *temp_s0;
    void *temp_v0_2;
    void *temp_v0_3;
    u8 *global;

    temp_a0 = FIELD(arg0, void *, 0x24);
    FIELD(arg1, s16, 2) =
        (s16)(FIELD(FIELD(temp_a0, void *, 8), u16, 2) +
              FIELD(arg0, u16, 0x3C));
    FIELD(arg1, s16, 6) =
        (s16)(FIELD(FIELD(temp_a0, void *, 8), u16, 6) +
              FIELD(arg0, u16, 0x3E));
    FIELD(arg1, s16, 0xA) =
        (s16)(FIELD(FIELD(temp_a0, void *, 8), u16, 0xA) +
              FIELD(arg0, u16, 0x40));
    temp_v0 = FIELD(arg0, u16, 0x16) + 1;
    FIELD(arg0, u16, 0x16) = temp_v0;
    if ((s16)temp_v0 < 0x14) {
        var_s1 = 0;
        do {
            temp_v0_2 = func_8003FC64(0x212);
            if (temp_v0_2 != NULL) {
                func_800D4BD4(temp_v0_2, arg0, arg1, arg2);
                temp_v0_3 = (u8 *)temp_v0_2 + 0x20;
                FIELD(temp_v0_3, s16, 0x1E) = 0xA;
                FIELD(temp_v0_3, s16, 0x20) = 0xA;
                FIELD(temp_v0_2, void *, 0x10) = D_800D4CB0;
                temp_s0 = FIELD(temp_v0_2, void *, 8);
                FIELD(temp_s0, s32, 0xC) =
                    ((rand() & 0x7FFF) - 0x4000) << 7;
                FIELD(temp_s0, s32, 0x10) =
                    ((rand() & 0x7FFF) - 0x4000) << 7;
                FIELD(temp_s0, s32, 0x14) =
                    ((rand() & 0x7FFF) - 0x4000) << 7;
                FIELD(temp_s0, u16, 0xA) =
                    FIELD(temp_s0, u16, 0xA) -
                    (D_800DDC40[FIELD(FIELD(arg0, void *, 0), u8, 0x13)] >> 1);
            }
            var_s1 += 1;
        } while (var_s1 < 4);
    }
    temp_v0_4 = FIELD(arg0, u16, 0x1E) - 1;
    FIELD(arg0, u16, 0x1E) = temp_v0_4;
    if ((temp_v0_4 << 0x10) <= 0) {
        FIELD(arg0, u16, -2) = FIELD(arg0, u16, -2) | 0x8000;
        D_800814A0 |= 0x8000;
        global = D_80083460;
        FIELD(global, u16, 0xA) = FIELD(global, u16, 0xA) - 1;
    }
}

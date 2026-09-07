#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

typedef struct {
    s32 f0;
    s32 f1;
    s32 f2;
    s32 f3;
    s32 f4;
    s32 f5;
} Copy6;

extern void *func_8003FC64(s32);
extern s32 func_8004491C(void *, void *);
extern s32 rand(void);
extern u8 D_80024044[9];
extern u8 D_80045340[9];
extern u8 D_800DE720[9];

s32 func_80024170(void *arg0, void *arg1)
{
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_v1;
    s32 var_v0;
    void *temp_s0;
    void *temp_s2;
    void *temp_v0;
    void *temp_v0_2;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != 0) {
        temp_s2 = temp_v0 + 0x20;
        FIELD(temp_v0, void *, 0x10) = D_80024044;
        FIELD(temp_v0, void *, 0x20) = arg0;
        FIELD(temp_s2, s16, 6) = 0;
        FIELD(temp_s2, u16, 8) = FIELD(arg0, u16, 0x12);
        temp_s0 = FIELD(temp_v0, void *, 0xC);
        FIELD(temp_s0, u8, 0xE) = 0x80;
        FIELD(temp_s0, u8, 0xD) = 0x80;
        FIELD(temp_s0, u8, 0xC) = 0x80;
        FIELD(temp_s0, void *, 8) = D_800DE720;
        FIELD(temp_s0, s16, 0x12) = 0x7E00;
        FIELD(temp_s0, u16, 0x14) |= 0x100;
        var_v0 = rand();
        temp_v1 = var_v0;
        if (temp_v1 < 0) {
            var_v0 = temp_v1 + 0xFFF;
        }
        FIELD(temp_s0, s16, 0x1A) = temp_v1 - ((var_v0 >> 0xC) << 0xC);
        FIELD(temp_s0, s16, 0x1E) = 0x400;
        FIELD(temp_s0, s16, 0x1C) = 0x400;
        func_8004491C(temp_v0, D_80045340);
        temp_v0_2 = FIELD(temp_v0, void *, 8);
        *(Copy6 *)temp_v0_2 = *(Copy6 *)arg1;
        temp_v1 = FIELD(temp_v0_2, s32, 8);
        FIELD(temp_s2, s32, 0xC) = temp_v1;
        return (s32)temp_v0;
    }
    return 0;
}

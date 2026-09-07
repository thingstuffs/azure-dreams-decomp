#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void *func_8003FC64(s32);
extern s32 rand(void);
extern void func_8003DB94(void *, void *, s32);
extern s32 func_80064584(s32);
extern s32 func_800644B8(s32);
extern void func_8004491C(void *, void *);

extern u8 D_800244A4[];
extern u8 D_80045340[];
extern u8 D_80083160[];
extern u8 D_800DE870[];

void func_80024550(void *arg0)
{
    s16 *global_base;
    s32 temp_v1;
    s32 var_v0;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s2;
    void *temp_v0;

    global_base = (s16 *)D_80083160;
    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != 0) {
        FIELD(temp_v0, void *, 0x10) = D_800244A4;
        var_v0 = rand();
        temp_v1 = var_v0;
        temp_s2 = (u8 *)temp_v0 + 0x20;
        if (temp_v1 < 0) {
            var_v0 = temp_v1 + 0xFFF;
        }
        FIELD(temp_s2, s16, 8) = temp_v1 - ((var_v0 >> 12) << 12);
        temp_s0 = FIELD(temp_v0, void *, 0xC);
        FIELD(temp_s0, u8, 0xE) = 0x80;
        FIELD(temp_s0, u8, 0xD) = 0x80;
        FIELD(temp_s0, u8, 0xC) = 0x80;
        func_8003DB94(temp_s0, D_800DE870, 0);
        FIELD(temp_s0, s16, 0x1E) = 0x1000;
        FIELD(temp_s0, s16, 0x1C) = 0x1000;
        FIELD(temp_s0, u16, 0x10) |= 0x20;
        FIELD(temp_s0, u16, 0x14) |= 0xC;
        FIELD(temp_s0, s16, 0x1A) =
            (s32)(0 - ((func_80064584(FIELD(temp_s2, s16, 8) -
                                      global_base[0x64]) >> 4) << 8)) >> 8;
        func_8004491C(temp_v0, D_80045340);
        temp_s0_2 = FIELD(temp_v0, void *, 8);
        FIELD(temp_s0_2, s16, 2) = FIELD(arg0, u16, 2) +
            ((func_800644B8(FIELD(temp_s2, s16, 8)) * 2) >> 8);
        FIELD(temp_s0_2, s16, 6) = FIELD(arg0, u16, 6) +
            ((func_80064584(FIELD(temp_s2, s16, 8)) * 2) >> 8);
        FIELD(temp_s0_2, u16, 0xA) = FIELD(arg0, u16, 0xA);
    }
}

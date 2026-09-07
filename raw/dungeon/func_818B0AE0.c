#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_8003DB94(void *, void *, s32);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 rand(void);
extern u8 D_800DEC70[];

void func_800242E0(void *arg0, void *arg1, void *arg2) {
    s32 temp_s0;
    u16 temp_v0;
    void *temp_v1;

    temp_v1 = FIELD(arg0, void *, 0);
    FIELD(temp_v1, u16, 0x14) = (u16)(FIELD(temp_v1, u16, 0x14) + 1);
    temp_v0 = FIELD(arg0, u16, 4) + FIELD(arg0, u16, 6);
    FIELD(arg0, u16, 4) = temp_v0;
    if ((s16)temp_v0 < -0x80) {
        temp_s0 = rand() % 0x1000;
        FIELD(arg1, s16, 2) = (s16)(FIELD(arg0, u16, 8) + ((func_800644B8(temp_s0) * 2) >> 8));
        FIELD(arg1, s16, 6) = (s16)(FIELD(arg0, u16, 0xA) + ((func_80064584(temp_s0) * 2) >> 8));
        FIELD(arg0, u16, 4) = (u16)(FIELD(arg0, u16, 4) + 0x80);
        FIELD(arg0, u16, 6) = (u16)(-6 - (rand() % 5));
    }
    FIELD(arg1, s16, 0xA) = (s16)(FIELD(arg0, u16, 0xC) + FIELD(arg0, u16, 4));
    func_800478B8(arg2);
    if (FIELD(arg2, u16, 0x14) & 0x6000) {
        func_8003DB94(arg2, D_800DEC70, 0);
    }
}

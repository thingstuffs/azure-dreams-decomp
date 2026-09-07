#include "common.h"

#define F(e, t, o) (*(t *)((s8 *)(e) + (o)))

extern void func_800AE734(void);

void func_800AE854(void *arg0) {
    s32 a0;
    s32 a0_2;
    s32 a0_3;
    s32 a0_4;
    s32 a0_5;
    s32 t;
    s32 v0;
    s32 v1;
    s32 diff;
    s32 f8;
    s32 last_denom;
    void *ptr;

    func_800AE734();
    a0 = F(arg0, s32, 0x20);
    diff = F(arg0, s32, 0x1C) - a0;
    f8 = F(arg0, s32, 8) * 0x10;
    v0 = diff * f8 / F(arg0, s32, 4) + 0xA;
    ptr = F(F(F(arg0, void *, 0xD8), void *, 4), void *, 4);
    F(ptr, s16, 0xA) = (s16)(a0 * 0x10 + v0);
    t = (F(arg0, s32, 8) * 8) / F(arg0, s32, 4);
    F(F(F(F(arg0, s32, 0x20) * 4 + F(arg0, void *, 0xD8), void *, 0x38), void *, 4), s16, 8) = (s16)(0x28 - t);
    F(F(F(F(arg0, s32, 0x1C) * 4 + F(arg0, void *, 0xD8), void *, 0x38), void *, 4), s16, 8) = (s16)(t + 0x20);
    F(F(F(F(arg0, s32, 0x20) * 4 + F(arg0, void *, 0xD8), void *, 0x50), void *, 4), s16, 8) = (s16)(0x97 - t);
    F(F(F(F(arg0, s32, 0x1C) * 4 + F(arg0, void *, 0xD8), void *, 0x50), void *, 4), s16, 8) = (s16)(t + 0x8F);
    F(F(F(F(arg0, s32, 0x20) * 4 + F(arg0, void *, 0xD8), void *, 8), void *, 4), s16, 8) = (s16)(0x11 - t);
    F(F(F(F(arg0, s32, 0x1C) * 4 + F(arg0, void *, 0xD8), void *, 8), void *, 4), s16, 8) = (s16)(t + 9);
    F(F(F(F(arg0, s32, 0x20) * 4 + F(arg0, void *, 0xD8), void *, 0x20), void *, 4), s16, 8) = (s16)(0x41 - t);
    F(F(F(F(arg0, s32, 0x1C) * 4 + F(arg0, void *, 0xD8), void *, 0x20), void *, 4), s16, 8) = (s16)(t + 0x39);
    a0_2 = F(arg0, s32, 4);
    F(F(F(F(arg0, s32, 0x20) * 4 + F(arg0, void *, 0xD8), void *, 0x38), void *, 4), s8, 0) = (s8)(((a0_2 - F(arg0, s32, 8)) * 0x18) / a0_2 + 0x68);
    a0_3 = F(arg0, s32, 4);
    F(F(F(F(arg0, s32, 0x20) * 4 + F(arg0, void *, 0xD8), void *, 0x38), void *, 4), s8, 1) = (s8)(((a0_3 - F(arg0, s32, 8)) * 0x18) / a0_3 + 0x68);
    v1 = F(arg0, s32, 4);
    F(F(F(F(arg0, s32, 0x20) * 4 + F(arg0, void *, 0xD8), void *, 0x38), void *, 4), s8, 2) = (s8)(((v1 - F(arg0, s32, 8)) << 5) / v1 + 0x60);
    a0_4 = F(arg0, s32, 4);
    F(F(F(F(arg0, s32, 0x1C) * 4 + F(arg0, void *, 0xD8), void *, 0x38), void *, 4), s8, 0) = (s8)(-0x80 - ((a0_4 - F(arg0, s32, 8)) * 0x18) / a0_4);
    a0_5 = F(arg0, s32, 4);
    F(F(F(F(arg0, s32, 0x1C) * 4 + F(arg0, void *, 0xD8), void *, 0x38), void *, 4), s8, 1) = (s8)(-0x80 - ((a0_5 - F(arg0, s32, 8)) * 0x18) / a0_5);
    last_denom = F(arg0, s32, 4);
    F(F(F(F(arg0, s32, 0x1C) * 4 + F(arg0, void *, 0xD8), void *, 0x38), void *, 4), s8, 2) = (s8)(-0x80 - ((last_denom - F(arg0, s32, 8)) << 5) / last_denom);
}

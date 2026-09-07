#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *D_80016000;
extern u8 D_800189DC[16];
extern u8 D_80018B94[16];
extern u8 D_8001A3AE[];
extern u8 D_8001A495[];

extern s32 func_800178A8(void *, s32, s32);
extern void *func_80017960(void *, void *, s32, s32);
extern void func_80018594(s32);
extern s32 func_8001868C(s32);

void *func_80016714(s32 arg0, s32 arg1, s32 arg2)
{
    void *result;
    u8 *base;

    base = D_800189DC;
    result = func_80017960(base, D_80018B94, arg0, arg2);
    if (arg2 == 0xB) {
        func_80018594(0x1458);
        if (func_800178A8(base, arg0, 0xB) != 0) {
            return &D_8001A3AE[0];
        }
        FIELD(FIELD(D_80016000, s32, 8) * 8 +
              FIELD(D_80016000, u8 *, 0x40), u8, 4)++;
        if (FIELD(FIELD(D_80016000, s32, 8) * 8 +
                  FIELD(D_80016000, u8 *, 0x40), u8, 4) >= 5U) {
            func_80018594(0x1459);
        }
        return result;
    }
    if (arg2 == 0x1C) {
        if (func_8001868C(0x992) == 0) {
            func_80018594(0x992);
            return &D_8001A495[0];
        }
    }
    return result;
}

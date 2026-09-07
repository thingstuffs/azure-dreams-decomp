#include "common.h"

extern u8 D_800189CC[16];
extern u8 D_80018B94[16];
extern u8 D_8001A3AE[];
extern u8 D_8001A495[];

extern void func_80017724(void);
extern s32 func_800178A8(void *, s32, s32);
extern void *func_80017960(void *, void *, s32, s32);
extern void func_80018594(s32);
extern s32 func_8001868C(s32);

void *func_8001662C(s32 arg0, s32 arg1, s32 arg2)
{
    void *result;
    u8 *base;

    base = D_800189CC;
    result = func_80017960(base, D_80018B94, arg0, arg2);
    if (arg2 == 0xB) {
        func_80017724();
        if (func_800178A8(base, arg0, 0xB) != 0) {
            return D_8001A3AE;
        }
        return result;
    }
    if (arg2 == 0x1C) {
        if (func_8001868C(0x992) == 0) {
            func_80018594(0x992);
            return D_8001A495;
        }
    }
    return result;
}

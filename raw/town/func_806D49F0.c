#include "common.h"

extern void *func_80016D98(s32 arg0);
extern s32 func_800178A8(void *arg0, s32 arg1, s32 arg2);
extern void *func_80017960(void *arg0, void *arg1, s32 arg2, s32 arg3);

extern u8 D_800189FC[16];
extern u8 D_80018B98[16];
extern u8 D_8001ABA0[16];

void *func_800169F0(s32 arg0, s32 arg1, s32 arg2)
{
    void *result;
    u8 *base;

    result = func_80016D98(arg2);
    if (result != 0) {
        return result;
    }

    base = D_800189FC;
    result = func_80017960(base, D_80018B98, arg0, arg2);
    if ((arg2 == 0xB) && (func_800178A8(base, arg0, 0xB) != 0)) {
        return D_8001ABA0;
    }
    return result;
}

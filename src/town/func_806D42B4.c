#include "common.h"

extern void *func_80016D98(s32 arg0);
extern s32 func_800178A8(void *arg0, s32 arg1, s32 arg2);
extern void *func_80017960(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern void func_80018594(s32 arg0);

extern u8 D_800189AC[16];
extern u8 D_80018B94[16];
extern u8 D_80018FFC[16];

void *func_806D42B4(s32 arg0, s32 arg1, s32 arg2) {
    void *result;

    result = func_80016D98(arg2);
    if (result != 0) {
        return result;
    }
    func_80018594(0x1451);
    result = func_80017960(&D_800189AC, &D_80018B94, arg0, arg2);
    if ((arg2 == 0x1C) && (func_800178A8(&D_800189AC, arg0, 0x1C) != 0)) {
        result = &D_80018FFC;
    }
    return result;
}

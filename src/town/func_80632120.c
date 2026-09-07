#include "common.h"

extern void *func_80016BD0(void *, void *, s32, s32);
extern s32 func_8001764C(u32);

extern u8 D_800176AC[9];
extern u8 D_80017778[9];
extern u8 D_80018ED1[9];

void *func_80632120(s32 arg0, s32 arg1, s32 arg2) {
    void *result;

    result = func_80016BD0(D_800176AC, D_80017778, arg0, arg2);
    if (func_8001764C(12) != 0) {
        result = D_80018ED1;
    }
    return result;
}

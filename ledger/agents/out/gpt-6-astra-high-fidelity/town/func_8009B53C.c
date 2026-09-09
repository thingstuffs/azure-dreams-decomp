#include "common.h"

extern void func_80098C40(s32 arg0, s32 arg1, s32 arg2);
extern s8 D_80082668;

void func_80098C9C(s32 arg0, s32 arg1, s32 arg2) {
    func_80098C40(arg0, arg1, arg2);
    D_80082668 = 0;
}

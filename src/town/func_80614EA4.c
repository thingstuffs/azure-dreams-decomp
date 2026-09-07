#include "common.h"

extern s32 func_80017E00(s32, s32);
extern void func_800181C8(void *, void *, s32, s32);
extern void func_80018B58(s32);
extern s32 func_80018C50(s32);

extern s8 D_80016000[];
extern s32 D_80018EAC;
extern s32 D_80018EC4;
extern s32 D_8001925C;

void func_800166A4(s32 arg0, s32 arg1, s32 arg2)
{
    s8 *base;

    if (func_80017E00(1, 8) != 0) {
        base = *(s8 **)D_80016000;
        base = *(s8 **)(base + 0x20);
        (*(void (**)(s32))(base + 0x78))(0);
        func_80018B58(0x681);
    } else {
        if (func_80018C50(0x681) == 0) {
            func_800181C8(&D_80018EAC, &D_8001925C, arg0, arg2);
            return;
        }
    }

    func_800181C8(&D_80018EC4, &D_8001925C, arg0, arg2);
}

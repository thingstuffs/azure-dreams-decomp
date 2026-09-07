#include "common.h"

extern s32 D_80018E1C;
extern s32 D_80018E34;
extern s32 D_8001925C;

extern void func_800181C8();
extern s32 func_80018C50();

void func_80016434(s32 arg0, s32 arg1, s32 arg2) {
    register void *call_arg0 ASM_REG("$4");

    if (func_80018C50(0xFBC) != 0) {
        call_arg0 = &D_80018E34;
    } else {
        call_arg0 = &D_80018E1C;
    }
    ASM_KEEP(call_arg0);
    func_800181C8(call_arg0, &D_8001925C, arg0, arg2);
}

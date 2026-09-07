#include "common.h"

extern void *D_800160D0[];
extern void *D_8001B16C[];
extern u8 D_8001B14C[];
extern u8 D_8001B9E0[];
extern u8 D_8001C6D0[];
extern u8 D_80020934[];

extern void *func_80016CE4(void);
extern void *func_80016D18(void);
extern void *func_80016E48(s32);
extern void func_8001A554(s32);

void *func_80017180(s32 arg0, s32 arg1, s32 arg2)
{
    void *result;
    s32 index;
    static void *const keepalive[] = {
        &&case_19, &&case_18, &&case_52, &&case_12, &&case_default
    };

    index = arg2 - 12;
    if ((u32)index >= 43) {
        goto case_default;
    }
    ASM_KEEP(arg0);   /* MATCH pin: keeps a statement from moving across a call/branch */
    goto *D_800160D0[index];

case_19:
    result = func_80016CE4();
    D_8001B16C[0] = result;
    if (result != 0) {
        return result;
    }
    return D_8001B9E0;

case_18:
    result = func_80016D18();
    D_8001B16C[0] = result;
    if (result != 0) {
        return result;
    }
    func_8001A554(0x943);
    return D_80020934;

case_52:
    return func_80016E48(arg2);

case_12:
    return D_8001C6D0;

case_default:
    return D_8001B14C;
}

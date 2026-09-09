#include "common.h"

extern void *D_80016020[43];
extern void *D_8001B16C[];
extern char D_8001B14C[];
extern char D_8001B8CC[];
extern char D_8001B9E0[];
extern char D_800206CC[];
extern char D_8001C6D0[];

extern void *func_80016CE4(s32, s32);
extern void *func_80016D18(void);
extern void *func_80016E48(s32);
extern s32 func_8001A64C(s32);
extern void func_8001A554(s32);

void *func_80016FE0(s32 arg0, s32 arg1, s32 arg2)
{
    void *result;
    u32 index;
    static void *const keepalive[] = {
        &&L_case19, &&L_case18, &&L_case52, &&L_case12, &&L_default
    };

    index = arg2 - 12;
    if (index >= 43) {
        goto L_default;
    }
    goto *D_80016020[index];

L_case19:
    result = func_80016CE4(arg0, arg1);
    D_8001B16C[0] = result;
    if (result != 0) {
        return result;
    }
    if (func_8001A64C(0x92C) == 0) {
        func_8001A554(0x92C);
        return D_8001B8CC;
    }
    return D_8001B9E0;

L_case18:
    result = func_80016D18();
    D_8001B16C[0] = result;
    if (result != 0) {
        return result;
    }
    if (func_8001A64C(0xAC) == 0) {
        func_8001A554(0xAC);
    }
    func_8001A554(0x943);
    return D_800206CC;

L_case52:
    {
        register s32 call_arg ASM_REG("$6") = arg2;   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(call_arg);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        return func_80016E48(call_arg);
    }

L_case12:
    return D_8001C6D0;

L_default:
    return D_8001B14C;
}

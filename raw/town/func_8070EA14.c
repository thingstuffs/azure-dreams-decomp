#include "common.h"

__asm__(".set jtbl_800165A0, 0x800165A0");
extern void *jtbl_800165A0[43];

extern u8 D_80016000[0x10];
extern char D_8001B14C[];
extern char D_8001BFF8[];
extern char D_8001C6D0[];
extern char D_8001C8AF[];
extern char D_8001C8DC[];
extern char D_80021F90[];
extern char D_8002242C[];
extern char D_800224EE[];
extern char D_800225DB[];
extern char D_800225F5[];
extern char D_8002264A[];

extern char *func_80016E48(s32);
extern void func_8001A554(s32);
extern s32 func_8001A64C(s32);
extern void func_8001A5CC(s32);

char *func_80017A14(s32 arg0, s32 arg1, s32 arg2)
{
    register s32 selector ASM_REG("$4") = arg2;
    u32 index;
    static void *const keepalive[] = {
        &&L_case19,
        &&L_case18,
        &&L_case12,
        &&L_case34,
        &&L_default
    };

    index = selector - 12;
    if (index >= 43) {
        goto L_default;
    }
    ASM_KEEP(selector);
    goto *jtbl_800165A0[index];

L_case19:
    if (func_8001A64C(0x938) == 0) {
        return D_8001BFF8;
    }
    return D_800225F5;

L_case18:
    if (func_8001A64C(0x938) == 0) {
        func_8001A554(0x937);
        func_8001A554(0x938);
        func_8001A554(0x94D);
        func_8001A5CC(0x94C);
        return D_80021F90;
    }
    return D_800225DB;

L_case12:
    if (func_8001A64C(0x938) == 0) {
        if (func_8001A64C(0x935) != 0) {
            return D_8001C8AF;
        }
        if (func_8001A64C(0x936) != 0) {
            return D_8001C8DC;
        }
        return D_8001C6D0;
    }
    if (func_8001A64C(0x94D) != 0) {
        func_8001A5CC(0x94D);
        func_8001A554(0x94C);
        {
            u8 *state = (u8 *)0x80010000;
            ASM_KEEP(state);
            (*(void (**)(s32))((u8 *)*(void **)((u8 *)*(void **)(state + 0x6000) + 0x20) + 0x258))(1);
            if (*(s32 *)((u8 *)*(void **)((u8 *)*(void **)(state + 0x6000) + 0x1C) + 8) < 0x460) {
                return D_800224EE;
            }
            return D_8002242C;
        }
    }
    return D_8002264A;

L_case34:
    return func_80016E48(selector);

L_default:
    return D_8001B14C;
}

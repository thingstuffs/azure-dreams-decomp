#include "common.h"

extern void *D_80016230[43];

extern char D_8001B14C[];
extern s32 D_8001B16C[];
extern char D_8001B9E0[];
extern char D_8001C6D0[];
extern char D_80020E44[];

extern s32 func_80016CE4(void);
extern s32 func_80016D18(void);
extern char *func_80016E48(s32);

char *func_8001747C(s32 arg0, s32 arg1, s32 arg2)
{
    s32 temp_v0;
    u32 index;
    void **table;
    register s32 selector ASM_REG("$6") = arg2;
    static void *const keepalive[] = {
        &&L_case19,
        &&L_case18,
        &&L_case52,
        &&L_case12,
        &&L_default
    };

    index = arg2 - 12;
    if (index >= 43) {
        goto L_default;
    }
    table = D_80016230;
    ASM_KEEP(selector);
    (void)keepalive;
    goto *table[index];

L_case19:
    temp_v0 = func_80016CE4();
    D_8001B16C[0] = temp_v0;
    if (temp_v0 != 0) {
        goto L_return_temp;
    }
    return D_8001B9E0;

L_case18:
    temp_v0 = func_80016D18();
    D_8001B16C[0] = temp_v0;
    if (temp_v0 == 0) {
        goto L_case18_zero;
    }

L_return_temp:
    return (char *)temp_v0;

L_case18_zero:
    return D_80020E44;

L_case52:
    return func_80016E48(selector);

L_case12:
    return D_8001C6D0;

L_default:
    return D_8001B14C;
}

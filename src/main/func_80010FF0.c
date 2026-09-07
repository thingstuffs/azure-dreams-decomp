#include "common.h"

extern u8 D_80023EC4[];
extern u8 D_80027DD0[];
extern u8 D_80029618[];

extern s32 func_8004B4A8(void *arg0);
extern void *func_8003FE78(s32 arg0, void *arg1, s32 arg2);
extern void func_8004491C(void *arg0, void *arg1);
extern void func_80024184(void *arg0);
extern void func_80069EC8(void *arg0, s32 arg1);
extern void func_80023EF4(void *arg0, s32 arg1);
extern s32 func_80023ECC(void *arg0);
extern void func_80023FA0(void *arg0, s32 arg1, s32 arg2);

void *func_80023FF0(s32 arg0, s32 arg1)
{
    u8 *object;
    u8 *runtime;

    object = D_80029618 + arg1 * 0x3E4;
    runtime = object + 0x20;
    if (func_8004B4A8(object) != 0)
        goto normal;
    object = func_8003FE78(0, object, 0xF9);
    func_8004491C(object, D_80027DD0);
    goto shared;
normal:
    func_80024184(object);
    *(u16 *)(object + 0x1E) &= 0x7FFF;
    func_80069EC8(runtime, 0x3C4);
shared:
    func_80023EF4(runtime, 0xA);
    *(void **)(object + 0xC) = runtime + 0x24C;
    *(s32 *)(runtime + 0x258) = func_80023ECC(runtime + 0x25C);
    func_80023FA0(runtime, arg0, arg1);
    *(void **)(object + 0x10) = D_80023EC4;
    return object;
}

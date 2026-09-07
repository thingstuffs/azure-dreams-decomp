#include "common.h"

typedef s32 (*Func8094D708Callback)(void *, s32);

typedef struct Func8094D708Object {
    u8 pad00[0x10];
    Func8094D708Callback *callbacks;
    s32 field14;
    u8 pad18[2];
    s16 field1A;
} Func8094D708Object;

extern void func_800166A0(s32, s16);

s32 func_808B1704(Func8094D708Object *arg0)
{
    s32 i = 0;
    register u8 *address ASM_REG("$3");
    Func8094D708Callback callback;

    func_800166A0(arg0->field14, arg0->field1A);

L_CALLBACK:
{
    register void *call_arg ASM_REG("$4") = arg0;
    ASM_KEEP(call_arg);
    address = (u8 *)(i << 4);
    address = (u8 *)((s32)address + (s32)arg0->callbacks);
    ASM_KEEP(address);
    callback = *(Func8094D708Callback *)address;
    if (callback(call_arg, i) == 0)
        return i;
    i++;
    goto L_CALLBACK;
}
}

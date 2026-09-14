#include "common.h"

typedef s32 (*Func8094D708Callback)(void *, s32);

typedef struct Func8094D708Object {
    u8 pad00[0x10];
    Func8094D708Callback *callbacks;
    s32 field14;
    u8 pad18[2];
    s16 field1A;
} Func8094D708Object;

extern void func_800166A4(s32, s16);
s32 func_8094D708(Func8094D708Object *arg0) {
    s32 i;
    Func8094D708Callback *base;
    u8 *address;
    void *call_arg;
    Func8094D708Callback callback;

    func_800166A4(arg0->field14, arg0->field1A);
    i = 0;
loop:
    call_arg = arg0;
    base = arg0->callbacks;
    address = (u8 *)(i << 4);
    callback = *(Func8094D708Callback *)((u8 *)((u8 *)((s32)address + (s32)base)));
    if (callback(call_arg, i) == 0) {
        return i;
    }
    i++;
    goto loop;
}

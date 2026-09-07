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
extern void func_8001672C(void) __attribute__((noreturn));
extern void func_8001672C_tail(void) __asm__("func_8001672C");

s32 func_8094D708(Func8094D708Object *arg0) {
    register s32 i ASM_REG("$16");
    register Func8094D708Callback *base ASM_REG("$2");
    register u8 *address ASM_REG("$3");
    register void *call_arg ASM_REG("$4");
    Func8094D708Callback callback;

    func_800166A4(arg0->field14, arg0->field1A);
    i = 0;
    ASM_KEEP(i);
    call_arg = arg0;
    ASM_KEEP(arg0);
    base = arg0->callbacks;
    address = (u8 *)(i << 4);
    address = (u8 *)((s32)address + (s32)base);
    ASM_KEEP(address);
    callback = *(Func8094D708Callback *)address;
    if (callback(call_arg, i) == 0) {
        return i;
    }
    func_8001672C_tail();
    i++;
    ASM_KEEP(i);
}

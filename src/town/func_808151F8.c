#include "common.h"

extern void func_8052FE88() __attribute__((noreturn));
extern s32 D_80084D5C;

void func_808151F8(void *arg0) {
    register u8 *inner ASM_REG("$2");
    s16 state;
    register s32 call_arg ASM_REG("$4");
    s32 value;

    state = *(s16 *)arg0;
    inner = *(u8 **)((u8 *)arg0 + 4);
    call_arg = state;
    if (state == 0) {
        goto state_0;
    }
    call_arg = 0xFFF70000;
    if (state == 1) {
        goto state_1;
    }
    func_8052FE88(call_arg, arg0);
    return;

state_0:
    if (*(u16 *)(inner + 0x1A) & 8) {
        *(s16 *)arg0 = call_arg + 1;
        func_8052FE88(call_arg, arg0);
    }
    return;

state_1:
    value = *(s32 *)((u8 *)arg0 + 8) + (call_arg | 0xF7F8);
    *(s32 *)((u8 *)arg0 + 8) = value;
    if (value <= 0x80808) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_80084D5C |= 0x8000;
    }
}

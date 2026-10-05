#include "common.h"

extern s32 D_80084D5C;

void func_8052FDF8(void *ptr) {
    u8 *inner;
    s32 state;
    s32 call_arg;
    s32 value;

    state = *(s16 *)ptr;
    inner = *(u8 **)((u8 *)ptr + 4);
    call_arg = state;
    if (state != 0) {
        call_arg = 0xFFF70000;
        if (state == 1) {
            goto state_1;
        }
        return;
    }
    if (*(u16 *)(inner + 0x1A) & 8) {
        (*(s16 *)ptr)++;
    }
    return;

state_1:
    value = *(s32 *)((u8 *)ptr + 8) + (call_arg | 0xF7F8);
    *(s32 *)((u8 *)ptr + 8) = value;
    if (value <= 0x80808) {
        *(u16 *)((u8 *)ptr - 2) |= 0x8000;
        D_80084D5C |= 0x8000;
    }
}

#include "common.h"

typedef struct Func800395B0State {
    u8 pad_00[0x10];
    void (*func_10)(void *);
    u8 pad_14[0x08];
    u8 *read_ptr;
    u8 pad_20[0x10];
    u16 half_30;
} Func800395B0State;

extern void func_80038394(void *arg0);

void func_800395B0(Func800395B0State *arg0) {
    u32 ptr = (u32)arg0->read_ptr;
    u32 next = ptr;
    u32 lo = *(u8 *)ptr;

    ptr = *(u8 *)(ptr + 1);
    arg0->read_ptr = (u8 *)(next + 2);
    arg0->func_10 = func_80038394;
    arg0->half_30 = (u16)(lo + (ptr << 8));
}

#include "common.h"

typedef struct Func80039578State {
    u8 pad_00[0x10];
    void (*func_10)(void *);
    u8 pad_14[0x04];
    u16 half_18;
    u8 pad_1A[0x02];
    u8 *read_ptr;
} Func80039578State;

extern void func_80038128(void *arg0);

void func_80039578(Func80039578State *arg0) {
    u32 ptr = (u32)arg0->read_ptr;
    u32 next = ptr;
    u32 lo = *(u8 *)ptr;

    ptr = *(u8 *)(ptr + 1);
    arg0->read_ptr = (u8 *)(next + 2);
    arg0->func_10 = func_80038128;
    arg0->half_18 = (u16)(lo + (ptr << 8));
}

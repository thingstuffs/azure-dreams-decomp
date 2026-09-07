#include "common.h"

typedef struct Func80039C44State {
    u8 pad_00[0x10];
    void (*func_10)(void *);
    u8 pad_14[0x08];
    u8 *read_ptr;
    u8 pad_20[0x06];
    u8 byte_26;
    u8 byte_27;
} Func80039C44State;

extern void func_800385D0(void *arg0);

void func_80039C44(Func80039C44State *arg0) {
    u32 ptr = (u32)arg0->read_ptr;
    u32 next = ptr;

    ptr = *(u8 *)ptr;
    arg0->read_ptr = (u8 *)(next + 1);
    arg0->byte_27 = 0;
    arg0->func_10 = func_800385D0;
    arg0->byte_26 = (u8)ptr;
}

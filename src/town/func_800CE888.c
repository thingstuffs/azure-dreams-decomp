#include "common.h"

extern void func_800C2E84(void *state, s32 output, void *entries);
extern u8 D_800D6AA8;

/* Initialize the object and advance its state. */
void func_800CBFE8(void *object, s32 unused, s32 context) {
    func_800C2E84(object, context, &D_800D6AA8);
    *(u16 *)((u8 *)object + 0x68) += 1;
}

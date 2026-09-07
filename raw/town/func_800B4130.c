#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef void (*Callback)(void *, s32);

extern void func_800B180C(void *, s32);
extern s32 func_800B18E0();

void func_800B1890(void *arg0) {
    void *temp_v1;
    s32 temp_a3;
    s16 temp_a1;
    u16 temp_a2;
    s32 temp_v0;

    temp_v1 = FIELD(arg0, void *, 0x3C);
    temp_a3 = FIELD(arg0, s32, 4);
    temp_a1 = FIELD(temp_v1, s16, 8);
    temp_a2 = FIELD(temp_v1, u16, 8);
    if (temp_a3 < temp_a1) {
        temp_v0 = temp_a1 + 4;
        temp_v0 = temp_a3 - temp_v0;
        temp_v0 >>= 2;
        FIELD(temp_v1, s16, 8) = temp_a2 + temp_v0;
        func_800B18E0(arg0, temp_a1, temp_a2, temp_a3);
        return;
    }

    FIELD(temp_v1, u16, 8) = FIELD(arg0, u16, 4);
    FIELD(arg0, volatile Callback, -0x10) = func_800B180C;
    func_800B180C(arg0, temp_a1);
}

/* MECHANISM: cdk-G0 gives the retail 0x18 frame with only ra saved.
   An explicit a1+4 temporary blocks reassociation into a3-4-a1.
   The volatile callback store stays before jal, restoring its trailing nop. */

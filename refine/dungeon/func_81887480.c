#include "common.h"

typedef s32 M2C_UNK;

M2C_UNK func_8002569C();
void *func_8003FD64();
M2C_UNK func_8004491C();

extern M2C_UNK D_80024804[3];
extern u16 D_80026324;
extern M2C_UNK D_80024EF4[3];

/* Creates an object, copies three source fields to its child, and runs 16 child setup steps. */
void *func_80024C80(s32 value, void *source, s32 unused, s32 context)
{
    void *source_or_value = source;
    register s32 saved_context ASM_REG("$21") = context;   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 adjusted_value;
    s32 step;
    void *child;
    void *object;
    u16 counter;

    adjusted_value = value - 0x20;
    object = func_8003FD64(2, adjusted_value);
    if (object != 0) {
        counter = D_80026324;
        *(M2C_UNK **)((u8 *)object + 0x10) = D_80024804;
        D_80026324 = counter + 1;
        func_8004491C(object, D_80024EF4);

        child = *(void **)((u8 *)object + 8);
        *(u16 *)((u8 *)child + 2) = *(u16 *)((u8 *)source_or_value + 2);
        step = 0;
        *(u16 *)((u8 *)child + 6) = *(u16 *)((u8 *)source_or_value + 6);
        *(u16 *)((u8 *)child + 0xA) = *(u16 *)((u8 *)source_or_value + 0xA);
        source_or_value = (void *)adjusted_value;
        *(s32 *)((u8 *)object + 0x20) = saved_context;
        ASM_KEEP(saved_context);   /* MATCH pin: retail schedule: same instructions, different order without it */

        do {
            func_8002569C(child, (s16)(step << 8), 0x40, -0x100, source_or_value);
            step += 1;
        } while (step < 0x10);
    }
    return object;
}


#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 D_800814A0;

void func_800D6804(void *arg0, void *arg1)
{
    s16 timer;

    {
        register void *state ASM_REG("$7");
        register s32 amount ASM_REG("$4");
        register s32 scaled ASM_REG("$5");
        register s32 addend ASM_REG("$3");
        s32 current;
        s32 quarter;

        state = arg1;
        amount = FIELD(state, s32, 0x14);
        current = FIELD(state, s32, 8);
        scaled = amount << 1;
        addend = amount;
        ASM_KEEP(addend);
        scaled += amount;
        current += addend;
        FIELD(state, s32, 8) = current;
        if (scaled < 0) {
            scaled += 3;
        }
        quarter = scaled >> 2;
        FIELD(state, s32, 0x14) = quarter;
        ASM_KEEP(scaled);
    }

    FIELD(arg0, u8, 4) =
        (FIELD(arg0, u8, 0) * FIELD(arg0, s16, 0x32)) /
        FIELD(arg0, s16, 0x34);
    FIELD(arg0, u8, 5) =
        (FIELD(arg0, u8, 1) * FIELD(arg0, s16, 0x32)) /
        FIELD(arg0, s16, 0x34);
    FIELD(arg0, u8, 6) =
        (FIELD(arg0, u8, 2) * FIELD(arg0, s16, 0x32)) /
        FIELD(arg0, s16, 0x34);

    timer = FIELD(arg0, u16, 0x32) - 1;
    FIELD(arg0, s16, 0x32) = timer;
    FIELD(arg0, s32, 8) = FIELD(arg0, s32, 4);
    if ((timer << 16) <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: The true-space function is a frameless leaf; state stays in a3 while arg0 stays in a2.
   A split shift/copy/add fixes the opening live ranges, and the tail copies the full word at +4.
   Direct scalar RMW plus moved-source orientation at 2.7.2-cdk-G0 closes the final coloring. */

#include "common.h"

extern void *D_800814A8;
extern void func_800DC1AC() __attribute__((noreturn));

void func_800DC168(void *arg0, void *arg1) {
    u8 temp_v1;

    ASM_KEEP(arg0);
    temp_v1 = *((u8 *)D_800814A8 + 0x29);
    if (temp_v1 != *((s32 *)arg0 + 5)) {
        register void *temp_a1 ASM_REG("$5");

        temp_a1 = *((void **)arg1 + 1);
        if (temp_v1 < 0x80U) {
            register s32 value ASM_REG("$2");

            value = -(s32)temp_v1;
            ASM_KEEP(value);
            value /= 2;
            ASM_KEEP(value);
            value -= 1;
            ASM_TAILSLOT_PIN(value);
            func_800DC1AC();
            return;
        }
        ASM_KEEP(temp_a1);
        *((s16 *)temp_a1 + 4) = -0x40;
    }
}

/* MECHANISM: LEAD-19 elides the ra-only frame; entry ASM_KEEP(arg0) schedules that
   frame before the D_800814A8 load so the retail load-delay nop survives.
   Guarded $a1/$v0 ABI pins retain the tail value; LEAD-28 sinks its -1 into the j slot. */

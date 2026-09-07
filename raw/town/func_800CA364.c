#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_800374F4(s32);
extern void func_800C2E84(void *, s32, void *);
extern s32 D_800C7674;
extern s32 D_800D5FE8;

void func_800C7AC4(void *arg0, void *arg1, s32 arg2)
{
    register void *bounds ASM_REG("$18");
    register s32 context ASM_REG("$19");
    s32 count;
    s32 direction;

    bounds = arg1;
    ASM_KEEP_NV(bounds);
    context = arg2;
    ASM_KEEP_NV(context);
    count = 0;
loop:
    direction = func_800374F4(4) & 0xFFFF;
    if (direction == 0) {
        register s32 total ASM_REG("$2");
        register s32 position ASM_REG("$3");
        register s32 component ASM_REG("$4");

        total = FIELD(arg0, s16, 0x84);
        component = FIELD(arg0, s16, 0x8C);
        position = FIELD(bounds, s16, 2);
        ASM_KEEP_NV(total);
        ASM_KEEP_NV(component);
        ASM_KEEP_NV(position);
        total += component;
        position = position < total;
        ASM_KEEP_NV(position);
        if (position != 0) {
            FIELD(arg0, s16, 0x72) = 0x400;
            goto done;
        }
    } else if (direction == 1) {
        register s32 total ASM_REG("$2");
        register s32 position ASM_REG("$3");
        register s32 component ASM_REG("$4");

        total = FIELD(arg0, s16, 0x86);
        component = FIELD(arg0, s16, 0x8E);
        position = FIELD(bounds, s16, 6);
        ASM_KEEP_NV(total);
        ASM_KEEP_NV(component);
        ASM_KEEP_NV(position);
        total += component;
        position = position < total;
        ASM_KEEP_NV(position);
        if (position != 0) {
            FIELD(arg0, s16, 0x72) = 0;
            goto done;
        }
    } else if (direction == 2) {
        register s32 difference ASM_REG("$2");
        register s32 component ASM_REG("$3");
        register s32 limit ASM_REG("$4");

        difference = FIELD(arg0, s16, 0x84);
        component = FIELD(arg0, s16, 0x8C);
        limit = FIELD(bounds, s16, 2);
        ASM_KEEP_NV(difference);
        ASM_KEEP_NV(component);
        ASM_KEEP_NV(limit);
        difference -= component;
        difference = difference < limit;
        ASM_KEEP_NV(difference);
        if (difference != 0) {
            FIELD(arg0, s16, 0x72) = 0xC00;
            goto done;
        }
    } else {
        register s32 difference ASM_REG("$2");
        register s32 component ASM_REG("$3");
        register s32 limit ASM_REG("$4");

        difference = FIELD(arg0, s16, 0x86);
        component = FIELD(arg0, s16, 0x8E);
        limit = FIELD(bounds, s16, 6);
        ASM_KEEP_NV(difference);
        ASM_KEEP_NV(component);
        ASM_KEEP_NV(limit);
        difference -= component;
        difference = difference < limit;
        ASM_KEEP_NV(difference);
        if (difference != 0) {
            FIELD(arg0, s16, 0x72) = 0x800;
            goto done;
        }
    }

    count++;
    if (count < 0x10) {
        goto loop;
    }

done:
    func_800C2E84(arg0, context, &D_800D5FE8);
    FIELD(arg0, void *, 0x50) = &D_800C7674;
}

/* MECHANISM: Recovered 0x800C7BB0 as the true-space local join, not a callee.
   Guarded s2/s3 holds leave the retry counter in s1 and reproduce the save contract.
   Arm-local v0/v1/a0 live ranges order all three loads before each add/sub compare.
   2.7.2-cdk-G0 closes the final lui/move/jal/addiu argument schedule. */

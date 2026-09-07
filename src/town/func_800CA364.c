#include "common.h"

typedef struct S_800C7AC4_0 {
    u8 pad_00[0x50];
    void * unk_50;
    u8 pad_54[0x1E];
    s16 unk_72;
    u8 pad_74[0x10];
    s16 unk_84;
    s16 unk_86;
    u8 pad_88[0x4];
    s16 unk_8C;
    s16 unk_8E;
} S_800C7AC4_0;   /* arg0 in func_800C7AC4 */

typedef struct S_800C7AC4_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800C7AC4_1;   /* bounds in func_800C7AC4 */



extern s32 func_800374F4(s32);
extern void func_800C2E84(void *, s32, void *);
extern s32 D_800C7674;
extern s32 D_800D5FE8;

void func_800C7AC4(S_800C7AC4_0 *arg0, void *arg1, s32 arg2)
{
    register void *bounds ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 context;
    s32 count;
    s32 direction;

    bounds = arg1;
    context = arg2;
    count = 0;
loop:
    direction = func_800374F4(4) & 0xFFFF;
    if (direction == 0) {
        s32 total;
        s32 position;   /* MATCH pin: retail register colouring depends on it */
        s32 component;

        total = arg0->unk_84;
        component = arg0->unk_8C;
        position = ((S_800C7AC4_1 *)bounds)->unk_02;
        total += component;
        position = position < total;
        if (position != 0) {
            arg0->unk_72 = 0x400;
            goto done;
        }
    } else if (direction == 1) {
        s32 total;
        s32 position;   /* MATCH pin: retail register colouring depends on it */
        s32 component;

        total = arg0->unk_86;
        component = arg0->unk_8E;
        position = ((S_800C7AC4_1 *)bounds)->unk_06;
        total += component;
        position = position < total;
        if (position != 0) {
            arg0->unk_72 = 0;
            goto done;
        }
    } else if (direction == 2) {
        s32 difference;
        s32 component;
        s32 limit;

        difference = arg0->unk_84;
        component = arg0->unk_8C;
        limit = ((S_800C7AC4_1 *)bounds)->unk_02;
           /* MATCH pin: load-bearing for the whole function shape */
        difference -= component;
        difference = difference < limit;
        if (difference != 0) {
            arg0->unk_72 = 0xC00;
            goto done;
        }
    } else {
        s32 difference;
        s32 component;
        s32 limit;

        difference = arg0->unk_86;
        component = arg0->unk_8E;
        limit = ((S_800C7AC4_1 *)bounds)->unk_06;
           /* MATCH pin: load-bearing for the whole function shape */
        difference -= component;
        difference = difference < limit;
        if (difference != 0) {
            arg0->unk_72 = 0x800;
            goto done;
        }
    }

    count++;
    if (count < 0x10) {
        goto loop;
    }

done:
    func_800C2E84(arg0, context, &D_800D5FE8);
    arg0->unk_50 = &D_800C7674;
}

/* MECHANISM: Recovered 0x800C7BB0 as the true-space local join, not a callee.
   Guarded s2/s3 holds leave the retry counter in s1 and reproduce the save contract.
   Arm-local v0/v1/a0 live ranges order all three loads before each add/sub compare.
   2.7.2-cdk-G0 closes the final lui/move/jal/addiu argument schedule. */

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

/* Try random directions against the bounds, then initialize the entity state. */
void func_800C7AC4(S_800C7AC4_0 *entity, void *bounds_arg, s32 context_arg)
{
    register void *bounds ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 context;
    s32 attempts;
    s32 direction;

    bounds = bounds_arg;
    context = context_arg;
    attempts = 0;
loop:
    direction = func_800374F4(4) & 0xFFFF;
    if (direction == 0) {
        s32 upper_edge;
        register s32 bound_test ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        s32 extent;

        upper_edge = entity->unk_84;
        extent = entity->unk_8C;
        bound_test = ((S_800C7AC4_1 *)bounds)->unk_02;
        upper_edge += extent;
        bound_test = bound_test < upper_edge;
        if (bound_test != 0) {
            entity->unk_72 = 0x400;
            goto done;
        }
    } else if (direction == 1) {
        s32 upper_edge;
        register s32 bound_test ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        s32 extent;

        upper_edge = entity->unk_86;
        extent = entity->unk_8E;
        bound_test = ((S_800C7AC4_1 *)bounds)->unk_06;
        upper_edge += extent;
        bound_test = bound_test < upper_edge;
        if (bound_test != 0) {
            entity->unk_72 = 0;
            goto done;
        }
    } else if (direction == 2) {
        s32 lower_edge;
        s32 extent;
        s32 bound_coord;

        lower_edge = entity->unk_84;
        extent = entity->unk_8C;
        bound_coord = ((S_800C7AC4_1 *)bounds)->unk_02;
        ASM_KEEP_NV(lower_edge);   /* MATCH pin: load-bearing for the whole function shape */
        lower_edge -= extent;
        lower_edge = lower_edge < bound_coord;
        if (lower_edge != 0) {
            entity->unk_72 = 0xC00;
            goto done;
        }
    } else {
        s32 lower_edge;
        s32 extent;
        s32 bound_coord;

        lower_edge = entity->unk_86;
        extent = entity->unk_8E;
        bound_coord = ((S_800C7AC4_1 *)bounds)->unk_06;
        ASM_KEEP_NV(lower_edge);   /* MATCH pin: load-bearing for the whole function shape */
        lower_edge -= extent;
        lower_edge = lower_edge < bound_coord;
        if (lower_edge != 0) {
            entity->unk_72 = 0x800;
            goto done;
        }
    }

    attempts++;
    if (attempts < 0x10) {
        goto loop;
    }

done:
    func_800C2E84(entity, context, &D_800D5FE8);
    entity->unk_50 = &D_800C7674;
}

/* MECHANISM: Recovered 0x800C7BB0 as the true-space local join, not a callee.
   Guarded s2/s3 holds leave the retry counter in s1 and reproduce the save contract.
   Arm-local v0/v1/a0 live ranges order all three loads before each add/sub compare.
   2.7.2-cdk-G0 closes the final lui/move/jal/addiu argument schedule. */

#include "common.h"
#include "records/Rec_func_80094268_arg0.h"


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
void func_800C7AC4(Rec_func_80094268_arg0 *entity, void *bounds_arg, s32 context_arg)
{
    register void *bounds ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
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
        s32 bound_test;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 extent;

        upper_edge = entity->unk_84.as_s16;
        extent = entity->unk_8C;
        bound_test = ((S_800C7AC4_1 *)bounds)->unk_02;
        upper_edge += extent;
        bound_test = bound_test < upper_edge;
        if (bound_test != 0) {
            entity->unk_72.as_s16 = 0x400;
            goto done;
        }
    } else if (direction == 1) {
        s32 upper_edge;
        s32 bound_test;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 extent;

        upper_edge = entity->unk_86.as_s16;
        extent = entity->unk_8E;
        bound_test = ((S_800C7AC4_1 *)bounds)->unk_06;
        upper_edge += extent;
        bound_test = bound_test < upper_edge;
        if (bound_test != 0) {
            entity->unk_72.as_s16 = 0;
            goto done;
        }
    } else if (direction == 2) {
        s32 lower_edge;
        s32 extent;
        s32 bound_coord;

        lower_edge = entity->unk_84.as_s16;
        extent = entity->unk_8C;
        bound_coord = ((S_800C7AC4_1 *)bounds)->unk_02;
           /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        lower_edge -= extent;
        lower_edge = lower_edge < bound_coord;
        if (lower_edge != 0) {
            entity->unk_72.as_s16 = 0xC00;
            goto done;
        }
    } else {
        s32 lower_edge;
        s32 extent;
        s32 bound_coord;

        lower_edge = entity->unk_86.as_s16;
        extent = entity->unk_8E;
        bound_coord = ((S_800C7AC4_1 *)bounds)->unk_06;
           /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        lower_edge -= extent;
        lower_edge = lower_edge < bound_coord;
        if (lower_edge != 0) {
            entity->unk_72.as_s16 = 0x800;
            goto done;
        }
    }

    attempts++;
    if (attempts < 0x10) {
        goto loop;
    }

done:
    func_800C2E84(entity, context, &D_800D5FE8);
    entity->unk_50.as_pv = &D_800C7674;
}

/* MECHANISM: Recovered 0x800C7BB0 as the true-space local join, not a callee.
   Guarded s2/s3 holds leave the retry counter in s1 and reproduce the save contract.
   Arm-local v0/v1/a0 live ranges order all three loads before each add/sub compare.
   2.7.2-cdk-G0 closes the final lui/move/jal/addiu argument schedule. */

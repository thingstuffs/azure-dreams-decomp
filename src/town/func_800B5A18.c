#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B3178_3 {
    u8 pad_00[0x4];
    s8 * unk_04;
} S_800B3178_3;   /* *var_s0 in func_800B3178 */

typedef struct S_800B3178_4 {
    u8 pad_00[0x1];
    s8 unk_01;
    s8 unk_02;
} S_800B3178_4;   /* ((S_800B3178_3 *)(*var_s0))->unk_04 in func_800B3178 */




s32 func_8004AC3C();                   /* extern */
s32 func_8004DC14();                        /* extern */
M2C_UNK func_800B3290();                            /* extern */

typedef struct S_800B3178_0 {
    s32 unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
} S_800B3178_0;   /* arg1 in func_800B3178 */

typedef struct S_800B3178_1 {
    s32 unk_00;
    s8 * unk_04;
} S_800B3178_1;   /* *var_s0 in func_800B3178 */

typedef struct S_800B3178_2 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800B3178_2;   /* *var_s1 in func_800B3178 */

void func_800B3178(void **arg0, S_800B3178_0 *arg1, s32 arg2) {
    s32 sp10;
    s32 temp_v1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    void **var_s0;
    void **var_s1;

    var_s3 = 0;
    var_s5 = 0x40;
    var_s4 = 0x80;
    temp_v1 = arg1->unk_00;
    var_s0 = arg0;
    var_s2 = temp_v1 * 0xA;
    var_s1 = (temp_v1 * 0x28) + arg2;
loop_1:
    if (var_s2 < arg1->unk_0C) {
        ((S_800B3178_1 *)(*var_s0))->unk_00 = func_8004DC14(func_8004AC3C(*var_s1, &sp10), sp10);
        if (((S_800B3178_2 *)(*var_s1))->unk_01 == 0x13) {
            *((S_800B3178_1 *)(*var_s0))->unk_04 = var_s5;
            ((S_800B3178_4 *)(((S_800B3178_3 *)(*var_s0))->unk_04))->unk_01 = var_s5;
            ((S_800B3178_4 *)(((S_800B3178_3 *)(*var_s0))->unk_04))->unk_02 = var_s5;
            func_800B3290();
            return;
        }
        *((S_800B3178_1 *)(*var_s0))->unk_04 = var_s4;
        ((S_800B3178_4 *)(((S_800B3178_3 *)(*var_s0))->unk_04))->unk_01 = var_s4;
        ((S_800B3178_4 *)(((S_800B3178_3 *)(*var_s0))->unk_04))->unk_02 = var_s4;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        var_s0 = (void **)((s8 *)((void **)((s8 *)var_s0 + 4)));
        var_s3 += 1;
        var_s1 = (void **)((s8 *)((void **)((s8 *)var_s1 + 4)));
        var_s2 += 1;
        if (var_s3 >= 0xA) {

        } else {
            goto loop_1;
        }
    }
}

/* MECHANISM: Named 0x40/0x80 locals span the loop and force s5/s4, completing the 0x38 hold-set.
   The third 0x40 byte store supplies the tail-j delay slot while arg1 naturally occupies s6.
   ASM_SCHED_BARRIER after the third 0x80 store keeps the four induction updates at the retail tail. */

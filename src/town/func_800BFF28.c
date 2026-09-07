#include "common.h"
#include "m2c_compat.h"

typedef struct S_800BD688_9 {
    void * unk_00;
    void * unk_04;
} S_800BD688_9;   /* arg0 in func_800BD688 */

typedef struct S_800BD688_10 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800BD688_10;   /* ((S_800BD688_9 *)arg0)->unk_00 in func_800BD688 */

typedef struct S_800BD688_11 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800BD688_11;   /* ((S_800BD688_9 *)arg0)->unk_04 in func_800BD688 */


typedef struct S_800BD688_0_pre {
    u16 unk_00;
} S_800BD688_0_pre;   /* the 0x2 bytes before arg0 in func_800BD688, addressed as arg0[-1] */

typedef struct S_800BD688_0 {
    void * unk_00;
    void * unk_04;
    s32 unk_08;
    u8 pad_0C[0x14];
    union { s16 s; u16 u; } unk_20;   /* accessed as both */
    u16 unk_22;
} S_800BD688_0;   /* arg0 in func_800BD688 */

typedef struct S_800BD688_1 {
    s32 unk_00;
} S_800BD688_1;   /* left_ptr in func_800BD688 */

typedef struct S_800BD688_2 {
    s32 unk_00;
} S_800BD688_2;   /* right_ptr in func_800BD688 */

typedef struct S_800BD688_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800BD688_3;   /* var_a0 in func_800BD688 */

typedef struct S_800BD688_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800BD688_4;   /* temp_v1_2 in func_800BD688 */

typedef struct S_800BD688_5 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800BD688_5;   /* temp_v1_3 in func_800BD688 */

typedef struct S_800BD688_6 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800BD688_6;   /* temp_a0 in func_800BD688 */

typedef struct S_800BD688_7 {
    s32 unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
} S_800BD688_7;   /* temp_a1 in func_800BD688 */

typedef struct S_800BD688_8 {
    s32 unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
} S_800BD688_8;   /* temp_a0_2 in func_800BD688 */


s32 rand(void);                      /* extern */

void func_800BD688(void *arg0_in) {
    void *arg0 = arg0_in;
    s32 temp_v1;
    s32 temp_v0_2;
    s32 temp_v1_4;
    s32 upper;
    s32 decrement;
    s32 var_s1;
    register s32 var_v0 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 var_v0_2;
    u16 temp_v0;
    register s32 *page ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    void **var_s0;
    S_800BD688_6 *temp_a0;
    S_800BD688_8 *temp_a0_2;
    S_800BD688_7 *temp_a1;
    S_800BD688_4 *temp_v1_2;
    S_800BD688_5 *temp_v1_3;
    S_800BD688_3 *var_a0;

    temp_v1 = ((S_800BD688_0 *)arg0)->unk_20.s;
    temp_v0 = (((S_800BD688_0 *)arg0)->unk_22 + 1) & 7;
    ((S_800BD688_0 *)arg0)->unk_22 = temp_v0;
    if (temp_v1 == 0) {
        goto state_zero;
    }
    if (temp_v1 == 1) {
        goto state_one;
    }
    goto done;

state_zero:
    var_a0 = (void *)0xFEC00000;
    if (temp_v0 == 0) {
        {
            S_800BD688_1 *left_ptr;
            S_800BD688_2 *right_ptr;

            left_ptr = ((S_800BD688_0 *)arg0)->unk_00;
            right_ptr = ((S_800BD688_0 *)arg0)->unk_04;
            var_v0 = left_ptr->unk_00;
            var_v0 -= right_ptr->unk_00;
        }
        if (var_v0 < 0) {
            var_v0 = 0 - var_v0;
        }
        ASM_KEEP(var_v0);   /* MATCH pin: retail basic-block layout depends on it */
        {
            register u32 range ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */

            range = var_v0 + 0xFFE00000;
            if (range > 0x200000U) {
                var_s1 = 1;
                upper = 0x7FFFF;
                decrement = 0xFFF80000;
                var_s0 = arg0 + 4;
                do {
                    temp_v0_2 = rand();
                    var_a0 = *var_s0;
                    var_v0_2 = (temp_v0_2 & 0x1FF) << 8;
                    if (var_a0->unk_0C > upper) {
                        var_v0_2 = 0 - var_v0_2;
                    }
                    var_a0->unk_0C = var_v0_2;
                    temp_v1_2 = *var_s0;
                    var_s0 = (void **)((s8 *)((void **)((s8 *)var_s0 - 4)));
                    var_s1 -= 1;
                    temp_v1_2->unk_0C = (s32) (temp_v1_2->unk_0C + decrement);
                } while (var_s1 >= 0);
            }
        }
        var_s1 = 1;
        var_s0 = arg0 + 4;
        do {
            temp_v0_2 = rand();
            var_s1 -= 1;
            temp_v1_3 = *var_s0;
            var_s0 = (void **)((s8 *)((void **)((s8 *)var_s0 - 4)));
            temp_v1_3->unk_10 = (s32) (((temp_v0_2 & 0x1FF) - 0x100) << 9);
        } while (var_s1 >= 0);
        ((S_800BD688_10 *)(((S_800BD688_9 *)arg0)->unk_00))->unk_14 = (s32) (((rand() & 0x1FF) - 0x100) << 8);
        ((S_800BD688_11 *)(((S_800BD688_9 *)arg0)->unk_04))->unk_14 = (s32) ((rand() & 0x1FF) << 7);
        temp_a0 = ((S_800BD688_0 *)arg0)->unk_04;
        if (((S_800BD688_10 *)(((S_800BD688_9 *)arg0)->unk_00))->unk_08 < temp_a0->unk_08) {
            temp_a0->unk_14 = (s32) (0 - temp_a0->unk_14);
        }
    }
    temp_a1 = ((S_800BD688_0 *)arg0)->unk_00;
    temp_v1_4 = ((S_800BD688_0 *)arg0)->unk_08 + 0xFEC00000;
    if (temp_a1->unk_00 < temp_v1_4) {
        temp_a0_2 = ((S_800BD688_0 *)arg0)->unk_04;
        if (temp_a0_2->unk_00 < temp_v1_4) {
            temp_a0_2->unk_0C = 0;
            temp_a1->unk_0C = 0;
            ((S_800BD688_0 *)arg0)->unk_20.u += 1;
        }
    }
    goto done;

state_one:
    page = (s32 *)0x80080000;
    ASM_KEEP(page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ((S_800BD688_0_pre *)arg0)[-1].unk_00 = (u16) (((S_800BD688_0_pre *)arg0)[-1].unk_00 | 0x8000);
    page[0x14A0 / 4] |= 0x8000;

done:
    return;
}

/* MECHANISM: True-space CFG labels place the state-one tail after the main path and preserve the 0x28 frame.
   Reused s1/s0 loop locals plus the zero-argument RNG shape recover the retail call slots and saved-register roles.
   Guarded v0/v1 runtime values and the held 0x80080000 page base close coloring and +0x14A0 addressing. */

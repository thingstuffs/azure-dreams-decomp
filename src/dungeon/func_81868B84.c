#include "common.h"
#include "m2c_compat.h"

typedef struct S_81868B84_0_pre {
    u16 unk_00;
} S_81868B84_0_pre;   /* the 0x2 bytes before arg0 in func_81868B84, addressed as arg0[-1] */

typedef struct S_81868B84_0 {
    u16 unk_00;
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    void * unk_0C;
    u8 unk_10;
} S_81868B84_0;   /* arg0 in func_81868B84 */

typedef struct S_81868B84_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_81868B84_1;   /* temp_v0 in func_81868B84 */

typedef struct S_81868B84_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
} S_81868B84_2;   /* arg1 in func_81868B84 */

typedef struct S_81868B84_3 {
    u8 pad_00[0x16];
    s8 unk_16;
} S_81868B84_3;   /* ((S_81868B84_0 *)arg0)->unk_0C in func_81868B84 */


M2C_UNK func_80024264();
extern void func_8002465C(void) __attribute__((noreturn));
extern void func_80024660(void) __attribute__((noreturn));
s32 func_800644B8();
s32 func_80064584();
s32 func_800A45D8();
extern s32 D_800814A0[];

void func_81868B84(void *arg0, void *arg1) {
    s32 temp_lo;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 var_s3;
    s32 var_s3_2;
    s32 var_s4;
    register s32 var_s4_2 ASM_REG("$20");   /* MATCH pin: retail register colouring depends on it */
    s32 state3_compare;
    u16 temp_v0_2;
    void *temp_v0;
    s16 state;

    temp_v0 = ((S_81868B84_0 *)arg0)->unk_0C;
    ((S_81868B84_1 *)temp_v0)->unk_14 = (u16) (((S_81868B84_1 *)temp_v0)->unk_14 + 1);
    ((S_81868B84_0 *)arg0)->unk_02.s = (u16) (((S_81868B84_0 *)arg0)->unk_02.s + 1);
    state = *(s16 *)arg0;
    if (state == 1) {
        goto state1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state0;
        }
        ((S_81868B84_0 *)arg0)->unk_00 = 3;
        func_80024660();
        return;
    }
    if (state == 2) {
        goto state2;
    }
    state3_compare = 3;
    ASM_KEEP(state3_compare);   /* MATCH pin: retail delay-slot contents depend on it */
    if (state == state3_compare) {
        goto state3;
    }
    ((S_81868B84_0 *)arg0)->unk_00 = 3;
    func_80024660();
    return;

state0:
        ((S_81868B84_2 *)arg1)->unk_0A = (u16) (((S_81868B84_2 *)arg1)->unk_0A - 4);
        func_80024264(((S_81868B84_0 *)arg0)->unk_0C, arg1, ((S_81868B84_0 *)arg0)->unk_10);
        if (((S_81868B84_0 *)arg0)->unk_02.u < 8) {
            return;
        }
        {
            s32 tail_value;
            tail_value = ((S_81868B84_0 *)arg0)->unk_00 + 1;
            ((S_81868B84_0 *)arg0)->unk_02.s = 0U;
            ASM_TAILSLOT_PIN(tail_value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            func_8002465C();
        }
        return;
state1:
        var_s3_2 = 0;
        var_s4_2 = var_s3_2;
        ((S_81868B84_0 *)arg0)->unk_06 = (u16) (((S_81868B84_0 *)arg0)->unk_06 + 6);
        temp_v0_2 = ((S_81868B84_0 *)arg0)->unk_0A + 0x10;
        ((S_81868B84_0 *)arg0)->unk_0A = temp_v0_2;
        ((S_81868B84_0 *)arg0)->unk_08 = (u16) (((S_81868B84_0 *)arg0)->unk_08 + temp_v0_2);
        do {
            temp_s0_2 = var_s4_2 >> 0x10;
            temp_lo = (func_800644B8((s16) ((S_81868B84_0 *)arg0)->unk_08 + temp_s0_2) >> 4) * (s16) ((S_81868B84_0 *)arg0)->unk_06;
            ((S_81868B84_2 *)arg1)->unk_02 = (u16) (((S_81868B84_2 *)arg1)->unk_0E + (temp_lo >> 8));
            temp_lo = (func_80064584((s16) ((S_81868B84_0 *)arg0)->unk_08 + temp_s0_2) >> 4) * (s16) ((S_81868B84_0 *)arg0)->unk_06;
            ((S_81868B84_2 *)arg1)->unk_06 = (u16) (((S_81868B84_2 *)arg1)->unk_12 + (temp_lo >> 8));
            if ((func_800A45D8(((S_81868B84_2 *)arg1)->unk_02, ((S_81868B84_2 *)arg1)->unk_06, (s16) ((S_81868B84_2 *)arg1)->unk_0A, temp_lo) << 0x10) == 0) {
                func_80024264(((S_81868B84_0 *)arg0)->unk_0C, arg1, ((S_81868B84_0 *)arg0)->unk_10);
            }
            var_s4_2 += 0x05550000;
            var_s3_2 += 1;
        } while (var_s3_2 < 3);
        if (((S_81868B84_0 *)arg0)->unk_02.u < 0x20) {
            return;
        }
        {
            s32 tail_value;
            tail_value = ((S_81868B84_0 *)arg0)->unk_00 + 1;
            ((S_81868B84_0 *)arg0)->unk_02.s = 0U;
            ASM_TAILSLOT_PIN(tail_value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            func_8002465C();
        }
        return;
state2:
        var_s3 = 0;
        var_s4 = var_s3;
        ((S_81868B84_0 *)arg0)->unk_06 = (u16) (((S_81868B84_0 *)arg0)->unk_06 + 6);
        ((S_81868B84_0 *)arg0)->unk_08 = (u16) (((S_81868B84_0 *)arg0)->unk_08 + ((S_81868B84_0 *)arg0)->unk_0A);
        do {
            temp_s0 = var_s4 >> 0x10;
            temp_lo = (func_800644B8((s16) ((S_81868B84_0 *)arg0)->unk_08 + temp_s0) >> 4) * (s16) ((S_81868B84_0 *)arg0)->unk_06;
            ((S_81868B84_2 *)arg1)->unk_02 = (u16) (((S_81868B84_2 *)arg1)->unk_0E + (temp_lo >> 8));
            temp_lo = (func_80064584((s16) ((S_81868B84_0 *)arg0)->unk_08 + temp_s0) >> 4) * (s16) ((S_81868B84_0 *)arg0)->unk_06;
            ((S_81868B84_2 *)arg1)->unk_06 = (u16) (((S_81868B84_2 *)arg1)->unk_12 + (temp_lo >> 8));
            if ((func_800A45D8(((S_81868B84_2 *)arg1)->unk_02, ((S_81868B84_2 *)arg1)->unk_06, (s16) ((S_81868B84_2 *)arg1)->unk_0A, temp_lo) << 0x10) == 0) {
                func_80024264(((S_81868B84_0 *)arg0)->unk_0C, arg1, ((S_81868B84_0 *)arg0)->unk_10);
            }
            var_s4 += 0x05550000;
            var_s3 += 1;
        } while (var_s3 < 3);
        ((S_81868B84_0 *)arg0)->unk_10 = (u8) (((S_81868B84_0 *)arg0)->unk_10 - 8);
        if (((S_81868B84_0 *)arg0)->unk_02.u < 8) {
            return;
        }
        {
            s32 tail_value;
            tail_value = ((S_81868B84_0 *)arg0)->unk_00 + 1;
            ((S_81868B84_0 *)arg0)->unk_02.s = 0U;
            ASM_TAILSLOT_PIN(tail_value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            func_8002465C();
        }
        return;
state3:
        ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
        ((S_81868B84_3 *)(((S_81868B84_0 *)arg0)->unk_0C))->unk_16 = 1;
        (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_81868B84_0_pre *)arg0)[-1].unk_00 | 0x8000);
        {
            s32 *state3_global;
            state3_global = D_800814A0;
            state3_global[0] |= 0x8000;
        }
        ((S_81868B84_0 *)arg0)->unk_00 = (u16) ((s32 (*)(void)) func_80024660)();
}

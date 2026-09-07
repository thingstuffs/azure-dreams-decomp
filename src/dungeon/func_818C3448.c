#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_818C3448_0_pre {
    u16 unk_00;
} S_818C3448_0_pre;   /* the 0x2 bytes before arg0 in func_818C3448, addressed as arg0[-1] */

typedef struct S_818C3448_0 {
    void * unk_00;
    u8 pad_04[0xA];
    union { s16 s; u16 u; } unk_0E;   /* accessed as both */
    union { u16 s; s16 u; } unk_10;   /* accessed as both */
    u16 unk_12;
    s16 unk_14;
} S_818C3448_0;   /* arg0 in func_818C3448 */

typedef struct S_818C3448_1 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_818C3448_1;   /* temp_v1 in func_818C3448 */



extern s32 D_800814A0[3];
M2C_UNK func_800247AC();
M2C_UNK func_80024AF4();
M2C_UNK func_80024E9C() __attribute__((noreturn));
void func_80024EEC(void) __attribute__((noreturn));
s32 func_80069EF8();

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
} Func818C3448State;

void func_818C3448(void *arg0, void *arg1, Rec_D_80082E80 *arg2) {
    s16 temp_lo;
    s32 temp_a1_s16;
    register s32 temp_s0 ASM_REG("$16");   /* MATCH pin: load-bearing for the whole function shape */
    s16 temp_v0;
    s16 temp_v1_3;
    s16 temp_v1_4;
    s16 tail_v0;
    s16 tail_v1;
    s32 var_v1;
    s32 temp_a0;
    s32 temp_a0_3;
    s32 temp_a1;
    register s32 case0_scale ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 var_a2;
    s32 var_v0;
    s32 tail_cond;
    u16 case2_state;
    u16 temp_a0_2;
    S_818C3448_1 *temp_v1;

    temp_v1 = ((S_818C3448_0 *)arg0)->unk_00;
    temp_v1->unk_0C = (u16) (temp_v1->unk_0C + 1);
    temp_v1_3 = (s16) (((S_818C3448_0 *)arg0)->unk_12 + 1);
    temp_s0 = temp_v1_3;
    ((S_818C3448_0 *)arg0)->unk_10.s = (u16) (((S_818C3448_0 *)arg0)->unk_10.s + 1);
    ((S_818C3448_0 *)arg0)->unk_12 = (u16) temp_v1_3;
    temp_s0 = (temp_s0 % 7) + 1;
    func_800478B8(arg2);
    temp_a1_s16 = (s16) temp_s0;
    var_v1 = temp_a1_s16;
    arg2->unk_1A.as_u16 = (u16) (arg2->unk_1A.as_u16 + 0x300);
    if (temp_a1_s16 < 0) {
        var_v1 = temp_a1_s16 + 3;
    }
    temp_a0 = temp_a1_s16 / 2;
    arg2->unk_0C.at00_s8.v = (s8) ((var_v1 >> 2) << 7);
    arg2->unk_0C.at01_s8.v = (s8) ((s32) (((s16) temp_a0 - (((s32) ((s16) temp_a0 + ((u32) (temp_a0 << 0x10) >> 0x1F)) >> 1) * 2)) << 0x10) >> 9);
    arg2->unk_0C.at02_s8.v = (s8) ((s32) ((temp_a1_s16 - (temp_a0 * 2)) << 0x10) >> 9);
    temp_v1_4 = ((S_818C3448_0 *)arg0)->unk_0E.s;
    temp_a0_2 = (u16) ((S_818C3448_0 *)arg0)->unk_0E.s;
    if (temp_v1_4 == 1) {
        goto case_1;
    }
    if (temp_v1_4 < 2) {
        if (temp_v1_4 == 0) {
            case0_scale = 0x1400;
            goto case_0;
        }
        func_80024EEC();
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
    if (temp_v1_4 == 2) {
        goto case_2;
    }
    if (temp_v1_4 == 3) {
        goto case_3;
    }
    func_80024EEC();

case_0:
        temp_lo = (case0_scale / (s16) ((S_818C3448_0 *)arg0)->unk_14) * (s16) ((S_818C3448_0 *)arg0)->unk_10.s;
        arg2->unk_1C.at02_s16.v = temp_lo;
        arg2->unk_1C.at00_s16.v = temp_lo;
        temp_v0_3 = ((Func818C3448State *)arg1)->f0;
        temp_v1_6 = ((Func818C3448State *)arg1)->fC;
        temp_a0_3 = ((Func818C3448State *)arg1)->f10;
        temp_a1 = ((Func818C3448State *)arg1)->f14;
        ((Func818C3448State *)arg1)->f0 = temp_v0_3 + temp_v1_6;
        ((Func818C3448State *)arg1)->f4 = (s32) (((Func818C3448State *)arg1)->f4 + temp_a0_3);
        ((Func818C3448State *)arg1)->f8 = (s32) (((Func818C3448State *)arg1)->f8 + temp_a1);
        tail_v0 = ((S_818C3448_0 *)arg0)->unk_10.u;
        tail_v1 = ((S_818C3448_0 *)arg0)->unk_14;
        tail_cond = tail_v0 < tail_v1;
        ASM_TAILSLOT_PIN(tail_cond);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_80024E9C(temp_a0_3, temp_a1);
        return;
case_1:
        if ((s16) ((S_818C3448_0 *)arg0)->unk_10.s < 0xC) {
            return;
        }
        ((S_818C3448_0 *)arg0)->unk_0E.s = (s16) (temp_a0_2 + 1);
        ((S_818C3448_0 *)arg0)->unk_10.u = 0;
        func_80024EEC();
        return;
case_2:
        func_80024AF4(arg0, arg1, arg2);
        var_v0 = func_80069EF8();
        temp_v1_5 = var_v0;
        if (temp_v1_5 < 0) {
            var_v0 = temp_v1_5 + 0xFFF;
        }
        temp_v0 = temp_v1_5 - ((var_v0 >> 0xC) << 0xC);
        func_800247AC(arg0, arg1, temp_v0);
        temp_v0_2 = temp_v0 + 0x800;
        var_a2 = temp_v0_2;
        if (temp_v0_2 < 0) {
            var_a2 = temp_v0 + 0x17FF;
        }
        func_800247AC(arg0, arg1, (s16) (temp_v0_2 - ((var_a2 >> 0xC) << 0xC)));
        if ((s16) ((S_818C3448_0 *)arg0)->unk_10.s < 0x21) {
            return;
        }
        case2_state = ((S_818C3448_0 *)arg0)->unk_0E.u;
        ((S_818C3448_0 *)arg0)->unk_10.s = 0U;
        ((S_818C3448_0 *)arg0)->unk_0E.u = (u16) (case2_state + 1);
        func_80024EEC();
        return;
case_3:
        if (arg2->unk_14.at00_u16.v & 0x6000) {
            ((S_818C3448_0_pre *)arg0)[-1].unk_00 = (u16) (((S_818C3448_0_pre *)arg0)[-1].unk_00 | 0x8000);
            D_800814A0[0] |= 0x8000;
        }
        return;
}

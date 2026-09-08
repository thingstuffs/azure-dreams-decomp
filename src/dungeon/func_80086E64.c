#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_80048A44();
extern s32 func_8008C730();
extern void func_8008c798(void) __attribute__((noreturn));
extern M2C_UNK func_80099844();
extern s32 func_8009B5AC();
extern M2C_UNK func_8009F644();
extern M2C_UNK func_800A56E0();
extern s32 D_80012090[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern s32 D_80081484[];
extern s32 D_80083170[];
extern s16 D_80083228[];
extern u8 D_8008ACDC[];
extern u8 D_800DCFC8[];
extern u8 D_800E0495[];



typedef struct S_8008C5C4_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_8008C5C4_1;   /* arg2 in func_8008C5C4 */

typedef struct S_8008C5C4_2 {
    u8 pad_00[0x8C];
    union { void * p; u8 * p2; } unk_8C;   /* accessed as both */
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x80];
    s32 unk_11C;
    u8 pad_120[0x4];
    s32 unk_124;
} S_8008C5C4_2;   /* arg0 in func_8008C5C4 */

typedef struct S_8008C5C4_3 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
} S_8008C5C4_3;   /* temp_v0 in func_8008C5C4 */

typedef struct S_8008C5C4_4 {
    u8 pad_00[0x1484];
    s32 unk_1484;
} S_8008C5C4_4;   /* (void *)tail_page in func_8008C5C4 */

typedef struct S_8008C5C4_5 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8008C5C4_5;   /* temp_a3 in func_8008C5C4 */

typedef struct S_8008C5C4_6 {
    u8 pad_00[0x60];
    void * unk_60;
} S_8008C5C4_6;   /* ((S_8008C5C4_2 *)arg0)->unk_124 in func_8008C5C4 */

s32 func_8008C5C4(S_8008C5C4_2 *arg0, void *arg1, S_8008C5C4_1 *arg2, Rec_D_800E3D7C *arg3) {
    s32 temp_a3;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_v0;
    register u32 tail_page ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s32 tail_result;
    s32 state_value;
    register s32 temp_v1_2 ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */

    temp_v1 = ((u16)arg3->unk_2A.as_u16 >> 8) & 0xE;
    temp_v0 = func_8009B5AC(
        arg3,
        (s16)(arg2->unk_24 + *(u16 *)(D_8006CCD8 + temp_v1)),
        (s16)(arg2->unk_25 + *(u16 *)(D_8006CCE8 + temp_v1)));
    arg0->unk_124 = temp_v0;
    if (temp_v0 != 0) {
        var_v0 = -1;
        if (temp_v0 <= 0) {
            if (!(((S_8008C5C4_3 *)temp_v0)->unk_14 & 0x80000)) {
                arg0->unk_11C = temp_v0;
                arg0->unk_124 = 0;
                return func_8008C730(temp_v0);
            }
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            state_value = *(s32 *)0x80012090;
            if (state_value == 1) {
                ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
                temp_v1_2 = ((S_8008C5C4_3 *)temp_v0)->unk_13;
                if ((temp_v1_2 == 0x39) || (temp_v1_2 == 2)) {
                    if (D_80083170[0] & 0x40) {
                        func_800A56E0(0x506);
                        func_80099844(arg0->unk_124, &D_800E0495);
                        tail_result = 0;
                    } else {
                        tail_result = 0;
                    }
                    ASM_KEEP(tail_result);   /* MATCH pin: keeps a constant in a register as retail does */
                    tail_page = 0x80080000;
                    ASM_KEEP(tail_page);   /* MATCH pin: keeps a statement from moving across a call/branch */
                    ((S_8008C5C4_4 *)((void *)tail_page))->unk_1484 = 0;
                    tail_page = 0x80090000;
                    ASM_KEEP(tail_page);   /* MATCH pin: keeps a statement from moving across a call/branch */
                    tail_page -= 0x5324;
                    arg0->unk_124 = 0;
                    arg0->unk_8C.p = (void *)tail_page;
                    return;
                }
            }
            temp_a3 = arg0->unk_124;
            ((S_8008C5C4_5 *)temp_a3)->unk_1C |= 0x80000;
            arg3->unk_1C.as_s32 |= 0x100000;
            ((S_8008C5C4_6 *)(arg0->unk_124))->unk_60 = arg3;
            func_8009F644(arg3, 0x20, 0, 0);
            func_800A56E0(0x511);
            arg0->unk_9A = 0x1B;
            arg0->unk_9B = 0;
            arg0->unk_8C.p = 0;
            arg2->unk_2C = D_800DCFC8;
            func_80048A44(
                arg2,
                D_800DCFC8[((s32)(D_80083228[0] +
                                         (s16)arg3->unk_2A.as_u16 + 0x100) >>
                                  9) &
                                 7],
                0, 1);
            tail_result = 1;
            ASM_TAILSLOT_PIN(tail_result);   /* MATCH pin: retail delay-slot contents depend on it */
            func_8008c798();
        }
        return var_v0;
    }
    arg0->unk_8C.p2 = D_8008ACDC;
    var_v0 = 0;
    return var_v0;
}

/* MECHANISM: The natural 0x20 frame holds arg0/arg2/arg3 in s0/s2/s1; v1 locals
   split the D_80012090 load and tail page bases, with fences at scheduling seams.
   Branch-local v0 merges and per-site noreturn/tail-slot contracts recover both tails. */

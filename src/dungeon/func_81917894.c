#include "common.h"
#include "m2c_compat.h"

typedef struct S_80025094_0_pre {
    u16 unk_00;
} S_80025094_0_pre;   /* the 0x2 bytes before arg0 in func_80025094, addressed as arg0[-1] */

typedef struct S_80025094_0 {
    void * unk_00;
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    s16 unk_08;
    u16 unk_0A;
    s16 unk_0C;
} S_80025094_0;   /* arg0 in func_80025094 */

typedef struct S_80025094_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80025094_1;   /* temp_v1 in func_80025094 */

typedef struct S_80025094_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80025094_2;   /* arg2 in func_80025094 */

typedef struct S_80025094_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
} S_80025094_3;   /* arg1 in func_80025094 */


M2C_UNK func_80024E80();              /* extern */
void func_80025150(void) __attribute__((noreturn)); /* extern */
void func_800251FC(void) __attribute__((noreturn)); /* extern */
void func_80025254(void) __attribute__((noreturn)); /* extern */
M2C_UNK func_800478B8();                      /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern s32 D_800814A0;

void func_80025094(void *arg0, void *arg1, void *arg2) {
    s32 temp_v0_2;
    s16 temp_v1_2;
    u8 temp_v0;
    void *temp_v1;

    temp_v1 = ((S_80025094_0 *)arg0)->unk_00;
    ((S_80025094_1 *)temp_v1)->unk_14 = (u16) (((S_80025094_1 *)temp_v1)->unk_14 + 1);
    func_800478B8(arg2);
    ((S_80025094_0 *)arg0)->unk_06.s = (u16) (((S_80025094_0 *)arg0)->unk_06.s + 1);
    ((S_80025094_2 *)arg2)->unk_1A = (u16) (((S_80025094_2 *)arg2)->unk_1A + 0x200);
    temp_v1_2 = ((S_80025094_0 *)arg0)->unk_04.s;

    if (temp_v1_2 == 1) {
        goto state_1;
    }
    if (temp_v1_2 < 2) {
        if (temp_v1_2 == 0) {
            goto state_0;
        }
        func_800251FC();
    }
    if (temp_v1_2 == 2) {
        goto state_2;
    }
    func_800251FC();

state_0:
    if (((S_80025094_0 *)arg0)->unk_06.s & 1) {
        u16 tail_value;

        tail_value = ((S_80025094_0 *)arg0)->unk_0A + 2;
        ASM_TAILSLOT_PIN(tail_value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_80025150();
    }
    ((S_80025094_0 *)arg0)->unk_0A =
        (u16) (((S_80025094_0 *)arg0)->unk_0A + 1);
    temp_v0 = ((S_80025094_2 *)arg2)->unk_0E + 3;
    ((S_80025094_2 *)arg2)->unk_0E = temp_v0;
    ((S_80025094_2 *)arg2)->unk_0D = temp_v0;
    ((S_80025094_2 *)arg2)->unk_0C = temp_v0;
    temp_v0_2 = ((S_80025094_0 *)arg0)->unk_06.u << 5;
    ((S_80025094_2 *)arg2)->unk_1E = temp_v0_2;
    ((S_80025094_2 *)arg2)->unk_1C = temp_v0_2;
    ((S_80025094_3 *)arg1)->unk_0A =
        (u16) (((S_80025094_3 *)arg1)->unk_0A - 2);

state_1:
    if ((s16) ((S_80025094_0 *)arg0)->unk_06.s >= 0x20) {
        ((S_80025094_0 *)arg0)->unk_06.s = 0U;
        ((S_80025094_0 *)arg0)->unk_04.u =
            (u16) (((S_80025094_0 *)arg0)->unk_04.u + 1);
        func_800251FC();
    }
    goto common;

state_2:
    if ((s16) ((S_80025094_0 *)arg0)->unk_06.s >=
            ((S_80025094_0 *)arg0)->unk_08) {
        func_80024E80(arg0, arg1);
        (*(u16 *)((u8 *)arg0 + -2)) =
            (u16) (((S_80025094_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
        return;
    }

common:
    ((S_80025094_3 *)arg1)->unk_02 = (s16) (((S_80025094_3 *)arg1)->unk_0E + ((s32) ((func_80064584(((S_80025094_0 *)arg0)->unk_0C) >> 4) * (s16) ((S_80025094_0 *)arg0)->unk_0A) >> 8));
    ((S_80025094_3 *)arg1)->unk_06 = (s16) (((S_80025094_3 *)arg1)->unk_12 + ((s32) ((func_800644B8(((S_80025094_0 *)arg0)->unk_0C) >> 4) * (s16) ((S_80025094_0 *)arg0)->unk_0A) >> 8));
}

/* MECHANISM: Explicit invalid-state predecessors plus a one-sided scheduling barrier
   prevent GCC from merging retail's two dispatcher tails. A guarded $v0 tail-slot pin
   preserves the hidden +2 continuation value; an s32 scale temp forces the signed lh. */

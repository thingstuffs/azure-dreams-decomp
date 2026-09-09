#include "common.h"
#include "m2c_compat.h"

typedef struct S_80024CD4_0_pre {
    u16 unk_00;
} S_80024CD4_0_pre;   /* the 0x2 bytes before arg0 in func_80024CD4, addressed as arg0[-1] */

typedef struct S_80024CD4_0 {
    u8 pad_00[0xA];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0xA];
    s16 unk_16;
    union { u16 s; volatile u16 u; s16 p; } unk_18;   /* accessed as both */
    u16 unk_1A;
    u16 unk_1C;
    u8 pad_1E[0x4];
    s16 unk_22;
} S_80024CD4_0;   /* arg0 in func_80024CD4 */

typedef struct S_80024CD4_1 {
    u8 pad_00[0x6];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_80024CD4_1;   /* arg2 in func_80024CD4 */

typedef struct S_80024CD4_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80024CD4_2;   /* arg1 in func_80024CD4 */


typedef struct {
    u16 value;
    u8 pad[8];
} Counter;

typedef struct {
    s16 value;
    u8 pad[8];
} Flag;

typedef struct {
    s32 value;
    u8 pad[8];
} Flags;

void func_8002522C();
void func_800262AC();
extern Counter D_80026472;
extern Flag D_80026474;
extern Flags D_800814A0;

void func_80024CD4(void *arg0, S_80024CD4_2 *arg1, S_80024CD4_1 *arg2) {
    s16 state;
    u16 temp_a3;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v1_2;
    register void *call_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 call_a1;

    D_80026472.value++;
    state = ((S_80024CD4_0 *)arg0)->unk_0A.s;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        temp_v0 = 0x20;
        arg2->unk_0C = temp_v0;
        goto finish_colors;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }

    temp_v0 = 0x20;
    arg2->unk_0C = temp_v0;
    goto finish_colors;

state_0:
    temp_v0 = arg2->unk_06.s + 0x80;
    arg2->unk_06.s = temp_v0;
    if ((s16) temp_v0 < 0x101) {
        temp_v0 = 0x20;
        goto finish;
    }
    arg2->unk_06.s = 0x100U;
    if (((S_80024CD4_0 *)arg0)->unk_22 < 0x61) {
        call_a0 = arg1;
        call_a1 = ((S_80024CD4_0 *)arg0)->unk_16;
        temp_v1_2 = ((S_80024CD4_0 *)arg0)->unk_18.s;
        temp_a3 = ((S_80024CD4_0 *)arg0)->unk_1C;
        ASM_USE2(temp_v1_2, temp_a3);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        temp_v1_2 =
            (u16) (temp_v1_2 - ((s32) (temp_v1_2 << 0x10) >> 0x13));
        temp_a3 += 0x80;
        ASM_USE(temp_a3);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        ((S_80024CD4_0 *)arg0)->unk_1C = temp_a3;
        ((S_80024CD4_0 *)arg0)->unk_18.u = temp_v1_2;
        func_8002522C(call_a0, call_a1,
            ((S_80024CD4_0 *)arg0)->unk_18.p, (s16) temp_a3,
            arg0 - 0x20);
    }
    ((S_80024CD4_0 *)arg0)->unk_0A.u++;
    if (((S_80024CD4_0 *)arg0)->unk_22 != 0x6F) {
        temp_v0 = 0x20;
        goto finish;
    }
    D_80026474.value = 1;
    goto set_20;

state_1:
    if (D_80026474.value == 0) {
        goto set_20;
    }
    arg2->unk_06.u = -0x100;
    ((S_80024CD4_0 *)arg0)->unk_1A = 0x10U;
    ((S_80024CD4_0 *)arg0)->unk_0A.u++;
    goto set_20;

state_2:
    temp_v0_2 = ((S_80024CD4_0 *)arg0)->unk_1A - 1;
    ((S_80024CD4_0 *)arg0)->unk_1A = temp_v0_2;
    if ((temp_v0_2 << 0x10) > 0) {
        temp_v0 = 0x20;
        goto finish;
    }
    ((S_80024CD4_0 *)arg0)->unk_0A.u++;

state_3:
    temp_v0_3 = arg2->unk_06.s + 0x80;
    arg2->unk_06.s = temp_v0_3;
    if ((s16) temp_v0_3 >= 0) {
        ((S_80024CD4_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0.value |= 0x8000;
    }

set_20:
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    temp_v0 = 0x20;

finish:
    arg2->unk_0C = temp_v0;
finish_colors:
    arg2->unk_0D = 0xE0;
    arg2->unk_0E = 0x40;
    func_800262AC(arg1->unk_02, arg1->unk_06, arg1->unk_0A);
}

/* MECHANISM: Padded globals force retail hi/lo bases; goto layout preserves the state CFG and noreturn tails.
   A volatile u16 store forces the sh/lh narrowing round trip, while the set_20 fence fixes its delay-slot edge.
   Guarded a0/a1 pins plus zero-byte liveness fences reproduce the final call-argument schedule. */

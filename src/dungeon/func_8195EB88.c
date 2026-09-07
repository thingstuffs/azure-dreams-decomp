#include "common.h"

typedef struct S_8195EB88_0_pre {
    u16 unk_00;
} S_8195EB88_0_pre;   /* the 0x2 bytes before arg0 in func_8195EB88, addressed as arg0[-1] */

typedef struct S_8195EB88_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0x30];
    u16 unk_40;
    u16 unk_42;
    union { s16 s; u16 u; } unk_44;   /* accessed as both */
    u8 pad_46[0x2];
    union { s16 s; u16 u; } unk_48;   /* accessed as both */
    s16 unk_4A;
} S_8195EB88_0;   /* arg0 in func_8195EB88 */

typedef struct S_8195EB88_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_8195EB88_1;   /* temp_s0 in func_8195EB88 */

typedef struct S_8195EB88_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8195EB88_2;   /* arg1 in func_8195EB88 */

typedef struct S_8195EB88_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8195EB88_3;   /* temp_a0_2 in func_8195EB88 */

typedef struct S_8195EB88_4 {
    u8 pad_00[0xC];
    union { u8 u8; u32 u32; } unk_0C;   /* accessed as both */
} S_8195EB88_4;   /* arg2 in func_8195EB88 */

typedef struct S_8195EB88_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_8195EB88_5;   /* ((S_8195EB88_0 *)arg0)->unk_0C in func_8195EB88 */



extern s32 func_8003DE58(void *, void *, void *, s32);
extern void func_80024414(void) __attribute__((noreturn));
extern s32 func_80027204(void *);
extern void func_8004491C(void *, void *);
extern void func_80024520(void) __attribute__((noreturn));

typedef struct CounterView {
    u16 value;
    u16 pad[5];
} CounterView;

typedef struct FlagsView {
    s32 value;
    s32 pad[2];
} FlagsView;

extern CounterView D_80027330;
extern u8 D_80045340[];
extern FlagsView D_800814A0;

void func_8195EB88(void *arg0, S_8195EB88_2 *arg1, S_8195EB88_4 *arg2)
{
    s16 temp_v1;
    u16 temp_a0;
    S_8195EB88_3 *temp_a0_2;
    S_8195EB88_1 *temp_s0;

    D_80027330.value = D_80027330.value + 1;
    temp_v1 = ((S_8195EB88_0 *)arg0)->unk_48.s;
    temp_a0 = ((S_8195EB88_0 *)arg0)->unk_48.u;

    if (temp_v1 == 0) {
        temp_s0 = ((S_8195EB88_5 *)(((S_8195EB88_0 *)arg0)->unk_0C))->unk_0C;
        if (((S_8195EB88_0 *)arg0)->unk_4A == 0) {
            if (func_8003DE58(temp_s0->unk_08, temp_s0,
                              (u8 *)arg0 + 0x40, 0) != 0) {
                ((S_8195EB88_0 *)arg0)->unk_4A = 1;
                func_80024414();
            }
            if (temp_s0->unk_14 & 0x8000) {
                ((S_8195EB88_0 *)arg0)->unk_4A = 1;
                ((S_8195EB88_0 *)arg0)->unk_44.s = -0x40;
            }
            if (((S_8195EB88_0 *)arg0)->unk_4A == 0) {
                goto end;
            }
        }

        temp_a0_2 = ((S_8195EB88_5 *)(((S_8195EB88_0 *)arg0)->unk_0C))->unk_08;
        arg1->unk_02 =
            temp_a0_2->unk_02 + ((S_8195EB88_0 *)arg0)->unk_40;
        arg1->unk_06 =
            temp_a0_2->unk_06 + ((S_8195EB88_0 *)arg0)->unk_42;
        arg1->unk_0A =
            temp_a0_2->unk_0A + ((S_8195EB88_0 *)arg0)->unk_44.u;
        if (func_80027204(arg1) != 0) {
            func_8004491C((u8 *)arg0 - 0x20, D_80045340);
            ((S_8195EB88_0 *)arg0)->unk_48.u = ((S_8195EB88_0 *)arg0)->unk_48.u + 1;
            func_80024520();
        }
    } else if (temp_v1 == 1) {
        if (arg2->unk_0C.u8 < 0xC0) {
            arg2->unk_0C.u32 += 0x202020;
            func_80024520();
        }
        ((S_8195EB88_0 *)arg0)->unk_48.u = temp_a0 + 1;
        func_80024520();
    } else if (temp_v1 == 2) {
        arg2->unk_0C.u32 += 0xFFEFEFF0;
        if (arg2->unk_0C.u8 == 0) {
            ((S_8195EB88_0_pre *)arg0)[-1].unk_00 |= 0x8000;
            D_800814A0.value |= 0x8000;
        }
    }
end:
    ;
}

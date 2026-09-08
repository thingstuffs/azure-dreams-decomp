#include "common.h"
#include "records/Rec_func_800249DC_arg0.h"

typedef struct S_819ACB28_0_pre {
    u16 unk_00;
} S_819ACB28_0_pre;   /* the 0x2 bytes before arg0 in func_819ACB28, addressed as arg0[-1] */

typedef struct S_819ACB28_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x18];
    u16 unk_24;
    u16 unk_26;
    union { s16 s; u16 u; } unk_28;   /* accessed as both */
    u8 pad_2A[0x2];
    union { s16 s; u16 u; } unk_2C;   /* accessed as both */
    s16 unk_2E;
} S_819ACB28_0;   /* arg0 in func_819ACB28 */

typedef struct S_819ACB28_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_819ACB28_1;   /* temp_s0 in func_819ACB28 */


typedef struct S_819ACB28_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_819ACB28_3;   /* temp_a0_2 in func_819ACB28 */

typedef struct S_819ACB28_4 {
    u8 pad_00[0xC];
    union { u8 u8; u32 u32; } unk_0C;   /* accessed as both */
} S_819ACB28_4;   /* arg2 in func_819ACB28 */

typedef struct S_819ACB28_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_819ACB28_5;   /* ((S_819ACB28_0 *)arg0)->unk_08 in func_819ACB28 */



extern s32 func_8003DE58(void *, void *, void *, s32);
extern void func_800244A8(void) __attribute__((noreturn));
extern s32 func_800249DC(void *);
extern void func_8004491C(void *, void *);

typedef struct CounterView {
    u16 value;
    u16 pad[5];
} CounterView;

typedef struct FlagsView {
    s32 value;
    s32 pad[2];
} FlagsView;

extern CounterView D_80027452;
extern u8 D_80045340[];
extern FlagsView D_800814A0;

void func_819ACB28(void *arg0, Rec_func_800249DC_arg0 *arg1, S_819ACB28_4 *arg2)
{
    s16 temp_v1;
    u16 temp_a0;
    S_819ACB28_3 *temp_a0_2;
    S_819ACB28_1 *temp_s0;

    D_80027452.value = D_80027452.value + 1;
    temp_v1 = ((S_819ACB28_0 *)arg0)->unk_2C.s;
    temp_a0 = ((S_819ACB28_0 *)arg0)->unk_2C.u;

    if (temp_v1 == 0) {
        temp_s0 = ((S_819ACB28_5 *)(((S_819ACB28_0 *)arg0)->unk_08))->unk_0C;
        if (((S_819ACB28_0 *)arg0)->unk_2E == 0) {
            if (func_8003DE58(temp_s0->unk_08, temp_s0,
                              (u8 *)arg0 + 0x24, 0) == 0) {
                if (temp_s0->unk_14 & 0x8000) {
                    ((S_819ACB28_0 *)arg0)->unk_28.s = -0x40;
                }
            }
            ((S_819ACB28_0 *)arg0)->unk_2E = 1;
        }

        temp_a0_2 = ((S_819ACB28_5 *)(((S_819ACB28_0 *)arg0)->unk_08))->unk_08;
        arg1->unk_00.at02_s16.v =
            temp_a0_2->unk_02 + ((S_819ACB28_0 *)arg0)->unk_24;
        arg1->unk_06 =
            temp_a0_2->unk_06 + ((S_819ACB28_0 *)arg0)->unk_26;
        arg1->unk_0A =
            temp_a0_2->unk_0A + ((S_819ACB28_0 *)arg0)->unk_28.u;
        if (func_800249DC(arg1) != 0) {
            func_8004491C((u8 *)arg0 - 0x20, D_80045340);
            ((S_819ACB28_0 *)arg0)->unk_2C.u = ((S_819ACB28_0 *)arg0)->unk_2C.u + 1;
            func_800244A8();
        }
    } else if (temp_v1 == 1) {
        if (arg2->unk_0C.u8 < 0xC0) {
            arg2->unk_0C.u32 += 0x202020;
            func_800244A8();
        }
        ((S_819ACB28_0 *)arg0)->unk_2C.u = temp_a0 + 1;
        func_800244A8();
    } else if (temp_v1 == 2) {
        arg2->unk_0C.u32 += 0xFFEFEFF0;
        if (arg2->unk_0C.u8 == 0) {
            ((S_819ACB28_0_pre *)arg0)[-1].unk_00 |= 0x8000;
            D_800814A0.value |= 0x8000;
        }
    }
}

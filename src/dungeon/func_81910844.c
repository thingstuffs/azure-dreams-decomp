#include "common.h"

typedef struct S_81910844_0_pre {
    u16 unk_00;
} S_81910844_0_pre;   /* the 0x2 bytes before arg0 in func_81910844, addressed as arg0[-1] */

typedef struct S_81910844_0 {
    void * unk_00;
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    s16 unk_08;
    u8 pad_0A[0x2];
    s32 unk_0C;
} S_81910844_0;   /* arg0 in func_81910844 */

typedef struct S_81910844_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_81910844_1;   /* temp_v1 in func_81910844 */

typedef struct S_81910844_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_81910844_2;   /* arg1 in func_81910844 */

typedef struct S_81910844_3 {
    u8 pad_00[0x1A];
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_81910844_3;   /* arg2 in func_81910844 */


#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 D_800814A0[3];
s32 func_800644B8(s32);

void func_81910844(void *arg0, S_81910844_2 *arg1, S_81910844_3 *arg2) {
    s32 temp_v0;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_a1;
    s32 temp_a0_2;
    u16 temp_v0_2;
    u16 temp_v1_2;
    s16 temp_v1_5;
    s16 temp_v0_3;
    S_81910844_1 *temp_v1;

    temp_v1 = ((S_81910844_0 *)arg0)->unk_00;
    temp_v1->unk_14 =
        (u16) (temp_v1->unk_14 + 1);
    ((S_81910844_0 *)arg0)->unk_06.s =
        (u16) (((S_81910844_0 *)arg0)->unk_06.s + 1);
    temp_v0 = arg1->unk_00;
    temp_v1_4 = arg1->unk_0C;
    temp_v1_3 = arg1->unk_04;
    temp_a1 = arg1->unk_10;
    arg1->unk_00 = temp_v0 + temp_v1_4;
    arg1->unk_04 = temp_v1_3 + temp_a1;
    ((S_81910844_0 *)arg0)->unk_0C =
        ((S_81910844_0 *)arg0)->unk_0C + arg1->unk_14;
    arg1->unk_08 =
        ((S_81910844_0 *)arg0)->unk_0C -
        ((func_800644B8((0x800 / (s16) ((S_81910844_0 *)arg0)->unk_08) *
                       (s16) ((S_81910844_0 *)arg0)->unk_06.s) >> 4) << 0xE);
    temp_a0_2 = 0x200 / (s16) ((S_81910844_0 *)arg0)->unk_08;
    temp_v0_2 = arg2->unk_1A;
    temp_v1_2 = arg2->unk_1E;
    arg2->unk_1A = temp_v0_2 + 0x300;
    temp_v1_2 = temp_v1_2 - temp_a0_2;
    arg2->unk_1E = temp_v1_2;
    arg2->unk_1C = temp_v1_2;
    temp_v1_5 = ((S_81910844_0 *)arg0)->unk_06.u;
    temp_v0_3 = ((S_81910844_0 *)arg0)->unk_08;
    if (temp_v1_5 > temp_v0_3) {
        ((S_81910844_0_pre *)arg0)[-1].unk_00 =
            ((S_81910844_0_pre *)arg0)[-1].unk_00 | 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}

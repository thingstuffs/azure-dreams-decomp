#include "common.h"

typedef struct S_800D4954_0_pre {
    u16 unk_00;
} S_800D4954_0_pre;   /* the 0x2 bytes before arg0 in func_800D4954, addressed as arg0[-1] */

typedef struct S_800D4954_0 {
    u8 pad_00[0x5A];
    u16 unk_5A;
    u8 pad_5C[0x2C];
    void * unk_88;
} S_800D4954_0;   /* arg0 in func_800D4954 */

typedef struct S_800D4954_1_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_800D4954_1_pre;   /* the 0x18 bytes before temp_a0 in func_800D4954, addressed as temp_a0[-1] */

typedef struct S_800D4954_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800D4954_2;   /* arg1 in func_800D4954 */

typedef struct S_800D4954_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800D4954_3;   /* temp_v1 in func_800D4954 */

typedef struct S_800D4954_4 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_800D4954_4;   /* arg2 in func_800D4954 */

typedef struct S_800D4954_5 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_800D4954_5;   /* temp_s1 in func_800D4954 */



extern s32 func_80042900(void *, s32);
extern s32 D_800814A0[3];

void func_800D4954(void *arg0, S_800D4954_2 *arg1, S_800D4954_4 *arg2) {
    u16 temp_v0;
    void *temp_a0;
    S_800D4954_5 *temp_s1;
    S_800D4954_3 *temp_v1;

    temp_a0 = ((S_800D4954_0 *)arg0)->unk_88;
    temp_v1 = ((S_800D4954_1_pre *)temp_a0)[-1].unk_00;
    temp_s1 = temp_a0 - 0x20;
    arg1->unk_02 = temp_v1->unk_02;
    arg1->unk_06 = temp_v1->unk_06;
    arg1->unk_0A = temp_v1->unk_0A - 0x32;
    arg2->unk_0E = 0x28;
    arg2->unk_0D = 0x28;
    arg2->unk_0C = 0x28;
    arg2->unk_1A = arg2->unk_1A + 0x190;
    if (((S_800D4954_0 *)arg0)->unk_5A & 1) {
        arg2->unk_0C = 0x64;
    }
    if (((S_800D4954_0 *)arg0)->unk_5A & 2) {
        arg2->unk_0D = 0x64;
    }
    if (((S_800D4954_0 *)arg0)->unk_5A & 4) {
        arg2->unk_0E = 0x64;
    }
    if (arg2->unk_1C < 0x1800U) {
        temp_v0 = arg2->unk_1E + 0x190;
        arg2->unk_1E = temp_v0;
        arg2->unk_1C = temp_v0;
    }
    if ((func_80042900(temp_a0, 0x1D) << 0x10) == 0) {
        ((S_800D4954_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
    if (temp_s1->unk_1E & 0x8000) {
        ((S_800D4954_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}

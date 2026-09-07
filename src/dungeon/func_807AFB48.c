#include "common.h"
#include "m2c_compat.h"

typedef struct S_807AFB48_3 {
    void * unk_00;
    void * unk_04;
} S_807AFB48_3;   /* arg0 in func_807AFB48 */

typedef struct S_807AFB48_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_807AFB48_4;   /* ((S_807AFB48_3 *)arg0)->unk_04 in func_807AFB48 */

typedef struct S_807AFB48_5 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_807AFB48_5;   /* ((S_807AFB48_3 *)arg0)->unk_00 in func_807AFB48 */


typedef struct S_807AFB48_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_807AFB48_0;   /* arg1 in func_807AFB48 */

typedef struct S_807AFB48_1 {
    u16 unk_00;
    u8 pad_02[0xC];
    s16 unk_0E;
} S_807AFB48_1;   /* arg0 in func_807AFB48; pointer addresses record offset 0x2 */

typedef struct S_807AFB48_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_807AFB48_2;   /* arg2 in func_807AFB48 */


extern s32 D_800814A0[3];

void func_807AFB48(void *arg0, S_807AFB48_0 *arg1, S_807AFB48_2 *arg2) {
    s16 temp_v0;
    s32 temp_a0;
    u8 temp_a0_2;

    arg1->unk_02 = (s16) ((u16) arg1->unk_02 + ((s32) (((S_807AFB48_4 *)(((S_807AFB48_3 *)arg0)->unk_04))->unk_02 - arg1->unk_02) / (s16) ((S_807AFB48_1 *)((u8 *)arg0 - 0x2))->unk_0E));
    arg1->unk_06 = (s16) ((u16) arg1->unk_06 + ((s32) (((S_807AFB48_4 *)(((S_807AFB48_3 *)arg0)->unk_04))->unk_06 - arg1->unk_06) / (s16) ((S_807AFB48_1 *)((u8 *)arg0 - 0x2))->unk_0E));
    arg1->unk_0A = (s16) ((u16) arg1->unk_0A + ((s32) (((S_807AFB48_4 *)(((S_807AFB48_3 *)arg0)->unk_04))->unk_0A - arg1->unk_0A) / (s16) ((S_807AFB48_1 *)((u8 *)arg0 - 0x2))->unk_0E));
    temp_a0 = arg2->unk_0E | (arg2->unk_0C | arg2->unk_0D);
    temp_a0_2 = temp_a0 + ((s32) (0xC0 - temp_a0) / (s16) ((S_807AFB48_1 *)((u8 *)arg0 - 0x2))->unk_0E);
    if (((S_807AFB48_5 *)(((S_807AFB48_3 *)arg0)->unk_00))->unk_14 & 1) {
        arg2->unk_0C = temp_a0_2;
    }
    if (((S_807AFB48_5 *)(((S_807AFB48_3 *)arg0)->unk_00))->unk_14 & 2) {
        arg2->unk_0E = temp_a0_2;
    }
    if (((S_807AFB48_5 *)(((S_807AFB48_3 *)arg0)->unk_00))->unk_14 & 4) {
        arg2->unk_0D = temp_a0_2;
    }
    temp_v0 = (u16) ((S_807AFB48_1 *)((u8 *)arg0 - 0x2))->unk_0E - 1;
    ((S_807AFB48_1 *)((u8 *)arg0 - 0x2))->unk_0E = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        ((S_807AFB48_1 *)((u8 *)arg0 - 0x2))->unk_00 = (u16) (((S_807AFB48_1 *)((u8 *)arg0 - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}

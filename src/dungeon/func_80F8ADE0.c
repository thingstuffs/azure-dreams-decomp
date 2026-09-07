#include "common.h"
#include "m2c_compat.h"

typedef struct S_80F8ADE0_0_pre {
    u16 unk_00;
} S_80F8ADE0_0_pre;   /* the 0x2 bytes before arg0 in func_80F8ADE0, addressed as arg0[-1] */

typedef struct S_80F8ADE0_0 {
    u8 pad_00[0x48];
    u16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
    u8 pad_4E[0xA];
    s32 unk_58;
} S_80F8ADE0_0;   /* arg0 in func_80F8ADE0 */


extern s32 D_800814A0[3];

void func_80F8ADE0(void *arg0) {
    u16 temp_v0;
    u16 var_a1;

    if (((S_80F8ADE0_0 *)arg0)->unk_4C == 8) {
        ((S_80F8ADE0_0 *)arg0)->unk_58 = (s32) (((S_80F8ADE0_0 *)arg0)->unk_58 + 8);
    }
    temp_v0 = ((S_80F8ADE0_0 *)arg0)->unk_48 - 1;
    ((S_80F8ADE0_0 *)arg0)->unk_48 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        var_a1 = 1;
        if (((S_80F8ADE0_0 *)arg0)->unk_4C == 7) {
            var_a1 = 0xA;
        }
        ((S_80F8ADE0_0 *)arg0)->unk_48 = var_a1;
        ((S_80F8ADE0_0 *)arg0)->unk_58 = (s32) ((((S_80F8ADE0_0 *)arg0)->unk_58 == 0) << 7);
        ((S_80F8ADE0_0 *)arg0)->unk_4C = (s16) ((u16) ((S_80F8ADE0_0 *)arg0)->unk_4C + 1);
    }
    if (((S_80F8ADE0_0 *)arg0)->unk_4C == 0xF) {
        ((S_80F8ADE0_0_pre *)arg0)[-1].unk_00 = (u16) (((S_80F8ADE0_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}

#include "common.h"
#include "m2c_compat.h"

typedef struct S_801741A0_0_pre {
    u16 unk_00;
} S_801741A0_0_pre;   /* the 0x2 bytes before arg0 in func_801741A0, addressed as arg0[-1] */

typedef struct S_801741A0_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x17];
    s16 unk_1A;
    u8 pad_1C[0x2];
    u16 unk_1E;
    s16 unk_20;
    u8 pad_22[0x1E];
    s32 unk_40;
    s32 unk_44;
} S_801741A0_0;   /* arg0 in func_801741A0 */

typedef struct S_801741A0_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801741A0_1;   /* arg1 in func_801741A0 */

typedef struct S_801741A0_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_801741A0_2;   /* arg2 in func_801741A0 */


M2C_UNK func_800478B8();                      /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 rand();                                /* extern */
M2C_UNK func_8017406C();      /* extern */
extern s32 D_800814A0[3];

void func_801741A0(void *arg0, S_801741A0_1 *arg1, S_801741A0_2 *arg2) {
    s16 temp_a0;
    s16 temp_v0;
    s16 temp_v0_2;

    temp_v0 = ((S_801741A0_0 *)arg0)->unk_1E - 0x12C;
    ((S_801741A0_0 *)arg0)->unk_1E = (u16) temp_v0;
    arg1->unk_00 = (s32) (((S_801741A0_0 *)arg0)->unk_40 + (func_80064584(temp_v0) * 0x280));
    arg1->unk_04 = (s32) (((S_801741A0_0 *)arg0)->unk_44 + (func_800644B8((s16) ((S_801741A0_0 *)arg0)->unk_1E) * 0x280));
    arg1->unk_08 = (s32) (arg1->unk_08 + 0xFFF60000);
    func_800478B8(arg2);
    if ((((S_801741A0_0 *)arg0)->unk_1A < 0x11) && (((S_801741A0_0 *)arg0)->unk_20 == 0) && !(rand() & 0xF)) {
        func_8017406C(arg0, arg1, arg2);
    }
    temp_a0 = ((S_801741A0_0 *)arg0)->unk_1A;
    if (temp_a0 < 0xA) {
        arg2->unk_0C = (s8) ((((S_801741A0_0 *)arg0)->unk_00 * temp_a0) / 9);
        arg2->unk_0D = (s8) ((((S_801741A0_0 *)arg0)->unk_01 * ((S_801741A0_0 *)arg0)->unk_1A) / 9);
        arg2->unk_0E = (s8) ((((S_801741A0_0 *)arg0)->unk_02 * ((S_801741A0_0 *)arg0)->unk_1A) / 9);
    }
    temp_v0_2 = (u16) ((S_801741A0_0 *)arg0)->unk_1A - 1;
    ((S_801741A0_0 *)arg0)->unk_1A = temp_v0_2;
    if ((temp_v0_2 << 0x10) <= 0) {
        ((S_801741A0_0_pre *)arg0)[-1].unk_00 = (u16) (((S_801741A0_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}

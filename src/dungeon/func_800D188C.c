#include "common.h"
#include "m2c_compat.h"

typedef struct S_800D6FEC_0_pre {
    u16 unk_00;
} S_800D6FEC_0_pre;   /* the 0x2 bytes before arg0 in func_800D6FEC, addressed as arg0[-1] */

typedef struct S_800D6FEC_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x18];
    void * unk_B0;
} S_800D6FEC_0;   /* arg0 in func_800D6FEC */

typedef struct S_800D6FEC_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800D6FEC_1;   /* arg1 in func_800D6FEC */

typedef struct S_800D6FEC_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800D6FEC_2;   /* temp_v1 in func_800D6FEC */


M2C_UNK func_800478B8();                     /* extern */
extern s32 D_800814A0[3];

void func_800D6FEC(void *arg0, S_800D6FEC_1 *arg1, M2C_UNK arg2) {
    u16 temp_v0;
    S_800D6FEC_2 *temp_v1;

    temp_v1 = ((S_800D6FEC_0 *)arg0)->unk_B0;
    arg1->unk_02 = (u16) temp_v1->unk_02;
    arg1->unk_06 = (u16) temp_v1->unk_06;
    arg1->unk_0A = (u16) temp_v1->unk_0A;
    func_800478B8(arg2);
    temp_v0 = ((S_800D6FEC_0 *)arg0)->unk_96 - 1;
    ((S_800D6FEC_0 *)arg0)->unk_96 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        ((S_800D6FEC_0_pre *)arg0)[-1].unk_00 = (u16) (((S_800D6FEC_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}

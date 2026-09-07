#include "common.h"

typedef struct S_8196BF24_0_pre {
    u16 unk_00;
} S_8196BF24_0_pre;   /* the 0x2 bytes before arg0 in func_8196BF24, addressed as arg0[-1] */

typedef struct S_8196BF24_0 {
    u8 pad_00[0x2C];
    union { u16 s; s16 u; } unk_2C;   /* accessed as both */
    u8 pad_2E[0x12];
    u8 unk_40;
    u8 unk_41;
} S_8196BF24_0;   /* arg0 in func_8196BF24 */

typedef struct S_8196BF24_1 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_8196BF24_1;   /* arg2 in func_8196BF24 */



extern s32 D_800814A0[3];

void func_8196BF24(void *arg0, s32 arg1, S_8196BF24_1 *arg2) {
    u8 temp_v0;

    ((S_8196BF24_0 *)arg0)->unk_2C.s = (s16)(((S_8196BF24_0 *)arg0)->unk_2C.s - 1);
    arg2->unk_1C = (u16)(arg2->unk_1C - 0x300);
    arg2->unk_1E = (u16)(arg2->unk_1E - 0x200);
    temp_v0 = ((S_8196BF24_0 *)arg0)->unk_40 - 0x18;
    ((S_8196BF24_0 *)arg0)->unk_40 = temp_v0;
    if ((temp_v0 & 0xFF) == 0xE8) {
        ((S_8196BF24_0 *)arg0)->unk_40 = 0x18U;
        ((S_8196BF24_0 *)arg0)->unk_41 = (u8)(((S_8196BF24_0 *)arg0)->unk_41 - 0x20);
    }
    if (((S_8196BF24_0 *)arg0)->unk_2C.u <= 0) {
        ((S_8196BF24_0_pre *)arg0)[-1].unk_00 = (u16)(((S_8196BF24_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32)(D_800814A0[0] | 0x8000);
    }
}

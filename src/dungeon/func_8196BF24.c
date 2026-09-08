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

/* Advance the effect animation and flag completion when its countdown expires. */
void func_8196BF24(void *effect, s32 unused, S_8196BF24_1 *transform) {
    u8 next_u;

    ((S_8196BF24_0 *)effect)->unk_2C.s = (s16)(((S_8196BF24_0 *)effect)->unk_2C.s - 1);
    transform->unk_1C = (u16)(transform->unk_1C - 0x300);
    transform->unk_1E = (u16)(transform->unk_1E - 0x200);
    next_u = ((S_8196BF24_0 *)effect)->unk_40 - 0x18;
    ((S_8196BF24_0 *)effect)->unk_40 = next_u;
    if ((next_u & 0xFF) == 0xE8) {
        ((S_8196BF24_0 *)effect)->unk_40 = 0x18U;
        ((S_8196BF24_0 *)effect)->unk_41 = (u8)(((S_8196BF24_0 *)effect)->unk_41 - 0x20);
    }
    if (((S_8196BF24_0 *)effect)->unk_2C.u <= 0) {
        ((S_8196BF24_0_pre *)effect)[-1].unk_00 = (u16)(((S_8196BF24_0_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32)(D_800814A0[0] | 0x8000);
    }
}

#include "common.h"

typedef struct S_819711E0_0_pre {
    u16 unk_00;
} S_819711E0_0_pre;   /* the 0x2 bytes before arg0 in func_819711E0, addressed as arg0[-1] */

typedef struct S_819711E0_0 {
    u8 pad_00[0x38];
    union { u16 s; s16 u; } unk_38;   /* accessed as both */
    s16 unk_3A;
    u8 pad_3C[0x4];
    void * unk_40;
    u16 unk_44;
    u16 unk_46;
    u16 unk_48;
} S_819711E0_0;   /* arg0 in func_819711E0 */

typedef struct S_819711E0_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_819711E0_1;   /* arg2 in func_819711E0 */

typedef struct S_819711E0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_819711E0_2;   /* arg1 in func_819711E0 */

typedef struct S_819711E0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_819711E0_3;   /* src in func_819711E0 */


extern s16 D_80025FF4;
extern s32 D_800814A0[3];


/* Decrement the timer, update scale and position, and flag completion at zero. */
void func_819711E0(void *state, S_819711E0_2 *position, S_819711E0_1 *scale) {
    s32 scale_factor;
    u16 ticks_left;
    S_819711E0_3 *base_position;

    ticks_left = ((S_819711E0_0 *)state)->unk_38.s - 1;
    scale_factor = (s32) ((s32) (ticks_left << 16) >> 9) / (s16) ((S_819711E0_0 *)state)->unk_3A;
    D_80025FF4 = 1;
    ((S_819711E0_0 *)state)->unk_38.s = ticks_left;
    scale->unk_0E = (s8) scale_factor;
    scale->unk_0D = (s8) scale_factor;
    scale->unk_0C = (s8) scale_factor;

    base_position = ((S_819711E0_0 *)state)->unk_40;
    position->unk_02 = ((S_819711E0_0 *)state)->unk_44;
    position->unk_06 = ((S_819711E0_0 *)state)->unk_46;
    position->unk_0A = ((S_819711E0_0 *)state)->unk_48;
    position->unk_02 = (u16) (position->unk_02 + base_position->unk_02);
    position->unk_06 = (u16) (position->unk_06 + base_position->unk_06);
    position->unk_0A = (u16) (position->unk_0A + base_position->unk_0A);

    if (((S_819711E0_0 *)state)->unk_38.u <= 0) {
        ((S_819711E0_0_pre *)state)[-1].unk_00 |= 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}

#include "common.h"
#include "m2c_compat.h"

typedef struct S_8189E820_0_pre {
    u16 unk_00;
} S_8189E820_0_pre;   /* the 0x2 bytes before arg0 in func_8189E820, addressed as arg0[-1] */

typedef struct S_8189E820_0 {
    s16 unk_00;
    s16 unk_02;
    s32 unk_04;
    void * unk_08;
} S_8189E820_0;   /* arg0 in func_8189E820 */

typedef struct S_8189E820_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8189E820_1;   /* temp_v1 in func_8189E820 */

typedef struct S_8189E820_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8189E820_2;   /* arg1 in func_8189E820 */

typedef struct S_8189E820_3 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_8189E820_3;   /* arg2 in func_8189E820 */

s32 func_800644B8();
extern s32 D_800814A0[3];

/* Advances arcing motion and rotation, then flags completion when the duration expires. */
void func_8189E820(void *state, S_8189E820_2 *motion, S_8189E820_3 *rotation)
{
    s16 next_frame;
    s32 x_pos;
    s32 x_step;
    s32 y_pos;
    s32 y_step;
    S_8189E820_1 *frame_state;

    frame_state = ((S_8189E820_0 *)state)->unk_08;
    frame_state->unk_14 =
        (u16)(frame_state->unk_14 + 1);
    x_pos = motion->unk_00;
    x_step = motion->unk_0C;
    y_pos = motion->unk_04;
    y_step = motion->unk_10;
    motion->unk_00 = x_pos + x_step;
    motion->unk_04 = y_pos + y_step;
    ((S_8189E820_0 *)state)->unk_04 =
        ((S_8189E820_0 *)state)->unk_04 + motion->unk_14;
    motion->unk_08 =
        ((S_8189E820_0 *)state)->unk_04 -
        ((func_800644B8((0x800 / (s16)((S_8189E820_0 *)state)->unk_02) *
                        ((S_8189E820_0 *)state)->unk_00,
                        y_step) >> 4) * 0xC000);
    rotation->unk_1A =
        (u16)(rotation->unk_1A + 0x300);
    next_frame = (u16)((S_8189E820_0 *)state)->unk_00 + 1;
    ((S_8189E820_0 *)state)->unk_00 = next_frame;
    if (((S_8189E820_0 *)state)->unk_02 < next_frame) {
        ((S_8189E820_0_pre *)state)[-1].unk_00 =
            (u16)(((S_8189E820_0_pre *)state)[-1].unk_00 | 0x8000);
        D_800814A0[0] |= 0x8000;
    }
}

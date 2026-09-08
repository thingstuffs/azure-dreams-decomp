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

/* Advance motion and visual animation, flagging completion after the duration. */
void func_81910844(void *state, S_81910844_2 *motion, S_81910844_3 *visual) {
    s32 pos_x;
    s32 pos_y;
    s32 velocity_x;
    s32 velocity_y;
    s32 scale_step;
    u16 angle;
    u16 scale;
    s16 elapsed;
    s16 duration;
    S_81910844_1 *owner;

    owner = ((S_81910844_0 *)state)->unk_00;
    owner->unk_14 =
        (u16) (owner->unk_14 + 1);
    ((S_81910844_0 *)state)->unk_06.s =
        (u16) (((S_81910844_0 *)state)->unk_06.s + 1);
    pos_x = motion->unk_00;
    velocity_x = motion->unk_0C;
    pos_y = motion->unk_04;
    velocity_y = motion->unk_10;
    motion->unk_00 = pos_x + velocity_x;
    motion->unk_04 = pos_y + velocity_y;
    ((S_81910844_0 *)state)->unk_0C =
        ((S_81910844_0 *)state)->unk_0C + motion->unk_14;
    motion->unk_08 =
        ((S_81910844_0 *)state)->unk_0C -
        ((func_800644B8((0x800 / (s16) ((S_81910844_0 *)state)->unk_08) *
                       (s16) ((S_81910844_0 *)state)->unk_06.s) >> 4) << 0xE);
    scale_step = 0x200 / (s16) ((S_81910844_0 *)state)->unk_08;
    angle = visual->unk_1A;
    scale = visual->unk_1E;
    visual->unk_1A = angle + 0x300;
    scale = scale - scale_step;
    visual->unk_1E = scale;
    visual->unk_1C = scale;
    elapsed = ((S_81910844_0 *)state)->unk_06.u;
    duration = ((S_81910844_0 *)state)->unk_08;
    if (elapsed > duration) {
        ((S_81910844_0_pre *)state)[-1].unk_00 =
            ((S_81910844_0_pre *)state)[-1].unk_00 | 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}

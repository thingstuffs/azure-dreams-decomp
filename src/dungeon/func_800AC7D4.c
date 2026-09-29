#include "common.h"
#include "shared/record_ptrs.h"

typedef struct S_800B1F34_0 {
    s16 * unk_00;
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    u16 unk_06;
} S_800B1F34_0;   /* arg0 in func_800B1F34 */

typedef struct S_800B1F34_1 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800B1F34_1;   /* arg1 in func_800B1F34 */

typedef struct S_800B1F34_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800B1F34_2;   /* global in func_800B1F34 */




/* Advances timed motion phases, updates the output offset, and sets the global update flag. */
void func_800B1F34(S_800B1F34_0 *animation, S_800B1F34_1 *motion)
{
    s16 state;
    u16 countdown;
    S_800B1F34_2 *update_state;

    state = animation->unk_04.s;
    switch (state) {
    case 0:
        animation->unk_06 = 0x10;
        animation->unk_04.u++;
    case 1:
        motion->unk_14 -= 0x4000;
        countdown = animation->unk_06 - 1;
        animation->unk_06 = countdown;
        if ((s16)countdown < 0) {
            animation->unk_06 = 0x40;
            animation->unk_04.u++;
        }
        break;
    case 2:
        motion->unk_14 += 0x6000;
        countdown = animation->unk_06 - 1;
        animation->unk_06 = countdown;
        if ((s16)countdown < 0) {
            animation->unk_06 = 0x3C;
            animation->unk_04.u++;
        }
    case 3:
        countdown = animation->unk_06 - 1;
        animation->unk_06 = countdown;
        if ((s16)countdown < 0) {
            motion->unk_14 = 0;
            animation->unk_06 = 0x3C;
            animation->unk_04.u++;
        }
        break;
    }
    update_state = D_800814A8;
    motion->unk_08.at00.v -= motion->unk_14;
    update_state->unk_1C |= 0x40000000;
    *animation->unk_00 = 0x20 - motion->unk_08.at02.v;
}

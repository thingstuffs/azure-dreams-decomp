#include "common.h"

typedef struct S_800CC070_0 {
    u8 pad_00[0x68];
    u16 unk_68;
    union { s16 s; u16 u; } unk_6A;   /* accessed as both */
} S_800CC070_0;   /* arg0 in func_800CC070 */

typedef struct S_800CC070_1 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_14;   /* overlapping accesses */
} S_800CC070_1;   /* arg1 in func_800CC070 */



extern void func_80095388(void *);
extern s16 func_800C2AE8(void *);
extern void func_800C2E84(void *, s32, void *);
extern s32 D_800D6ABC;
extern s32 D_800D6AD0;

/* Advances a jump through ascent and descent, clamping the landing height. */
void func_800CC070(S_800CC070_0 *actor, S_800CC070_1 *motion, s32 animation_id, s16 jump_velocity)
{
    s16 state;

    state = actor->unk_6A.s;
    switch (state) {
    case 0:
        func_800C2E84(actor, animation_id, &D_800D6ABC);
        motion->unk_14.at02.v = jump_velocity;
        actor->unk_6A.u++;
        break;

    case 1:
        motion->unk_08.at00.v += motion->unk_14.at00.v;
        func_80095388(motion);
        if (motion->unk_14.at00.v >= 0) {
            func_800C2E84(actor, animation_id, &D_800D6AD0);
            actor->unk_6A.u++;
        }
        break;

    case 2:
        motion->unk_08.at00.v += motion->unk_14.at00.v;
        if (func_800C2AE8(motion) < motion->unk_08.at02.v) {
            motion->unk_14.at00.v = 0;
            motion->unk_08.at02.v = func_800C2AE8(motion);
            actor->unk_6A.s = 0;
            actor->unk_68++;
        } else {
            func_80095388(motion);
        }
        break;
    }
}

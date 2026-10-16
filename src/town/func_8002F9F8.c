/* Relink of matched town/func_800CE910; every changed retail word is a paired relocation. */
#define D_800D6ABC D_800D6F4C
#define D_800D6AD0 D_800D6F60
#include "common.h"

typedef struct S_800CC070_0 {
    u8 pad_00[0x68];
    u16 unk_68;
    union { s16 s; u16 u; } unk_6A;   /* accessed as both */
} S_800CC070_0;   /* arg0 in func_800CD158 */

typedef struct S_800CC070_1 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_14;   /* overlapping accesses */
} S_800CC070_1;   /* arg1 in func_800CD158 */


extern void townAddHex20000SSignedOffsetHex14(void *);
extern s16 townQueryLoweredTransformPosition(void *);
extern void townInitializeObjectEntries(void *, s32, void *);
extern s32 D_800D6F4C;
extern s32 D_800D6F60;

/* Advances a jump through ascent and descent, clamping the landing height. */
void func_800CD158(S_800CC070_0 *actor, S_800CC070_1 *motion, s32 animation_id, s16 jump_velocity)
{
    s16 state;

    state = actor->unk_6A.s;
    switch (state) {
    case 0:
        townInitializeObjectEntries(actor, animation_id, &D_800D6F4C);
        motion->unk_14.at02.v = jump_velocity;
        actor->unk_6A.u++;
        break;

    case 1:
        motion->unk_08.at00.v += motion->unk_14.at00.v;
        townAddHex20000SSignedOffsetHex14(motion);
        if (motion->unk_14.at00.v >= 0) {
            townInitializeObjectEntries(actor, animation_id, &D_800D6F60);
            actor->unk_6A.u++;
        }
        break;

    case 2:
        motion->unk_08.at00.v += motion->unk_14.at00.v;
        if (townQueryLoweredTransformPosition(motion) < motion->unk_08.at02.v) {
            motion->unk_14.at00.v = 0;
            motion->unk_08.at02.v = townQueryLoweredTransformPosition(motion);
            actor->unk_6A.s = 0;
            actor->unk_68++;
        } else {
            townAddHex20000SSignedOffsetHex14(motion);
        }
        break;
    }
}

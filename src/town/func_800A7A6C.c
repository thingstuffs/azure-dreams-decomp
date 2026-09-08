#include "common.h"

typedef struct S_800A51CC_0 {
    union { struct { s32 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    u8 pad_06[0xA];
    union { struct { s32 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_10;   /* overlapping accesses */
    union { s16 s; u16 u; } unk_14;   /* accessed as both */
    u8 pad_16[0x2];
    s32 unk_18;
    u8 pad_1C[0x4];
    void * unk_20;
} S_800A51CC_0;   /* arg0 in func_800A51CC */

typedef struct S_800A51CC_1 {
    u8 pad_00[0xAC];
    union { struct { s32 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_AC;   /* overlapping accesses */
    union { s16 s; u16 u; } unk_B0;   /* accessed as both */
} S_800A51CC_1;   /* base in func_800A51CC */



extern u8 D_80083160[0xB2];
extern u8 D_800A526C[16];

/* Update current and saved coordinates from the reference, or set state 9 if they differ. */
void func_800A51CC(S_800A51CC_0 *object)
{
    u8 *reference;
    s32 position_pair;
    u16 coord;

    reference = D_80083160;
    position_pair = object->unk_00.at00.v;
    if ((position_pair != ((S_800A51CC_1 *)reference)->unk_AC.at00.v) ||
        (object->unk_04.s != ((S_800A51CC_1 *)reference)->unk_B0.s)) {
        if ((position_pair != object->unk_10.at00.v) ||
            (object->unk_04.s != object->unk_14.s)) {
            object->unk_18 = 9;
            object->unk_20 = D_800A526C;
            return;
        }

        coord = ((S_800A51CC_1 *)reference)->unk_AC.at00u.v;
        object->unk_00.at00u.v = coord;
        object->unk_10.at00u.v = coord;
        coord = ((S_800A51CC_1 *)reference)->unk_AC.at02.v;
        object->unk_00.at02.v = coord;
        object->unk_10.at02.v = coord;
        coord = ((S_800A51CC_1 *)reference)->unk_B0.u;
        object->unk_04.u = coord;
        object->unk_14.u = coord;
    }
}

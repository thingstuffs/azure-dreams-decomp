#include "common.h"
#include "shared/object_flags.h"

typedef struct S_801712C4_0 {
    union { struct { s32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s8 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
    u8 pad_0C[0xB];
    u8 unk_17;
    u8 pad_18[0x1A];
    union { u16 u; s16 s; } unk_32;   /* accessed as both */
    s16 unk_34;
    u8 pad_36[0xA];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
} S_801712C4_0;   /* arg0 in func_801712C4 */

typedef struct S_801712C4_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801712C4_1;   /* arg1 in func_801712C4 */



extern void func_801710B8(void *, void *, s32);

/* Advance the effect, then move and fade it until its timer expires. */
void func_801712C4(void *effect, void *position, s32 update_param)
{
    s32 state;

    state = ((S_801712C4_0 *)effect)->unk_17;
    ((S_801712C4_0 *)effect)->unk_32.u = ((S_801712C4_0 *)effect)->unk_32.u - 1;
    switch (state) {
    case 0:
        func_801710B8(effect, position, update_param);
        func_801710B8(effect, position, update_param);
        if (((S_801712C4_0 *)effect)->unk_32.s == 0) {
            ((S_801712C4_0 *)effect)->unk_32.u = 0x10;
            ((S_801712C4_0 *)effect)->unk_34 = 0x10;
            ((S_801712C4_0 *)effect)->unk_17++;
        }
        ((S_801712C4_0 *)effect)->unk_08 = ((S_801712C4_0 *)effect)->unk_00.at00.v;
        break;
    case 1:
        ((S_801712C4_1 *)position)->unk_00 += ((S_801712C4_0 *)effect)->unk_40;
        ((S_801712C4_1 *)position)->unk_04 += ((S_801712C4_0 *)effect)->unk_44;
        ((S_801712C4_1 *)position)->unk_08 += ((S_801712C4_0 *)effect)->unk_48;
        ((S_801712C4_1 *)position)->unk_00 += ((S_801712C4_0 *)effect)->unk_40;
        ((S_801712C4_1 *)position)->unk_04 += ((S_801712C4_0 *)effect)->unk_44;
        ((S_801712C4_1 *)position)->unk_08 += ((S_801712C4_0 *)effect)->unk_48;

        ((S_801712C4_0 *)effect)->unk_04.at00.v =
            (((S_801712C4_0 *)effect)->unk_00.at00u.v * ((S_801712C4_0 *)effect)->unk_32.s) /
            ((S_801712C4_0 *)effect)->unk_34;
        ((S_801712C4_0 *)effect)->unk_04.at01.v =
            (((S_801712C4_0 *)effect)->unk_00.at01.v * ((S_801712C4_0 *)effect)->unk_32.s) /
            ((S_801712C4_0 *)effect)->unk_34;
        ((S_801712C4_0 *)effect)->unk_04.at02.v =
            (((S_801712C4_0 *)effect)->unk_00.at02.v * ((S_801712C4_0 *)effect)->unk_32.s) /
            ((S_801712C4_0 *)effect)->unk_34;
        ((S_801712C4_0 *)effect)->unk_08 = ((S_801712C4_0 *)effect)->unk_04.at00u.v;

        if (((S_801712C4_0 *)effect)->unk_32.s <= 0) {
            (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
        break;
    }
}

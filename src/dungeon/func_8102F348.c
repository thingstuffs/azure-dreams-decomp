#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_8102F348_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; volatile s16 v; } at02u; } unk_08;   /* overlapping accesses */
} S_8102F348_0;   /* arg1 in func_8102F348 */

typedef struct S_8102F348_1_pre {
    u16 unk_00;
} S_8102F348_1_pre;   /* the 0x2 bytes before arg0 in func_8102F348, addressed as arg0[-1] */

typedef struct S_8102F348_1 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x8];
    union { s16 s; u16 u; } unk_1E;   /* accessed as both */
    u16 unk_20;
    u8 pad_22[0x2E];
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
    s32 unk_64;
} S_8102F348_1;   /* arg0 in func_8102F348 */




extern s32 func_800A45D8(u16, u16, s16);
extern s16 func_800BCB04(u16, u16, s16);
extern void func_800478B8(void *);
/* Updates effect motion and collision, grows its sprite, and flags expired effects. */
void func_8102F348(void *effect, S_8102F348_0 *position, Rec_D_80082E80 *sprite) {
    s32 height;

    position->unk_00.at00.v += ((S_8102F348_1 *)effect)->unk_50;
    ((S_8102F348_1 *)effect)->unk_50 += ((S_8102F348_1 *)effect)->unk_5C;
    if ((func_800A45D8(position->unk_00.at02.v, position->unk_04.at02.v,
                       position->unk_08.at02.v) << 16) != 0) {
        position->unk_00.at00.v -= ((S_8102F348_1 *)effect)->unk_50;
        ((S_8102F348_1 *)effect)->unk_50 = 0;
        ((S_8102F348_1 *)effect)->unk_5C = 0;
    }

    position->unk_04.at00.v += ((S_8102F348_1 *)effect)->unk_54;
    ((S_8102F348_1 *)effect)->unk_54 += ((S_8102F348_1 *)effect)->unk_60;
    if ((func_800A45D8(position->unk_00.at02.v, position->unk_04.at02.v,
                       position->unk_08.at02.v) << 16) != 0) {
        position->unk_04.at00.v -= ((S_8102F348_1 *)effect)->unk_54;
        ((S_8102F348_1 *)effect)->unk_54 = 0;
        ((S_8102F348_1 *)effect)->unk_60 = 0;
    }

    position->unk_08.at00.v += ((S_8102F348_1 *)effect)->unk_58;
    ((S_8102F348_1 *)effect)->unk_58 += ((S_8102F348_1 *)effect)->unk_64;
    height = position->unk_08.at02.v;
    if ((func_800BCB04(position->unk_00.at02.v, position->unk_04.at02.v,
                       (s16)((u16)position->unk_08.at02u.v - 4)) - 0x10) < height) {
        ((S_8102F348_1 *)effect)->unk_58 = 0;
        position->unk_08.at02.v = func_800BCB04(
            position->unk_00.at02.v, position->unk_04.at02.v,
            (s16)((u16)position->unk_08.at02.v - 4)) - 0x11;
        position->unk_08.at00u.v = 0;
        if (((S_8102F348_1 *)effect)->unk_14 == 0) {
            ((S_8102F348_1 *)effect)->unk_14 = 1;
            ((S_8102F348_1 *)effect)->unk_1E.s = 0;
        }
    }

    ((S_8102F348_1 *)effect)->unk_20++;
    if ((((S_8102F348_1 *)effect)->unk_20 & 3) == 0) {
        func_800478B8(sprite);
    }

    sprite->unk_1C.at00_u16.v += 100;
    if (sprite->unk_1C.at00_u16.v > 0x1000) {
        sprite->unk_1C.at00_u16.v = 0x1000;
    }

    sprite->unk_1C.at02_u16.v += 100;
    if (sprite->unk_1C.at02_u16.v > 0x1000) {
        sprite->unk_1C.at02_u16.v = 0x1000;
    }

    ((S_8102F348_1 *)effect)->unk_1E.u = ((S_8102F348_1 *)effect)->unk_1E.u - 1;
    if ((s16)((S_8102F348_1 *)effect)->unk_1E.u <= 0) {
        s32 *status_page = (s32 *)0x80080000;
        ((S_8102F348_1_pre *)effect)[-1].unk_00 |= 0x8000;
        status_page[0x14A0 / 4] |= 0x8000;
    }

    if (sprite->unk_14.at00_u16.v & 0x8000) {
        s32 *status_page = (s32 *)0x80080000;
        ((S_8102F348_1_pre *)effect)[-1].unk_00 |= 0x8000;
        status_page[0x14A0 / 4] |= 0x8000;
    }
}

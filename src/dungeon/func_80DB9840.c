#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80171040_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; volatile u16 v; } at02u; struct { u8 pad[0x2]; u16 v; } at02p; } unk_08;   /* overlapping accesses */
} S_80171040_0;   /* arg1 in func_80171040 */

typedef struct S_80171040_1 {
    u8 pad_00[0x96];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x4];
    u16 unk_9E;
    u8 pad_A0[0x4];
    s32 unk_A4;
    s32 unk_A8;
    s32 unk_AC;
    s32 unk_B0;
} S_80171040_1;   /* arg0 in func_80171040 */




extern void func_800478B8(void *arg0);
extern s32 func_800A45D8(u16 arg0, u16 arg1, s16 arg2);
extern s16 func_800BCB04(u16 arg0, u16 arg1, s16 arg2);
extern s32 D_800814A0;

void func_80171040(void *arg0, void *arg1, void *arg2)
{
    s32 height;
    u16 count;

    ((S_80171040_0 *)arg1)->unk_00.at00.v += ((S_80171040_1 *)arg0)->unk_A4;
    ((S_80171040_1 *)arg0)->unk_A4 = (((S_80171040_1 *)arg0)->unk_A4 * 2) / 3;
    if ((s16)func_800A45D8(((S_80171040_0 *)arg1)->unk_00.at02.v,
                           ((S_80171040_0 *)arg1)->unk_04.at02.v,
                           ((S_80171040_0 *)arg1)->unk_08.at02.v) != 0) {
        ((S_80171040_0 *)arg1)->unk_00.at00.v -= ((S_80171040_1 *)arg0)->unk_A4;
        ((S_80171040_1 *)arg0)->unk_A4 = 0;
    }

    ((S_80171040_0 *)arg1)->unk_04.at00.v += ((S_80171040_1 *)arg0)->unk_A8;
    ((S_80171040_1 *)arg0)->unk_A8 = (((S_80171040_1 *)arg0)->unk_A8 * 2) / 3;
    if ((s16)func_800A45D8(((S_80171040_0 *)arg1)->unk_00.at02.v,
                           ((S_80171040_0 *)arg1)->unk_04.at02.v,
                           ((S_80171040_0 *)arg1)->unk_08.at02.v) != 0) {
        ((S_80171040_0 *)arg1)->unk_04.at00.v -= ((S_80171040_1 *)arg0)->unk_A8;
        ((S_80171040_1 *)arg0)->unk_A8 = 0;
    }

    ((S_80171040_0 *)arg1)->unk_08.at00.v += ((S_80171040_1 *)arg0)->unk_AC;
    ((S_80171040_1 *)arg0)->unk_AC += ((S_80171040_1 *)arg0)->unk_B0;

    height = ((S_80171040_0 *)arg1)->unk_08.at02.v;
    if (func_800BCB04(((S_80171040_0 *)arg1)->unk_00.at02.v,
                      ((S_80171040_0 *)arg1)->unk_04.at02.v,
                      (s16)(((S_80171040_0 *)arg1)->unk_08.at02u.v - 4)) - 0x10 < height) {
        ((S_80171040_1 *)arg0)->unk_AC = 0;
        ((S_80171040_0 *)arg1)->unk_08.at02.v = func_800BCB04(
            ((S_80171040_0 *)arg1)->unk_00.at02.v, ((S_80171040_0 *)arg1)->unk_04.at02.v,
            (s16)(((S_80171040_0 *)arg1)->unk_08.at02p.v - 4)) - 0x11;
        ((S_80171040_0 *)arg1)->unk_08.at00u.v = 0;
        if (((S_80171040_1 *)arg0)->unk_98 == 0) {
            ((S_80171040_1 *)arg0)->unk_98 = 1;
            ((S_80171040_1 *)arg0)->unk_96 = 0;
        }
    }

    ((S_80171040_1 *)arg0)->unk_9E++;
    func_800478B8(arg2);
    count = ((S_80171040_1 *)arg0)->unk_96 - 1;
    ((S_80171040_1 *)arg0)->unk_96 = count;
    if ((s16)count <= 0) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

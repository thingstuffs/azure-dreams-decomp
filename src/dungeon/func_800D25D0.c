#include "common.h"
#include "records/Rec_D_80082E80.h"


extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 rand(void);
extern s32 D_800814A0;
extern u16 D_80083460[];


typedef struct S_800D7D30_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800D7D30_0;   /* arg1 in func_800D7D30 */

typedef struct S_800D7D30_1 {
    u8 pad_00[0xC];
    u16 unk_0C;
    u16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x6];
    union { s16 s; u16 u; } unk_18;   /* accessed as both */
    u8 pad_1A[0x2];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_1C;   /* overlapping accesses */
    u8 pad_20[0x8];
    s32 unk_28;
    u8 pad_2C[0x8];
    s32 unk_34;
    u8 pad_38[0x14];
    union { s16 s; u16 u; } unk_4C;   /* accessed as both */
} S_800D7D30_1;   /* arg0 in func_800D7D30 */


void func_800D7D30(void *arg0, void *arg1, void *arg2) {
    register s32 x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 z;
    s32 dz;
    s32 value;
    u32 c0;
    u32 c1;
    u32 c2;
    s16 state;

    z = ((S_800D7D30_0 *)arg1)->unk_10;
    dz = ((S_800D7D30_0 *)arg1)->unk_14;
    ((S_800D7D30_0 *)arg1)->unk_00.at00.v += ((S_800D7D30_0 *)arg1)->unk_0C;
    ((S_800D7D30_0 *)arg1)->unk_04.at00.v += z;
    ((S_800D7D30_0 *)arg1)->unk_08.at00.v += dz;

    state = ((S_800D7D30_1 *)arg0)->unk_4C.s;
    if (state != 0) {
        if (state == 1) {
            goto state_one;
        }
        return;
    }

    func_800478B8(arg2);
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000) {
        ((Rec_D_80082E80 *)arg2)->unk_04.as_s8 = 0;
        ((Rec_D_80082E80 *)arg2)->unk_05.as_s8 = 0;
    }

    ((S_800D7D30_0 *)arg1)->unk_00.at02.v = (s16)(((S_800D7D30_1 *)arg0)->unk_0C +
        ((func_800644B8(((S_800D7D30_1 *)arg0)->unk_18.s) *
          ((S_800D7D30_1 *)arg0)->unk_1C.at02.v) >> 12));
    ((S_800D7D30_0 *)arg1)->unk_04.at02.v = (s16)(((S_800D7D30_1 *)arg0)->unk_0E +
        ((func_80064584(((S_800D7D30_1 *)arg0)->unk_18.s) *
          ((S_800D7D30_1 *)arg0)->unk_1C.at02.v) >> 12));

    ((S_800D7D30_0 *)arg1)->unk_14 += 0xFFFE0000 +
        ((rand() & 0xFF) << 9);
    ((S_800D7D30_1 *)arg0)->unk_18.s = (s16)(((S_800D7D30_1 *)arg0)->unk_18.u + 0x80 +
        (rand() & 0x3F));

    do {
    } while (0);

    x = ((S_800D7D30_1 *)arg0)->unk_28 + ((S_800D7D30_1 *)arg0)->unk_34;
    ((S_800D7D30_1 *)arg0)->unk_28 = x;
    value = ((S_800D7D30_1 *)arg0)->unk_1C.at00.v;
    if (value <= 0) {
        x >>= 2;
    }
    ((S_800D7D30_1 *)arg0)->unk_1C.at00.v = value + x;

    c0 = ((Rec_D_80082E80 *)arg2)->unk_0C.at00_u8.v;
    c1 = ((Rec_D_80082E80 *)arg2)->unk_0C.at01_u8.v;
    ((Rec_D_80082E80 *)arg2)->unk_0C.at00_u8.v = c0 - (c0 >> 4);
    ((Rec_D_80082E80 *)arg2)->unk_0C.at01_u8.v = c1 - (c1 >> 4);
    c2 = ((Rec_D_80082E80 *)arg2)->unk_0C.at02_u8.v;
    ((Rec_D_80082E80 *)arg2)->unk_0C.at02_u8.v = c2 - (c2 >> 4);
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000) {
        ((Rec_D_80082E80 *)arg2)->unk_04.as_s8 = 0;
        ((Rec_D_80082E80 *)arg2)->unk_05.as_s8 = 0;
    }

    if (((S_800D7D30_0 *)arg1)->unk_08.at02.v < ((S_800D7D30_1 *)arg0)->unk_10 - 0x60) {
        ((S_800D7D30_1 *)arg0)->unk_4C.u++;
        return;
    }
    return;

state_one:
    {
        u16 *fixed = D_80083460;
        fixed[5]--;
    }
    (*(u16 *)((u8 *)arg0 + (-2))) |= 0x8000;
    D_800814A0 |= 0x8000;
}

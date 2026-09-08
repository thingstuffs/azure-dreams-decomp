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


/* Update a spiraling effect's motion and color, then retire it below its height limit. */
void func_800D7D30(void *effect, void *motion, void *sprite) {
    register s32 radius_step ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 velocity_y;
    s32 velocity_z;
    s32 radius;
    u32 red;
    u32 green;
    u32 blue;
    s16 state;

    velocity_y = ((S_800D7D30_0 *)motion)->unk_10;
    velocity_z = ((S_800D7D30_0 *)motion)->unk_14;
    ((S_800D7D30_0 *)motion)->unk_00.at00.v += ((S_800D7D30_0 *)motion)->unk_0C;
    ((S_800D7D30_0 *)motion)->unk_04.at00.v += velocity_y;
    ((S_800D7D30_0 *)motion)->unk_08.at00.v += velocity_z;

    state = ((S_800D7D30_1 *)effect)->unk_4C.s;
    if (state != 0) {
        if (state == 1) {
            goto retire;
        }
        return;
    }

    func_800478B8(sprite);
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
        ((Rec_D_80082E80 *)sprite)->unk_04.as_s8 = 0;
        ((Rec_D_80082E80 *)sprite)->unk_05.as_s8 = 0;
    }

    ((S_800D7D30_0 *)motion)->unk_00.at02.v = (s16)(((S_800D7D30_1 *)effect)->unk_0C +
        ((func_800644B8(((S_800D7D30_1 *)effect)->unk_18.s) *
          ((S_800D7D30_1 *)effect)->unk_1C.at02.v) >> 12));
    ((S_800D7D30_0 *)motion)->unk_04.at02.v = (s16)(((S_800D7D30_1 *)effect)->unk_0E +
        ((func_80064584(((S_800D7D30_1 *)effect)->unk_18.s) *
          ((S_800D7D30_1 *)effect)->unk_1C.at02.v) >> 12));

    ((S_800D7D30_0 *)motion)->unk_14 += 0xFFFE0000 +
        ((rand() & 0xFF) << 9);
    ((S_800D7D30_1 *)effect)->unk_18.s = (s16)(((S_800D7D30_1 *)effect)->unk_18.u + 0x80 +
        (rand() & 0x3F));

    do {
    } while (0);

    radius_step = ((S_800D7D30_1 *)effect)->unk_28 + ((S_800D7D30_1 *)effect)->unk_34;
    ((S_800D7D30_1 *)effect)->unk_28 = radius_step;
    radius = ((S_800D7D30_1 *)effect)->unk_1C.at00.v;
    if (radius <= 0) {
        radius_step >>= 2;
    }
    ((S_800D7D30_1 *)effect)->unk_1C.at00.v = radius + radius_step;

    red = ((Rec_D_80082E80 *)sprite)->unk_0C.at00_u8.v;
    green = ((Rec_D_80082E80 *)sprite)->unk_0C.at01_u8.v;
    ((Rec_D_80082E80 *)sprite)->unk_0C.at00_u8.v = red - (red >> 4);
    ((Rec_D_80082E80 *)sprite)->unk_0C.at01_u8.v = green - (green >> 4);
    blue = ((Rec_D_80082E80 *)sprite)->unk_0C.at02_u8.v;
    ((Rec_D_80082E80 *)sprite)->unk_0C.at02_u8.v = blue - (blue >> 4);
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
        ((Rec_D_80082E80 *)sprite)->unk_04.as_s8 = 0;
        ((Rec_D_80082E80 *)sprite)->unk_05.as_s8 = 0;
    }

    if (((S_800D7D30_0 *)motion)->unk_08.at02.v < ((S_800D7D30_1 *)effect)->unk_10 - 0x60) {
        ((S_800D7D30_1 *)effect)->unk_4C.u++;
        return;
    }
    return;

retire:
    {
        u16 *counters = D_80083460;
        counters[5]--;
    }
    (*(u16 *)((u8 *)effect + (-2))) |= 0x8000;
    D_800814A0 |= 0x8000;
}

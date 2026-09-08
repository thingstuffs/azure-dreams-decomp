#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_801725D0_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    s8 unk_6D;
    u8 pad_6E[0x1A];
    u16 unk_88;
} S_801725D0_0;   /* arg3 in func_801725D0 */

typedef struct S_801725D0_1 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_90;   /* overlapping accesses */
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xA];
    s16 unk_A6;
} S_801725D0_1;   /* arg0 in func_801725D0 */


typedef struct S_801725D0_3_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_801725D0_3_pre;   /* the 0x18 bytes before linked in func_801725D0, addressed as linked[-1] */

typedef struct S_801725D0_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801725D0_4;   /* entry in func_801725D0 */




extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern s16 func_800BCB04(s32, s32, s16);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_800E3DE8;
extern s32 D_80170E5C;
extern u8 D_80173D04[];
extern u8 D_80173D34[];

/* Advances the actor's movement sequence and resets motion and animation on landing. */
void func_801725D0(void *action, void *motion, void *sprite, void *actor)
{
    s32 direction_offset;
    s32 x_step;
    s32 y_step;
    s32 ticks_left;
    s32 state;
    s32 height_delta;

    direction_offset = (((S_801725D0_0 *)actor)->unk_2A.s >> 8) & 0xE;
    x_step = *(s16 *)((u8 *)&D_8006CCD8 + direction_offset);
    ticks_left = ((S_801725D0_1 *)action)->unk_96.s - 1;
    y_step = *(s16 *)((u8 *)&D_8006CCE8 + direction_offset);
    state = ((S_801725D0_1 *)action)->unk_9B;
    ((S_801725D0_1 *)action)->unk_96.s = ticks_left;

    if (state == 2) {
        goto state_2;
    }
    if ((s32)state < 3) {
        if (state == 0) {
            goto state_0;
        }
        if (state == 1) {
            goto state_1;
        }
        goto done;
    }
    if (state == 3) {
        goto state_3;
    }
    if (state == 0xFF) {
        goto state_ff;
    }
    goto done;

state_0:
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
        ((S_801725D0_1 *)action)->unk_9B = 0xFF;
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
        func_8009C12C(actor, sprite, ((S_801725D0_0 *)actor)->unk_2A.u, 1);
        goto done;
    }

    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80173D34;
    func_80047784(
        sprite,
        D_80173D34[((D_80083228 + ((S_801725D0_0 *)actor)->unk_2A.u + 0x100) >> 9) & 7],
        0);

    if (((S_801725D0_0 *)actor)->unk_60 != 0) {
        void *linked = ((S_801725D0_0 *)actor)->unk_60;
        void *height_entry = ((S_801725D0_3_pre *)linked)[-1].unk_00;
        ((S_801725D0_1 *)action)->unk_A6 = ((S_801725D0_4 *)height_entry)->unk_0A - 0x34;
    } else {
        ((S_801725D0_1 *)action)->unk_A6 =
            func_800BCB04(
                ((((Rec_D_80082E80 *)sprite)->unk_24 + x_step) << 6) & 0xFFC0,
                ((((Rec_D_80082E80 *)sprite)->unk_25 + y_step) << 6) & 0xFFC0,
                (s16)(((S_801725D0_0 *)actor)->unk_88 - 0xA0)) - 0x34;
    }
    ((S_801725D0_1 *)action)->unk_96.s = 2;
    ((S_801725D0_1 *)action)->unk_9B++;
    goto done;

state_1:
    ((S_801725D0_1 *)action)->unk_90.at02.v +=
        (((S_801725D0_1 *)action)->unk_A6 - ((Rec_D_800E3D7C *)motion)->unk_08.at02_s16.v) / 3;
    if (((S_801725D0_1 *)action)->unk_96.u > 0) {
        goto done;
    }

    ((S_801725D0_1 *)action)->unk_98 |= 8;
    ((S_801725D0_0 *)actor)->unk_1C &= 0xF7FFFFFF;
    ((S_801725D0_1 *)action)->unk_90.at02u.v = -0x18;
    ((S_801725D0_1 *)action)->unk_96.s = 4;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 =
        (x_step << 22) / ((S_801725D0_1 *)action)->unk_96.u;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = (y_step << 22) / ((S_801725D0_1 *)action)->unk_96.u;
    ((S_801725D0_1 *)action)->unk_9B++;
    goto done;

state_2:
    ((S_801725D0_1 *)action)->unk_90.at00.v +=
        ((((S_801725D0_1 *)action)->unk_A6 - ((Rec_D_800E3D7C *)motion)->unk_08.at02_s16.v) / 3) << 16;
    if (((S_801725D0_1 *)action)->unk_96.u > 0) {
        goto done;
    }
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    ((S_801725D0_1 *)action)->unk_96.s = 10;
    ((S_801725D0_1 *)action)->unk_9B++;
    goto done;

state_3:
    height_delta = ((s32)(ticks_left << 16) >> 4) + 0x2000;
    ((S_801725D0_1 *)action)->unk_90.at00.v -= height_delta;
    if (((S_801725D0_1 *)action)->unk_96.u == 6) {
        func_800A56E0(0x808);
    }
    if (((S_801725D0_1 *)action)->unk_96.u == 2) {
        func_8009C12C(actor, sprite, ((S_801725D0_0 *)actor)->unk_2A.u, 1);
    }
    if (((S_801725D0_1 *)action)->unk_96.u > 0) {
        goto done;
    }
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = (0 - x_step) << 19;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = (0 - y_step) << 19;
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0xFFF80000;
    ((S_801725D0_1 *)action)->unk_9B = 0xFF;
    goto done;

state_ff:
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 += 0x18000;
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    ((S_801725D0_1 *)action)->unk_98 &= 0xFFF7;
    ((S_801725D0_0 *)actor)->unk_1C |= 0x08000000;
    ((S_801725D0_1 *)action)->unk_90.at00.v = 0;
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80173D04;
    func_80047784(
        sprite,
        D_80173D04[((D_80083228 + ((S_801725D0_0 *)actor)->unk_2A.u + 0x100) >> 9) & 7],
        0);
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    func_800AD594(actor, 0x100);
    ((S_801725D0_1 *)action)->unk_8C = &D_80170E5C;
    D_8008346C = 0;
    func_800A4ACC(actor);
    if (((S_801725D0_0 *)actor)->unk_6D == 0) {
        ((S_801725D0_0 *)actor)->unk_46 &= 0x7FFF;
    } else {
        D_800E3DE8 = (u8 *)actor - 0x20;
    }

done:
    return;
}

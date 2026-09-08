#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


typedef struct Node Node;


typedef struct S_80172908_1 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172908_1;   /* arg0 in func_80172908 */




extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern Node *D_800E3DE8[];
extern u8 D_801710F4[];
extern u8 D_80174F30;

/* Updates movement animation and settles the actor at its target tile. */
void func_80172908(void *action, void *motion, void *sprite, void *actor)
{
    s32 state;
    s32 wait_state;
    s32 direction_offset;
    s32 direction_x;
    s32 direction_y;
    u16 frames_left;

    direction_offset = ((u16)((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 >> 8) & 0xE;
    direction_x = *(s16 *)((u8 *)&D_8006CCD8 + direction_offset);
    direction_y = *(s16 *)((u8 *)&D_8006CCE8 + direction_offset);
    state = ((S_80172908_1 *)action)->unk_9B;
    wait_state = 1;
    if (state == wait_state) {
        goto state_1;
    }
    if (!(state < 2)) {
        goto state_ge_2;
    }
    if (state == 0) {
        goto state_0;
    }
    goto end;

state_ge_2:
    if (state == 2) {
        goto state_2;
    }
    if (state == 0xFF) {
        goto state_ff;
    }
    goto end;

state_0:
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
        ((S_80172908_1 *)action)->unk_9B = 0xFF;
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
        func_8009C12C(actor, sprite, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1);
        goto end;
    }

    (*(u8 * *)((u8 *)sprite + 0x2C)) = &D_80174F30;
    func_80047784(sprite,
        *(&D_80174F30 +
          (((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7)),
        0);
    goto bump_state;

state_1:
    if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == state &&
         (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
        (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        func_800A56E0(0x808);
        ((S_80172908_1 *)action)->unk_90 = 0;
        ((S_80172908_1 *)action)->unk_98 |= 8;
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = (s32)0xFFF50000;
        ((S_80172908_1 *)action)->unk_96.s = 4;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = (direction_x << 23) / 5;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = (direction_y << 23) / 5;
        goto bump_state;
    }
    goto end;

bump_state:
    ((S_80172908_1 *)action)->unk_9B++;
    goto end;

state_2:
    frames_left = ((S_80172908_1 *)action)->unk_96.s - 1;
    ((S_80172908_1 *)action)->unk_96.s = frames_left;
    if ((s16)frames_left == 3) {
        func_8009C12C(actor, sprite, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1);
    }

    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 += (5 - ((S_80172908_1 *)action)->unk_96.u) << 16;
    if (((S_80172908_1 *)action)->unk_96.u < 3) {
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    }
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 -= (((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 << 2) / 5;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v -= (((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v << 2) / 5;
    if (((S_80172908_1 *)action)->unk_96.u > 0) {
        goto end;
    }
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((S_80172908_1 *)action)->unk_9B = 0xFF;
    ((S_80172908_1 *)action)->unk_98 &= 0xFFF7;
    goto end;

state_ff:
    {
        s32 target_x = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
        s32 current_x = ((Rec_D_800E3D7C *)motion)->unk_00.at02_s16.v - 0x20;

        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = (target_x - current_x) << 14;
    }
    {
        s32 target_y = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
        s32 current_y = ((Rec_D_800E3D7C *)motion)->unk_04.at02_s16.v - 0x20;

        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = (target_y - current_y) << 14;
    }
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        goto end;
    }
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    func_800AD594(actor, 0x100);
    ((S_80172908_1 *)action)->unk_8C = D_801710F4;
    D_8008346C = 0;
    func_800A4ACC(actor);
    if (((Rec_D_800E3D7C *)actor)->unk_6D.as_s8 == 0) {
        ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v &= 0x7FFF;
    } else {
        D_800E3DE8[0] = (Node *)((u8 *)actor - 0x20);
    }
end:
    return;
}

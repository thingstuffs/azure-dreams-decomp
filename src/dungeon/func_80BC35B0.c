#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80170838[16];
extern s32 D_801719DC;
extern u8 D_8017464C[8];
extern u8 D_80174654[8];
extern u8 D_8017465C[8];
extern u8 D_80174664[8];


typedef struct S_80172DB0_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
    u8 pad_A8[0x4];
    s32 unk_AC;
    s32 unk_B0;
} S_80172DB0_0;   /* arg0 in func_80172DB0 */



typedef struct S_80172DB0_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172DB0_3;   /* arg1 in func_80172DB0 */

/* Updates a staged jump animation and returns the actor to its tile center. */
void func_80172DB0(void *action, void *motion, void *sprite, void *actor)
{
    u8 state;
    static void *const state_labels[] = { &&start, &&windup, &&jump, &&land, &&recenter, &&finish };

    state = ((S_80172DB0_0 *)action)->unk_9B;
    if ((u32)state >= 6) {
        return;
    }
    goto *(((void **)D_80170838)[state]);

start:
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
        ((S_80172DB0_0 *)action)->unk_9B = 5;
        ((S_80172DB0_0 *)action)->unk_96.u = 0;
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
        func_8009C12C(actor, sprite, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1);
        return;
    }
    ((S_80172DB0_3 *)motion)->unk_14 = 0;
    ((S_80172DB0_3 *)motion)->unk_10 = 0;
    ((S_80172DB0_3 *)motion)->unk_0C = 0;
    if (((S_80172DB0_0 *)action)->unk_A4 != 0) {
        return;
    }
    (*(u8 * *)((u8 *)sprite + (0x2C))) = D_8017464C;
    func_80047784(sprite,
        D_8017464C[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    ((S_80172DB0_0 *)action)->unk_96.u = 8;
    ((S_80172DB0_0 *)action)->unk_9B++;
    return;

windup:
    {
        u16 timer = ((S_80172DB0_0 *)action)->unk_96.u;

        ((S_80172DB0_0 *)action)->unk_96.u = timer - 1;
        if ((s16)timer > 0 && !(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
    }
    (*(u8 * *)((u8 *)sprite + (0x2C))) = D_80174654;
    func_80047784(sprite,
        D_80174654[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    func_800A56E0(0x707);
    ((S_80172DB0_0 *)action)->unk_96.u = 6;
    ((S_80172DB0_0 *)action)->unk_AC = 0x80000;
    ((S_80172DB0_0 *)action)->unk_B0 = (s32)0xFFFE0000;
    ((S_80172DB0_0 *)action)->unk_9B++;
    ((S_80172DB0_3 *)motion)->unk_0C =
        -*(s16 *)(&D_8006CCD8 + (((u16)((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 >> 8) & 0xE)) << 18;
    ((S_80172DB0_3 *)motion)->unk_10 =
        -*(s16 *)(&D_8006CCE8 + (((u16)((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 >> 8) & 0xE)) << 18;
    return;

jump:
    ((S_80172DB0_0 *)action)->unk_A4 += ((S_80172DB0_0 *)action)->unk_AC;
    ((S_80172DB0_0 *)action)->unk_AC += ((S_80172DB0_0 *)action)->unk_B0;
    if (((S_80172DB0_0 *)action)->unk_96.s < 2) {
        ((S_80172DB0_3 *)motion)->unk_0C =
            *(s16 *)(&D_8006CCD8 + (((u16)((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 >> 8) & 0xE)) << 19;
        ((S_80172DB0_3 *)motion)->unk_10 =
            *(s16 *)(&D_8006CCE8 + (((u16)((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 >> 8) & 0xE)) << 19;
    }
    {
        u16 timer = ((S_80172DB0_0 *)action)->unk_96.u;

        ((S_80172DB0_0 *)action)->unk_96.u = timer - 1;
        if ((s16)timer > 0 && !(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
    }
    func_8009C12C(actor, sprite, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1);
    ((S_80172DB0_0 *)action)->unk_9B++;
    func_800A56E0(0x804);
    return;

land:
    ((S_80172DB0_0 *)action)->unk_A4 += ((S_80172DB0_0 *)action)->unk_AC;
    ((S_80172DB0_0 *)action)->unk_AC += ((S_80172DB0_0 *)action)->unk_B0;
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    (*(u8 * *)((u8 *)sprite + (0x2C))) = D_8017465C;
    func_80047784(sprite,
        D_8017465C[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    ((S_80172DB0_0 *)action)->unk_9B++;
    ((S_80172DB0_3 *)motion)->unk_10 = 0;
    ((S_80172DB0_3 *)motion)->unk_0C = 0;
    ((S_80172DB0_0 *)action)->unk_A4 = 0;
    return;

recenter:
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    (*(u8 * *)((u8 *)sprite + (0x2C))) = D_80174664;
    func_80047784(sprite,
        D_80174664[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    ((S_80172DB0_0 *)action)->unk_96.u = 4;
    ((S_80172DB0_0 *)action)->unk_A4 = 0;
    ((S_80172DB0_0 *)action)->unk_9B++;
    {
        s32 target_x = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
        s32 current_x = ((S_80172DB0_3 *)motion)->unk_02 - 0x20;

        ((S_80172DB0_3 *)motion)->unk_0C = ((target_x - current_x) << 16)
            / ((S_80172DB0_0 *)action)->unk_96.s;
    }
    {
        s32 target_y = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
        s32 current_y = ((S_80172DB0_3 *)motion)->unk_06 - 0x20;

        ((S_80172DB0_3 *)motion)->unk_10 = ((target_y - current_y) << 16)
            / ((S_80172DB0_0 *)action)->unk_96.s;
    }
    return;

finish:
    {
        s16 timer = ((S_80172DB0_0 *)action)->unk_96.s;

        if (timer != 0) {
            {
                s32 target_x = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
                s32 current_x = ((S_80172DB0_3 *)motion)->unk_02 - 0x20;

                ((S_80172DB0_3 *)motion)->unk_0C = ((target_x - current_x) << 16) / timer;
            }
            {
                s32 target_y = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
                s32 current_y = ((S_80172DB0_3 *)motion)->unk_06 - 0x20;

                ((S_80172DB0_3 *)motion)->unk_10 = ((target_y - current_y) << 16)
                    / ((S_80172DB0_0 *)action)->unk_96.s;
            }
        }
    }
    ((S_80172DB0_0 *)action)->unk_96.u--;
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    func_800AD594(actor, 0x100);
    ((S_80172DB0_0 *)action)->unk_8C = &D_801719DC;
    D_8008346C = 0;
    func_800A4ACC(actor);
    ((S_80172DB0_3 *)motion)->unk_10 = 0;
    ((S_80172DB0_3 *)motion)->unk_0C = 0;
    ((S_80172DB0_3 *)motion)->unk_02 = (((Rec_D_80082E80 *)sprite)->unk_24 << 6) + 0x20;
    ((S_80172DB0_3 *)motion)->unk_06 = (((Rec_D_80082E80 *)sprite)->unk_25 << 6) + 0x20;
    ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v &= 0x7FFF;
}

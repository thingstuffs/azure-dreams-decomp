#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"


extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_801753DC(void *, void *);

extern s32 D_80171FA4;
extern u8 D_80175C48[];
extern u8 D_80175C50[];
extern u8 D_80175C58[];


typedef struct S_80173408_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    union { u8 n; u8 v; } unk_9B;   /* accessed as both */
    u8 pad_9C[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_A0;   /* overlapping accesses */
    u8 pad_A4[0x4];
    s32 unk_A8;
    s32 unk_AC;
} S_80173408_0;   /* arg0 in func_80173408 */


typedef struct S_80173408_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80173408_2;   /* call_a0 in func_80173408 */


typedef struct S_80173408_4 {
    u8 pad_00[0x2A];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_80173408_4;   /* arg3 in func_80173408 */

/* Updates jump movement, animation, and landing across five states. */
void func_80173408(void *jump, EntityRec *motion, void *sprite, void *actor)
{
    u32 step_x;
    s32 step_y;
    u8 state;

    state = ((S_80173408_0 *)jump)->unk_9B.n;
    switch (state) {

case 0:
    {
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((S_80173408_0 *)jump)->unk_9B.n = 4;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
            func_8009C12C(actor, sprite, ((S_80173408_2 *)actor)->unk_2A, 1);
            return;
        }
    }

case 1:
    motion->unk_0C -=
        *(s16 *)((u8 *)((s8 *)dirStepX) +
                 (((u16)((S_80173408_4 *)actor)->unk_2A.u >> 8) & 0xE)) << 14;
    motion->unk_10 -=
        *(s16 *)((u8 *)((s8 *)dirStepY) +
                 (((u16)((S_80173408_4 *)actor)->unk_2A.u >> 8) & 0xE)) << 14;
    ((S_80173408_0 *)jump)->unk_A0.at00.v += 0x60000;
    if (((S_80173408_0 *)jump)->unk_A0.at02.v >= 0x31) {
        ((S_80173408_0 *)jump)->unk_A0.at02.v = 0x30;
    }
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
        return;
    }
    motion->flags14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    if (((S_80173408_0 *)jump)->unk_A0.at02.v < 0x30) {
        return;
    }
    (*(u8 * *)((u8 *)sprite + (0x2C))) = D_80175C48;
    func_80047784(sprite,
        D_80175C48[((gameWork.view.viewAngle + ((S_80173408_4 *)actor)->unk_2A.s + 0x100) >> 9) & 7],
        0);
    func_801753DC((u8 *)jump - 0x20, (u8 *)actor + 0x2A);
    state = ((S_80173408_0 *)jump)->unk_9B.v;
    ((S_80173408_0 *)jump)->unk_96.s = 0;
    goto increment_state;

case 2:
    {
        s16 *x_table;
        s16 *y_table;
        s16 *x_entry;
        s16 *y_entry;
        s32 arc;
        s16 timer;

        x_table = (s16 *)((s8 *)dirStepX);
        y_entry = (s16 *)(((u16)((S_80173408_4 *)actor)->unk_2A.u >> 8) & 0xE);
        x_entry = (s16 *)((s32)y_entry + (u8 *)x_table);
        y_table = (s16 *)((s8 *)dirStepY);
        y_entry = (s16 *)((s32)y_entry + (u8 *)y_table);
        arc = *x_entry;
        y_entry = (s16 *)(*y_entry);
        step_x = arc << 16;
        step_y = (s32)y_entry << 16;
        motion->unk_0C += step_x;
        motion->unk_10 += step_y;
        arc = -func_800644B8(((S_80173408_0 *)jump)->unk_96.s * 170);
        ((S_80173408_0 *)jump)->unk_A0.at00.v = ((arc * 5) << 8) + 0x300000;
        timer = ((S_80173408_0 *)jump)->unk_96.u + 1;
        ((S_80173408_0 *)jump)->unk_96.u = timer;
        if (timer < 9) {
            return;
        }
    }
    (*(u8 * *)((u8 *)sprite + (0x2C))) = D_80175C50;
    func_80047784(sprite,
        D_80175C50[((gameWork.view.viewAngle + ((S_80173408_4 *)actor)->unk_2A.s + 0x100) >> 9) & 7],
        0);
    func_800A56E0(0x808);
    state = ((S_80173408_0 *)jump)->unk_9B.n;
increment_state:
    ((S_80173408_0 *)jump)->unk_9B.n = state + 1;
    return;

case 3:
    {
        s16 *x_table;
        s16 *y_table;
        s16 *x_entry;
        s16 *y_entry;
        s32 arc;
        s32 direction_x;
        s32 dir_offset;
        s16 timer;
        s32 velocity_x;
        s32 velocity_y;

        if ((*(s16 *)((u8 *)jump + 0x96)) == 10) {
            func_8009C12C(actor, sprite, ((S_80173408_4 *)actor)->unk_2A.s, 1);
        }
        x_table = (s16 *)((s8 *)dirStepX);
        dir_offset = ((u16)((S_80173408_4 *)actor)->unk_2A.u >> 8) & 0xE;
        x_entry = (s16 *)(dir_offset + (u8 *)x_table);
        y_table = (s16 *)((s8 *)dirStepY);
        y_entry = (s16 *)(dir_offset + (u8 *)y_table);
        direction_x = *x_entry;
        arc = *y_entry;
        step_x = direction_x << 16;
        step_y = arc << 16;
        motion->unk_0C += step_x;
        motion->unk_10 += step_y;
        arc = -func_800644B8(((S_80173408_0 *)jump)->unk_96.s * 170);
        ((S_80173408_0 *)jump)->unk_A0.at00.v = ((arc * 5) << 8) + 0x300000;
        timer = ((S_80173408_0 *)jump)->unk_96.u + 1;
        ((S_80173408_0 *)jump)->unk_96.u = timer;
        if (timer < 13) {
            return;
        }
        (*(u8 * *)((u8 *)sprite + (0x2C))) = D_80175C58;
        func_80047784(sprite,
            D_80175C58[((gameWork.view.viewAngle + ((S_80173408_4 *)actor)->unk_2A.s + 0x100) >> 9) & 7],
            0);

        velocity_x = -*(s16 *)((u8 *)x_table +
            (((u16)((S_80173408_4 *)actor)->unk_2A.u >> 8) & 0xE)) << 18;
        velocity_x += velocity_x >> 2;
        motion->unk_0C = velocity_x;

        velocity_y = -*(s16 *)((u8 *)y_table +
            (((u16)((S_80173408_4 *)actor)->unk_2A.u >> 8) & 0xE)) << 18;
        velocity_y += velocity_y >> 2;
        motion->unk_10 = velocity_y;
        ((S_80173408_0 *)jump)->unk_A8 = motion->unk_0C / 24;
        ((S_80173408_0 *)jump)->unk_AC = motion->unk_10 / 24;
    }
    ((S_80173408_0 *)jump)->unk_96.s = 12;
    ((S_80173408_0 *)jump)->unk_9B.n++;
    return;

case 4:
    motion->unk_0C -= ((S_80173408_0 *)jump)->unk_A8;
    motion->unk_10 -= ((S_80173408_0 *)jump)->unk_AC;
    if (((S_80173408_0 *)jump)->unk_A0.at02.v > 0) {
        ((S_80173408_0 *)jump)->unk_A0.at02u.v -= 0x10;
    } else {
        ((S_80173408_0 *)jump)->unk_A0.at02.v = 0;
    }
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    motion->flags14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    func_800AD594(actor, 0x100);
    ((S_80173408_0 *)jump)->unk_8C = &D_80171FA4;
    dungeonStatus.unk_0C = 0;
    func_800A4ACC(actor);
    ((S_80173408_4 *)actor)->unk_46 &= 0x7FFF;
    break;
    default:
        return;
    }
}

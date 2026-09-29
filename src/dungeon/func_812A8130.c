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
extern void func_8017586C(void *, void *, void *);

extern u8 D_80171FA4[9];
extern u8 D_80175C68[8];
extern u8 D_80175C70[8];


typedef struct S_80173930_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x4];
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_A0;   /* overlapping accesses */
    u8 pad_A4[0x4];
    s32 unk_A8;
    s32 unk_AC;
} S_80173930_0;   /* arg0 in func_80173930 */

/* Updates the actor's staged movement, height, and directional animation. */
void func_80173930(void *motion, EntityRec *velocity, void *sprite, EntityRec *actor)
{
    u8 state;

    state = ((S_80173930_0 *)motion)->unk_9B;
    switch (state) {

    case 0:
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            func_800A56E0(0x80E);
        }
        ((S_80173930_0 *)motion)->unk_9B++;

    case 1:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((S_80173930_0 *)motion)->unk_96.u = 0x100;
            ((S_80173930_0 *)motion)->unk_9B = 5;
            func_8009C12C(actor, sprite, actor->facing, 1);
            return;
        }

        ((Rec_D_80082E80 *)sprite)->unk_05.as_u8 -= 2;
        {
            u32 direction_offset = ((u16)actor->facing >> 8) & 0xE;
            velocity->unk_0C -=
                (s32)*(s16 *)((u8 *)((s8 *)dirStepX) + direction_offset) << 16;
            velocity->unk_10 -=
                (s32)*(s16 *)((u8 *)((s8 *)dirStepY) + direction_offset) << 16;
        }
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            (*(u8 * *)((u8 *)sprite + (0x2C))) = D_80175C68;
            func_80047784(
                sprite,
                D_80175C68[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_80173930_0 *)motion)->unk_9B++;
        }

    case 2:
    {
        u16 height = ((S_80173930_0 *)motion)->unk_A0.at02.v + 0x10;

        ((S_80173930_0 *)motion)->unk_A0.at02.v = height;
        if ((s16)height >= 0x31) {
            ((S_80173930_0 *)motion)->unk_A0.at02.v = 0x30;
            velocity->unk_10 = 0;
            velocity->unk_0C = 0;
        }
    }
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
            return;
        }
        velocity->flags14 = 0;
        velocity->unk_10 = 0;
        velocity->unk_0C = 0;
        if (((S_80173930_0 *)motion)->unk_A0.at02u.v < 0x30) {
            return;
        }
        {
            s32 current_state = ((S_80173930_0 *)motion)->unk_9B;

            ((S_80173930_0 *)motion)->unk_96.u = 0;
            if (current_state == 0) {
                return;
            }
        }
        func_800A56E0(0x808);
        ((S_80173930_0 *)motion)->unk_9B++;
        func_8017586C((u8 *)motion - 0x20, (u8 *)actor + 0x2A,
                      (u8 *)motion + 0x9B);
        return;

    case 3:
    {
        u8 *direction_x = (u8 *)((s8 *)dirStepX);
        u8 *direction_y = (u8 *)((s8 *)dirStepY);
        u16 frame;

        velocity->unk_0C +=
            (s32)*(s16 *)(direction_x +
                (((u16)actor->facing >> 8) & 0xE)) << 17;

        velocity->unk_10 +=
            (s32)*(s16 *)(direction_y +
                (((u16)actor->facing >> 8) & 0xE)) << 17;

        ((S_80173930_0 *)motion)->unk_A0.at00.v -= (s32)((S_80173930_0 *)motion)->unk_96.s << 17;
        frame = ((S_80173930_0 *)motion)->unk_96.u + 1;
        ((S_80173930_0 *)motion)->unk_96.u = frame;
        if ((s16)frame < 9) {
            return;
        }

        func_8009C12C(actor, sprite, actor->facing, 1);
        (*(u8 * *)((u8 *)sprite + (0x2C))) = D_80175C70;
        func_80047784(
            sprite,
            D_80175C70[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);

        velocity->unk_0C =
            -*(s16 *)(direction_x +
                (((u16)actor->facing >> 8) & 0xE)) << 20;

        velocity->unk_10 =
            -*(s16 *)(direction_y +
                (((u16)actor->facing >> 8) & 0xE)) << 20;
        ((S_80173930_0 *)motion)->unk_A8 = velocity->unk_0C / 6;
        ((S_80173930_0 *)motion)->unk_AC = velocity->unk_10 / 6;
        ((S_80173930_0 *)motion)->unk_96.u = 0;
        ((S_80173930_0 *)motion)->unk_9B++;
        return;
    }

    case 4:
        velocity->unk_0C -= ((S_80173930_0 *)motion)->unk_A8;
        velocity->unk_10 -= ((S_80173930_0 *)motion)->unk_AC;
        ((S_80173930_0 *)motion)->unk_A0.at00.v =
            func_800644B8(((S_80173930_0 *)motion)->unk_96.s * 146) * 160 + 0x100000;

    case 5:
    {
        u16 frame = ((S_80173930_0 *)motion)->unk_96.u + 1;

        ((S_80173930_0 *)motion)->unk_96.u = frame;
        if ((s16)frame < 7 && !(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            return;
        }
    }
        velocity->flags14 = 0;
        velocity->unk_10 = 0;
        velocity->unk_0C = 0;
        func_800A2B04(velocity, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        func_800AD594(actor, 0x100);
        ((S_80173930_0 *)motion)->unk_8C = D_80171FA4;
        dungeonStatus.unk_0C = 0;
        func_800A4ACC(actor);
        actor->unk_46 &= 0x7FFF;
        break;
    default:
        return;
    }
}

#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
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
extern void func_8009C12C(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern Node *D_800E3DE8[];
extern u8 D_801710F4[];
extern u8 D_80174F30;

/* Updates movement animation and settles the actor at its target tile. */
void func_80172908(void *action, void *motion, void *sprite, void *actor)
{
    s32 state;
    s32 direction_offset;
    s32 direction_x;
    s32 direction_y;
    u16 frames_left;

    direction_offset = ((u16)((EntityRec *)actor)->facing >> 8) & 0xE;
    direction_x = *(s16 *)((u8 *)((s8 *)dirStepX) + direction_offset);
    direction_y = *(s16 *)((u8 *)((s8 *)dirStepY) + direction_offset);
    state = ((S_80172908_1 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((S_80172908_1 *)action)->unk_9B = 0xFF;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
            func_8009C12C(actor, sprite, ((EntityRec *)actor)->facing, 1);
            return;
        }

        (*(u8 * *)((u8 *)sprite + 0x2C)) = &D_80174F30;
        func_80047784(sprite,
            *(&D_80174F30 +
              (((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7)),
            0);
        ((S_80172908_1 *)action)->unk_9B++;
        return;
    case 1:
        if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == state &&
             (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            func_800A56E0(0x808);
            ((S_80172908_1 *)action)->unk_90 = 0;
            ((S_80172908_1 *)action)->unk_98 |= 8;
            ((EntityRec *)motion)->flags14 = (s32)0xFFF50000;
            ((S_80172908_1 *)action)->unk_96.s = 4;
            ((EntityRec *)motion)->unk_0C = (direction_x << 23) / 5;
            ((EntityRec *)motion)->unk_10 = (direction_y << 23) / 5;
            ((S_80172908_1 *)action)->unk_9B++;
        }
        return;
    case 2:
        frames_left = ((S_80172908_1 *)action)->unk_96.s - 1;
        ((S_80172908_1 *)action)->unk_96.s = frames_left;
        if ((s16)frames_left == 3) {
            func_8009C12C(actor, sprite, ((EntityRec *)actor)->facing, 1);
        }

        ((EntityRec *)motion)->flags14 += (5 - ((S_80172908_1 *)action)->unk_96.u) << 16;
        if (((S_80172908_1 *)action)->unk_96.u < 3) {
            ((EntityRec *)motion)->flags14 = 0;
        }
        ((EntityRec *)motion)->unk_0C -= (((EntityRec *)motion)->unk_0C << 2) / 5;
        ((EntityRec *)motion)->unk_10 -= (((EntityRec *)motion)->unk_10 << 2) / 5;
        if (((S_80172908_1 *)action)->unk_96.u > 0) {
            return;
        }
        ((EntityRec *)motion)->flags14 = 0;
        ((S_80172908_1 *)action)->unk_9B = 0xFF;
        ((S_80172908_1 *)action)->unk_98 &= 0xFFF7;
        return;
    case 0xFF:
    {
        s32 target_x = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
        s32 current_x = ((EntityRec *)motion)->x.w.i - 0x20;

        ((EntityRec *)motion)->unk_0C = (target_x - current_x) << 14;
    }
        {
            s32 target_y = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
            s32 current_y = ((EntityRec *)motion)->y.w.i - 0x20;

            ((EntityRec *)motion)->unk_10 = (target_y - current_y) << 14;
        }
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        ((EntityRec *)motion)->unk_10 = 0;
        ((EntityRec *)motion)->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        func_800AD594(actor, 0x100);
        ((S_80172908_1 *)action)->unk_8C = D_801710F4;
        dungeonStatus.unk_0C = 0;
        func_800A4ACC(actor);
        if (((EntityRec *)actor)->unk_6D == 0) {
            ((EntityRec *)actor)->unk_46 &= 0x7FFF;
        } else {
            D_800E3DE8[0] = (Node *)((u8 *)actor - 0x20);
        }
        return;
    default:
        return;
    }
}

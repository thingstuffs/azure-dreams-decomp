#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172C98_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x12];
    union { s16 s; u16 u; } unk_AE;   /* accessed as both */
} S_80172C98_0;   /* arg0 in func_80172C98 */






extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_801752EC(void *, void *, void *);
extern void func_801755A8(void *, void *, void *);

extern u8 D_80171094[];
extern u8 D_80176488[];

/* Updates a timed backward-then-forward movement sequence and handles animation completion. */
void func_80172C98(void *action, void *motion, void *animation, void *actor)
{
    u16 timer;
    s32 state;

    state = ((S_80172C98_0 *)action)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        return;
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 3) {
        goto state_three;
    }
    return;

state_zero:
    ((S_80172C98_0 *)action)->unk_AE.s = 6;
    ((EntityRec *)motion)->unk_0C =
        -(((func_80064584(((EntityRec *)actor)->facing) >> 4) << 13) /
          ((S_80172C98_0 *)action)->unk_AE.s);
    ((EntityRec *)motion)->unk_10 =
        -(((func_800644B8(((EntityRec *)actor)->facing) >> 4) << 13) /
          ((S_80172C98_0 *)action)->unk_AE.s);
    ((S_80172C98_0 *)action)->unk_9B++;

state_one:
    if (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x8000) {
        ((S_80172C98_0 *)action)->unk_9B = 3;
        ((EntityRec *)motion)->unk_0C =
            ((EntityRec *)motion)->unk_10 =
                ((EntityRec *)motion)->flags14 = 0;
        ((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v |= 0x6000;
        func_8009C12C(actor, animation, ((EntityRec *)actor)->facing, 1);
        return;
    }

    timer = ((S_80172C98_0 *)action)->unk_AE.u - 1;
    ((S_80172C98_0 *)action)->unk_AE.u = timer;
    if ((s16)timer < 0) {
        ((EntityRec *)motion)->unk_0C =
            ((EntityRec *)motion)->unk_10 =
                ((EntityRec *)motion)->flags14 = 0;
    }

    if (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x6000) {
        u8 *direction_anims = D_80176488;

        (*(u8 * *)((u8 *)animation + 0x2C)) = direction_anims;
        func_80047784(
            animation,
            direction_anims[((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);
        ((S_80172C98_0 *)action)->unk_AE.s = 6;
        ((EntityRec *)motion)->unk_0C =
            ((func_80064584(((EntityRec *)actor)->facing) >> 4) << 14) /
            ((S_80172C98_0 *)action)->unk_AE.s;
        ((EntityRec *)motion)->unk_10 =
            ((func_800644B8(((EntityRec *)actor)->facing) >> 4) << 14) /
            ((S_80172C98_0 *)action)->unk_AE.s;
        ((S_80172C98_0 *)action)->unk_AE.u--;
        func_801752EC(action, motion, animation);
        func_801755A8(action, motion, animation);
        func_800A56E0(0x80E);
        ((S_80172C98_0 *)action)->unk_9B++;
        ((S_80172C98_0 *)action)->unk_96 = 0;
    }
    return;

state_two:
    timer = ((S_80172C98_0 *)action)->unk_AE.u - 1;
    ((S_80172C98_0 *)action)->unk_AE.u = timer;
    if ((s16)timer < 0) {
        ((EntityRec *)motion)->unk_0C =
            ((EntityRec *)motion)->unk_10 =
                ((EntityRec *)motion)->flags14 = 0;
    }

    timer = ((S_80172C98_0 *)action)->unk_96 + 1;
    ((S_80172C98_0 *)action)->unk_96 = timer;
    if (((s16)timer == 5) || (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x8000)) {
        func_8009C12C(actor, animation, ((EntityRec *)actor)->facing, 1);
        func_800A56E0(0x808);
    }

state_three:
    if (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0xE000) {
        func_800AD594(actor, 0x100);
        func_800A2B04(motion, ((Rec_D_80082E80 *)animation)->unk_24, ((Rec_D_80082E80 *)animation)->unk_25);
        ((EntityRec *)motion)->unk_0C =
            ((EntityRec *)motion)->unk_10 =
                ((EntityRec *)motion)->flags14 = 0;
        ((S_80172C98_0 *)action)->unk_8C = D_80171094;
        dungeonStatus.unk_0C = 0;
        (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        func_800A4ACC(actor);
    }
}

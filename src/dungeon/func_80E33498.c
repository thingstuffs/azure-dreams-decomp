/* Relink of matched dungeon/func_80E0F498; every changed retail word is a paired relocation. */
#define dungeonAdvanceBackwardForwardMotion func_8014EC98
#define D_80171094 D_8014D094
#define D_80176488 D_80152488
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
} S_80172C98_0;   /* arg0 in func_8014EC98 */


extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_80047784(void *, s32, s32);
extern void dungeonResolveAttackDamageAndEffects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void dungeonSetRecordIntegerTileCenter(void *, u8, u8);
extern void dungeonAdvanceStatusTimers(void *);
extern void func_800A56E0(s32);
extern void dungeonReduceActorFoodMeter(void *, s32);
extern s32 func_801512EC(void *, void *, void *);
extern s32 func_801515A8(void *, void *, void *);

extern u8 D_8014D094[];
extern u8 D_80152488[];

/* Updates a timed backward-then-forward movement sequence and handles animation completion. */
void func_8014EC98(void *action, EntityRec *motion, void *animation, EntityRec *actor)
{
    u16 timer;
    s32 state;

    state = ((S_80172C98_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        ((S_80172C98_0 *)action)->unk_AE.s = 6;
        motion->unk_0C =
            -(((func_80064584(actor->facing) >> 4) << 13) /
              ((S_80172C98_0 *)action)->unk_AE.s);
        motion->unk_10 =
            -(((func_800644B8(actor->facing) >> 4) << 13) /
              ((S_80172C98_0 *)action)->unk_AE.s);
        ((S_80172C98_0 *)action)->unk_9B++;

    case 1:
        if (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x8000) {
            ((S_80172C98_0 *)action)->unk_9B = 3;
            motion->unk_0C =
                motion->unk_10 =
                    motion->flags14 = 0;
            ((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v |= 0x6000;
            dungeonResolveAttackDamageAndEffects(actor, animation, actor->facing, 1);
            return;
        }

        timer = ((S_80172C98_0 *)action)->unk_AE.u - 1;
        ((S_80172C98_0 *)action)->unk_AE.u = timer;
        if ((s16)timer < 0) {
            motion->unk_0C =
                motion->unk_10 =
                    motion->flags14 = 0;
        }

        if (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x6000) {
            u8 *direction_anims = D_80152488;

            (*(u8 * *)((u8 *)animation + 0x2C)) = direction_anims;
            func_80047784(
                animation,
                direction_anims[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_80172C98_0 *)action)->unk_AE.s = 6;
            motion->unk_0C =
                ((func_80064584(actor->facing) >> 4) << 14) /
                ((S_80172C98_0 *)action)->unk_AE.s;
            motion->unk_10 =
                ((func_800644B8(actor->facing) >> 4) << 14) /
                ((S_80172C98_0 *)action)->unk_AE.s;
            ((S_80172C98_0 *)action)->unk_AE.u--;
            func_801512EC(action, motion, animation);
            func_801515A8(action, motion, animation);
            func_800A56E0(0x80E);
            ((S_80172C98_0 *)action)->unk_9B++;
            ((S_80172C98_0 *)action)->unk_96 = 0;
        }
        return;

    case 2:
        timer = ((S_80172C98_0 *)action)->unk_AE.u - 1;
        ((S_80172C98_0 *)action)->unk_AE.u = timer;
        if ((s16)timer < 0) {
            motion->unk_0C =
                motion->unk_10 =
                    motion->flags14 = 0;
        }

        timer = ((S_80172C98_0 *)action)->unk_96 + 1;
        ((S_80172C98_0 *)action)->unk_96 = timer;
        if (((s16)timer == 5) || (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x8000)) {
            dungeonResolveAttackDamageAndEffects(actor, animation, actor->facing, 1);
            func_800A56E0(0x808);
        }

    case 3:
        if (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0xE000) {
            dungeonReduceActorFoodMeter(actor, 0x100);
            dungeonSetRecordIntegerTileCenter(motion, ((Rec_D_80082E80 *)animation)->unk_24, ((Rec_D_80082E80 *)animation)->unk_25);
            motion->unk_0C =
                motion->unk_10 =
                    motion->flags14 = 0;
            ((S_80172C98_0 *)action)->unk_8C = D_8014D094;
            dungeonStatus.unk_0C = 0;
            (actor->unk_46) &= 0x7FFF;
            dungeonAdvanceStatusTimers(actor);
        }
    }
}

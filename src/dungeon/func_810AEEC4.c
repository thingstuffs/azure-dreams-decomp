#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_801726C4_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801726C4_0;   /* arg0 in advanceActorActionAnimationAndCleanup */


extern void func_80047784(void *, u8, s32);
extern void dungeonResolveAttackDamageAndEffects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void dungeonSetRecordIntegerTileCenter(s32, u8, u8);
extern void dungeonAdvanceStatusTimers(void *);
extern void func_800A56E0(s32);
extern void dungeonReduceActorFoodMeter(void *, s32);

extern void *D_800E3DE8;
extern s32 D_80170E54;
extern u8 D_80173C84[];

/* Advances the actor action through animation setup, completion, and cleanup. */
void advanceActorActionAnimationAndCleanup(void *action, s32 actor_id, void *animation, EntityRec *actor) {
    s32 state;

    state = ((S_801726C4_0 *)action)->unk_9B;
    ((S_801726C4_0 *)action)->unk_96--;
    switch (state) {
    case 0:
        if (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x8000) {
            ((S_801726C4_0 *)action)->unk_9B = 0xFF;
            ((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v |= 0x6000;
            dungeonResolveAttackDamageAndEffects(actor, animation, actor->facing, 1);
            return;
        }
        (*(u8 * *)((u8 *)animation + 0x2C)) = D_80173C84;
        func_80047784(animation,
            D_80173C84[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_801726C4_0 *)action)->unk_9B++;
        return;

    case 1:
        if (((((Rec_D_80082E80 *)animation)->unk_04.as_s8 == 6) &&
             (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x1000)) ||
            (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x8000)) {
            func_800A56E0(0x808);
            dungeonResolveAttackDamageAndEffects(actor, animation, actor->facing, 1);
            ((S_801726C4_0 *)action)->unk_9B = 0xFF;
        }
        return;

    case 0xFF:
        if (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0xE000) {
            dungeonSetRecordIntegerTileCenter(actor_id, ((Rec_D_80082E80 *)animation)->unk_24, ((Rec_D_80082E80 *)animation)->unk_25);
            dungeonReduceActorFoodMeter(actor, 0x200);
            ((S_801726C4_0 *)action)->unk_8C = &D_80170E54;
            dungeonStatus.unk_0C = 0;
            dungeonAdvanceStatusTimers(actor);
            if (actor->unk_6D == 0) {
                actor->unk_46 &= 0x7FFF;
                return;
            }
            D_800E3DE8 = (u8 *)actor - 0x20;
        }
        return;
    }
}

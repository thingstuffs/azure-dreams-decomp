#include "modules/dungeon_resource06_slot0.h"

void dungeonAdvanceActionThroughAnimation(R06_8017278C_S_8017278C_0 *action, EntityRec *motion, Rec_D_80082E80 *sprite, void *actor) {
    u16 ticks_left;
    s32 initial_state;
    s32 state;
    u8 *direction_frames;

    initial_state = 1;
    state = action->unk_9B;
    switch (state) {
    case 0:
        action->unk_9B = initial_state;
    case 1:
        if (sprite->unk_14.at00_u16.v & 0x8000) {
            action->unk_9B = 3U;
            sprite->unk_14.at00_u16.v = (u16) (sprite->unk_14.at00_u16.v | 0x6000);
            dungeonResolveAttackDamageAndEffects(actor, sprite,(s16)(((EntityRec *)actor)->facing),(s16)(1));
            return;
        }
        direction_frames = ((u8 *)D_8017587C);
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        sprite->unk_2C.as_pu8 = direction_frames;
        func_80047784(sprite,(u8)(direction_frames[((s32) (gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100)
            >> 9) & 7]), 0);
        action->unk_96 = 9;
        action->unk_9B++;
        return;
    case 2:
        ticks_left = action->unk_96 - 1;
        action->unk_96 = ticks_left;
        if ((ticks_left << 0x10) > 0) {
            return;
        }
        func_800A56E0(0x804);
        dungeonResolveAttackDamageAndEffects(actor, sprite,(s16)(((EntityRec *)actor)->facing),(s16)(1));
        action->unk_9B++;
        return;
    case 3:
        if (sprite->unk_14.at00_u16.v & 0xE000) {
            dungeonSetRecordIntegerTileCenter(motion,(u8)(sprite->unk_24),(u8)(sprite->unk_25));
            dungeonReduceActorFoodMeter(actor, 0x100);
            action->unk_8C = ((u8 *)func_8017140C);
            dungeonStatus.unk_0C = 0;
            dungeonAdvanceStatusTimers(actor);
            if (((EntityRec *)actor)->unk_6D == 0) {
                ((EntityRec *)actor)->unk_46 = (u16) (((EntityRec *)actor)->unk_46 & 0x7FFF);
            } else {
                *((void * *)D_800E3DE8) = actor - 0x20;
            }
        }
        return;
    default:
        return;
    }
}

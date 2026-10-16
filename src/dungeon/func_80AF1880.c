#include "modules/dungeon_resource10_slot0.h"

void func_80173080(void *action, void *motion, void *sprite, EntityRec *actor)
{
    u16 timer;
    s32 state;

    state = ((R10_80173080_S_80173080_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((R10_80173080_S_80173080_0 *)action)->unk_9B = 3;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
            dungeonResolveAttackDamageAndEffects(actor, sprite,(s16)(actor->facing),(s16)(1));
            return;
        }
        ((R10_80173080_S_80173080_3 *)motion)->unk_14 = 0;
        ((R10_80173080_S_80173080_3 *)motion)->unk_10 = 0;
        ((R10_80173080_S_80173080_3 *)motion)->unk_0C = 0;
        ((R10_80173080_S_80173080_0 *)action)->unk_96.u = 0;
        ((R10_80173080_S_80173080_0 *)action)->unk_9B++;
        return;
    case 1:
        timer = ((R10_80173080_S_80173080_0 *)action)->unk_96.u + 1;
        ((R10_80173080_S_80173080_0 *)action)->unk_96.u = timer;
        if (((s16)timer == 4) || (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            u8 *direction_table = ((u8 *)D_801759C0);

            (*(u8 * *)((u8 *)sprite + (0x2C))) = direction_table;
            func_80047784(sprite,
                          direction_table[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                          0);
            ((R10_80173080_S_80173080_0 *)action)->unk_96.u = 0;
            ((R10_80173080_S_80173080_0 *)action)->unk_9B++;
            return;
        }
        return;
    case 2:
        timer = ((R10_80173080_S_80173080_0 *)action)->unk_96.u + 1;
        ((R10_80173080_S_80173080_0 *)action)->unk_96.u = timer;
        if (((s16)timer == 7) || (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            dungeonResolveAttackDamageAndEffects(actor, sprite,(s16)(actor->facing),(s16)(1));
            ((R10_80173080_S_80173080_0 *)action)->unk_96.u = 0;
            ((R10_80173080_S_80173080_0 *)action)->unk_9B++;
        }
        if (((R10_80173080_S_80173080_0 *)action)->unk_96.s == 5) {
            func_800A56E0(0x808);
            return;
        }
        return;
    case 3:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
            dungeonReduceActorFoodMeter(actor, 0x100);
            ((R10_80173080_S_80173080_0 *)action)->unk_8C = ((u8 *)func_801717F4);
            dungeonStatus.unk_0C = 0;
            dungeonAdvanceStatusTimers(actor);
            actor->unk_46 &= 0x7FFF;
        }
        return;
    }
}

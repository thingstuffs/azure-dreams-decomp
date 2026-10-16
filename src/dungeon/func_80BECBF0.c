#include "modules/dungeon_resource16_slot0.h"

void func_801723F0(void *action, void *motion, void *anim, void *actor) {
    s32 state;
    u16 ticks;

    state = ((R16_801723F0_S_801723F0_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        ((R16_801723F0_S_801723F0_0 *)action)->unk_9B = 1;
    case 1:
        if (((Rec_D_80082E80 *)anim)->unk_14.at00_u16.v & 0x8000) {
            ((R16_801723F0_S_801723F0_0 *)action)->unk_9B = 3;
            ((Rec_D_80082E80 *)anim)->unk_14.at00_u16.v |= 0x6000;
            func_8009C12C(actor, anim,(s16)(((EntityRec *)actor)->facing),(s16)(1));
            return;
        }
        ((R16_801723F0_S_801723F0_3 *)motion)->unk_14 = 0;
        ((R16_801723F0_S_801723F0_3 *)motion)->unk_10 = 0;
        ((R16_801723F0_S_801723F0_3 *)motion)->unk_0C = 0;
        (*(u8 * *)((u8 *)anim + 0x2C)) = ((u8 *)D_8017423C);
        func_80047784(anim,(u8)(((u8 *)D_8017423C)[((s32)(gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7]),
            0);
        ((R16_801723F0_S_801723F0_0 *)action)->unk_96 = 0;
        ((R16_801723F0_S_801723F0_0 *)action)->unk_9B++;
        func_800A56E0(0x804);
        return;
    case 2:
        ticks = ((R16_801723F0_S_801723F0_0 *)action)->unk_96 + 1;
        ((R16_801723F0_S_801723F0_0 *)action)->unk_96 = ticks;
        if (((s16)ticks == 8) || (((Rec_D_80082E80 *)anim)->unk_14.at00_u16.v & 0x8000)) {
            func_8009C12C(actor, anim,(s16)(((EntityRec *)actor)->facing),(s16)(1));
        }
    case 3:
        if (((Rec_D_80082E80 *)anim)->unk_14.at00_u16.v & 0xE000) {
            func_800AD594(actor, 0x100);
            ((R16_801723F0_S_801723F0_0 *)action)->unk_8C = ((u8 *)func_80171014);
            dungeonStatus.unk_0C = 0;
            (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
            func_800A4ACC(actor);
        }
    default:
        break;
    }
}

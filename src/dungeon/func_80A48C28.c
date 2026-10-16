#include "modules/dungeon_resource06_slot0.h"

void dungeonUpdateActorActionAndDirection(void *action_state, void *context, void *sprite, EntityRec *actor) {
    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)) {
        dungeonApplyCameraOffsetAndSelectTarget((u8 *)actor - 0x20, context, 8, 0x300);
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            ((R06_80172428_S_80172428_1 *)action_state)->unk_9A = 0x11;
            (*(s32 *)((u8 *)action_state + 0x8C)) = 0;
            ((R06_80172428_S_80172428_1 *)action_state)->unk_9B = 0;
            (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = ((u8 *)D_8017587C);
            func_80047784(sprite, *((((s32) (gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7)
                + ((u8 *)D_8017587C)), 0);
            actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
            dungeonPrepareDirectionalAttack(actor, sprite, actor->facing, 1, 0);
            ((R06_80172428_S_80172428_1 *)action_state)->unk_98 = (u16) (((R06_80172428_S_80172428_1 *)action_state)->unk_98 | 8);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
        }
    }
}

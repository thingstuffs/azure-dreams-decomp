#include "modules/dungeon_ovl_e0365c.h"

void func_80171FD4(void *action_state, void *action_context, void *sprite, EntityRec *actor) {
    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)) {
        func_800C7930((u8 *)actor - 0x20, action_context, 8, 0x300);
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            ((E_80171FD4_S_80171FC4_1 *)action_state)->unk_9A = 0x11;
            (*(s32 *)((u8 *)action_state + 0x8C)) = 0;
            ((E_80171FD4_S_80171FC4_1 *)action_state)->unk_9B = 0;
            (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_80174540;
            func_80047784(sprite, *((((s32) (gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7)
                + &D_80174540), 0);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
            actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
            func_8009C93C(actor, sprite, actor->facing, 1, 0);
        }
    }
}

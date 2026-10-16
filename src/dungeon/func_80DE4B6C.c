#include "modules/dungeon_ovl_e0365c.h"

void dungeonStartActorDirectionalAnimation(void *actor_state, s32 action_param, void *sprite, EntityRec *actor) {
    actor->unk_71 = actor->unk_71 & 0x7F;
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)) {
        dungeonApplyCameraOffsetAndSelectTarget((u8 *)actor - 0x20, action_param, 8, 0x300);
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            ((E_8017236C_S_8017236C_1 *)actor_state)->unk_9A = 0x18;
            ((E_8017236C_S_8017236C_1 *)actor_state)->unk_8C = 0;
            ((E_8017236C_S_8017236C_1 *)actor_state)->unk_9B = 0;
            (*(s32 * *)((u8 *)sprite + 0x2C)) = &D_80174558;
            func_80047784(sprite,
                          *((((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7)
                            + (u8 *)&D_80174558),
                          0);
            dungeonAdvanceStatusTimers(actor);
            actor->unk_6D = ((u8)actor->unk_6D) - 1;
        }
    }
}

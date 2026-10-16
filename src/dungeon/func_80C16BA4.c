#include "modules/dungeon_resource17_slot0.h"

void func_801723A4(Rec_func_800A9E70_arg0 *action_state, void *context, Rec_D_80082E80 *animation,
    EntityRec *entity) {
    entity->unk_71 = (s8) (entity->unk_71 & 0x7F);
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2B5C(entity) << 0x10) == 0)) {
        dungeonApplyCameraOffsetAndSelectTarget((u8 *)entity - 0x20, context, 8, 0x300);
        if ((func_800A2B5C(entity) << 0x10) == 0) {
            action_state->unk_9A.as_s8 = 0x11;
            action_state->unk_8C = 0;
            action_state->unk_9B.as_s8 = 0;
            func_80047784(animation, *(animation->unk_2C.as_pu8 + (((s32) (gameWork.view.viewAngle + entity->facing
                + 0x100) >> 9) & 7)), 0);
            entity->unk_6D = (u8) (((u8)entity->unk_6D) - 1);
            dungeonPrepareDirectionalAttack(entity, animation, entity->facing, 1, 0);
            action_state->unk_98 = (u16) (action_state->unk_98 | 8);
            entity->unk_84 = 0x7C;
            entity->unk_85 = 0;
        }
    }
}

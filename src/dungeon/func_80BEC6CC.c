#include "modules/dungeon_resource16_slot0.h"

s32 dungeonInitializeTransitionAction(void *action_state, s32 action_id, void *source_obj, EntityRec *actor)
{
    s32 target_angle;
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */

    actor->unk_71 &= 0x7F;
    if (dungeonStatus.flags & 0x2000) {
        return -1;
    }
    target_angle = dungeonPlaceActorAtDirectionalNeighbor(actor, ((R16_80171ECC_S_80171ECC_1 *)source_obj)->unk_24,
                                 ((R16_80171ECC_S_80171ECC_1 *)source_obj)->unk_25, actor->facing);
    if ((func_800A2CB8(actor, target_angle) << 16) == 0) {
        return 0;
    }
    if (dungeonStatus.flags & 0x2000) {
        return -1;
    }
    if (!(actor->unk_46 & 0x8000) && (dungeonStatus.flags & 8)) {
        return -1;
    }
    if ((u16)(-dungeonGetActorHeightDifference(target_angle, actor) + 0x40) >= 0x81U) {
        return 0;
    }
    if ((func_800A2B5C(actor) << 16) != 0) {
        return -1;
    }
    dungeonApplyCameraOffsetAndSelectTarget((u8 *)actor - 0x20, action_id, 8, 0x300);
    if ((func_800A2B5C(actor) << 16) == 0) {
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_u8 = 0x11;
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_u8 = 0;
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
        actor->unk_84 = 0x7C;
        actor->unk_85 = 0;
        (*(u8 * *)((u8 *)source_obj + 0x2C)) = ((u8 *)D_80174214);
        func_80047784(
            source_obj,
            ((u8 *)D_80174214)[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        dungeonPrepareDirectionalAttack(actor, source_obj, actor->facing, 1, 0);
        actor->unk_6D--;
        return 1;
    }
    return -1;
}

/* MECHANISM: The true-rowbase CFG holds arg2 in $s3 and the status base in $s2 at cdk-G0.
   An unused 8-byte local (unused[2]) raises the otherwise exact 0x38 frame to retail's 0x40
   without emitting body code; source-based byte indexing preserves the final call operands. */

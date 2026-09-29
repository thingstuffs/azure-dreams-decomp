#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"


typedef struct S_80171ECC_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80171ECC_1;   /* source in func_80171ECC */


extern s32 func_80047784();
extern s32 func_8009C93C();
extern s32 func_800A0134();
extern s32 func_800A04F0();
extern s32 func_800A2B5C();
extern s32 func_800A2CB8();
extern s32 func_800C7930();
extern u8 D_80174214[];

/* Check the actor's transition conditions and initialize the action and source animation. */
s32 func_80171ECC(void *action_state, s32 action_id, void *source_obj, EntityRec *actor)
{
    s32 target_angle;
    volatile long long frame_pad;

    actor->unk_71 &= 0x7F;
    if (dungeonStatus.flags & 0x2000) {
        return -1;
    }
    target_angle = func_800A04F0(actor, ((S_80171ECC_1 *)source_obj)->unk_24,
                                 ((S_80171ECC_1 *)source_obj)->unk_25, actor->facing);
    if ((func_800A2CB8(actor, target_angle) << 16) == 0) {
        return 0;
    }
    if (dungeonStatus.flags & 0x2000) {
        return -1;
    }
    if (!(actor->unk_46 & 0x8000) && (dungeonStatus.flags & 8)) {
        return -1;
    }
    if ((u16)(-func_800A0134(target_angle, actor) + 0x40) >= 0x81U) {
        return 0;
    }
    if ((func_800A2B5C(actor) << 16) != 0) {
        return -1;
    }
    func_800C7930((u8 *)actor - 0x20, action_id, 8, 0x300);
    if ((func_800A2B5C(actor) << 16) == 0) {
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_u8 = 0x11;
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_u8 = 0;
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
        actor->unk_84 = 0x7C;
        actor->unk_85 = 0;
        (*(u8 * *)((u8 *)source_obj + 0x2C)) = D_80174214;
        func_80047784(
            source_obj,
            D_80174214[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        func_8009C93C(actor, source_obj, actor->facing, 1, 0);
        actor->unk_6D--;
        return 1;
    }
    return -1;
}

/* MECHANISM: The true-rowbase CFG holds arg2 in $s3 and the status base in $s2 at cdk-G0.
   A volatile eight-byte frame object raises the otherwise exact 0x38 frame to retail's 0x40
   without emitting body code; source-based byte indexing preserves the final call operands. */

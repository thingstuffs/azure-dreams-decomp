#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_800A9E70_arg0.h"






extern s32 func_80047784();
extern s32 func_8009C93C();
extern s32 func_800A0134();
extern s32 func_800A04F0();
extern s32 func_800A2B5C();
extern s32 func_800A2CB8();
extern s32 func_800C7930();
extern u8 D_8017386C[];

/* Attempt an actor transition and update its state and sprite on success. */
s32 func_80171D80(void *state, s32 action_id, void *sprite, EntityRec *actor)
{
    volatile u16 *status;
    s32 transitioned;
    s32 target;

    actor->unk_71 &= 0x7F;
    status = ((u16 *)(&dungeonStatus));
    transitioned = 0;
    if (!(((volatile u16 *)status)[1] & 0x2000)) {
        target = func_800A04F0(actor, ((Rec_D_80082E80 *)sprite)->unk_24,
                               ((Rec_D_80082E80 *)sprite)->unk_25, actor->facing);
        if ((func_800A2CB8(actor, target) << 16) == 0) {
            goto return_zero;
        }
        {
            u16 status_flags = status[1];

            if (status_flags & 0x2000) {
                return -1;
            }
            if (!(actor->unk_46 & 0x8000) && (status_flags & 8)) {
                return -1;
            }
        }
        if ((s16)(-func_800A0134(target, actor) + 0x40) >= 0x81U) {
            return transitioned;
        }

        transitioned = 1;
        if ((func_800A2B5C(actor) << 16) != 0) {
            return -1;
        }
        func_800C7930((u8 *)actor - 0x20, action_id, 8, 0x300);
        if ((func_800A2B5C(actor) << 16) == 0) {
            goto transition_ok;
        }
    }
    return -1;

transition_ok:
    {
        u16 state_flags;

        state_flags = ((Rec_func_800A9E70_arg0 *)state)->unk_98;
        ((Rec_func_800A9E70_arg0 *)state)->unk_9B.as_u8 = 0;
        ((Rec_func_800A9E70_arg0 *)state)->unk_8C = 0;
        if (state_flags & 0x8000) {
            ((Rec_func_800A9E70_arg0 *)state)->unk_9A.as_u8 = 0x17;
            actor->unk_84 = 0x10;
            actor->unk_85 = 0x10;
        } else {
            ((Rec_func_800A9E70_arg0 *)state)->unk_9A.as_u8 = 0x11;
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
        }
    }

    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_8017386C;
    func_80047784(sprite,
                  D_8017386C[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                  0);
    actor->unk_6D--;
    if (((Rec_func_800A9E70_arg0 *)state)->unk_9A.as_u8 != 0x11) {
        return transitioned;
    }
    func_8009C93C(actor, sprite, actor->facing, 1, 0);
    return transitioned;

return_zero:
    return 0;
}

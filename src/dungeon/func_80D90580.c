#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_800A9E70_arg0.h"






extern s32 func_80047784();
extern s32 func_8009C93C();
extern s32 func_800A0134();
extern s32 func_800A04F0();
extern s32 func_800A2B5C();
extern s32 func_800A2CB8();
extern s32 func_800C7930();
extern s16 D_80083228;
extern volatile u16 D_80083460[];
extern u8 D_8017386C[];

/* Attempt an actor transition and update its state and sprite on success. */
s32 func_80171D80(void *state, s32 action_id, void *sprite, void *actor)
{
    volatile u16 *status;
    s32 transitioned;
    s32 target;

    ((Rec_D_800E3D7C *)actor)->unk_71.as_u8 &= 0x7F;
    status = D_80083460;
    transitioned = 0;
    if (((volatile u16 *)status)[1] & 0x2000) {
        goto abort_transition;
    }
    target = func_800A04F0(actor, ((Rec_D_80082E80 *)sprite)->unk_24,
                           ((Rec_D_80082E80 *)sprite)->unk_25, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16);
    if ((func_800A2CB8(actor, target) << 16) == 0) {
        goto return_zero;
    }
    {
        u16 status_flags = status[1];

        if (status_flags & 0x2000) {
            return -1;
        }
        if (!(((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x8000) && (status_flags & 8)) {
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

abort_transition:
    return -1;

transition_ok:
    {
        u16 state_flags;

        state_flags = ((Rec_func_800A9E70_arg0 *)state)->unk_98;
        ((Rec_func_800A9E70_arg0 *)state)->unk_9B.as_u8 = 0;
        ((Rec_func_800A9E70_arg0 *)state)->unk_8C = 0;
        if (state_flags & 0x8000) {
            ((Rec_func_800A9E70_arg0 *)state)->unk_9A.as_u8 = 0x17;
            ((Rec_D_800E3D7C *)actor)->unk_84.as_u8 = 0x10;
            ((Rec_D_800E3D7C *)actor)->unk_85.as_u8 = 0x10;
        } else {
            ((Rec_func_800A9E70_arg0 *)state)->unk_9A.as_u8 = 0x11;
            ((Rec_D_800E3D7C *)actor)->unk_84.as_u8 = 0x7C;
            ((Rec_D_800E3D7C *)actor)->unk_85.as_u8 = 0;
        }
    }

    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_8017386C;
    func_80047784(sprite,
                  D_8017386C[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                  0);
    ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8--;
    if (((Rec_func_800A9E70_arg0 *)state)->unk_9A.as_u8 != 0x11) {
        return transitioned;
    }
    func_8009C93C(actor, sprite, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1, 0);
    return transitioned;

return_zero:
    return 0;
}

#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"


typedef struct S_80171DA0_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80171DA0_1;   /* held_arg2 in func_80171DA0 */




extern void func_80047784();
extern void func_8009C93C();
extern s32 func_800A0134();
extern s32 func_800A04F0();
extern s32 func_800A2B5C();
extern s32 func_800A2CB8();
extern void func_800C7930();
extern u8 D_80173C7C;

/* Checks whether the actor can transition and starts its directional effect. */
s32 func_80171DA0(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, void *sprite_arg, EntityRec *actor)
{
    s32 target_angle;
    u16 status_flags;
    u8 actor_flags;
    volatile s32 frame_pad[2];

    actor_flags = actor->unk_71;
    actor_flags &= 0x7F;
    actor->unk_71 = actor_flags;
    if (dungeonStatus.flags & 0x2000) {
        goto abort_transition;
    }

    target_angle = func_800A04F0(actor, ((S_80171DA0_1 *)sprite_arg)->unk_24,
                           ((S_80171DA0_1 *)sprite_arg)->unk_25, actor->facing);
    if ((func_800A2CB8(actor, target_angle) << 16) == 0) {
        return 0;
    }

    status_flags = dungeonStatus.flags;
    if (status_flags & 0x2000) {
        return -1;
    }
    if (!(actor->unk_46 & 0x8000) && (status_flags & 8)) {
        return -1;
    }
    if ((u16)(-func_800A0134(target_angle, actor) + 0x40) >= 0x81U) {
        return 0;
    }
    if ((func_800A2B5C(actor) << 16) != 0) {
        return -1;
    }

    func_800C7930((u8 *)actor - 0x20, motion_param, 8, 0x300);
    if ((func_800A2B5C(actor) << 16) == 0) {
        goto transition_ok;
    }

abort_transition:
    return -1;

transition_ok:
    {
        action_state->unk_9A.as_u8 = 0x11;
        action_state->unk_9B.as_u8 = 0;
        action_state->unk_8C = 0;
        actor->unk_84 = 0x7C;
        actor->unk_85 = 0;
        ((S_80171DA0_1 *)sprite_arg)->unk_2C = &D_80173C7C;
        func_80047784(sprite_arg, (&D_80173C7C)[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        actor->unk_6D--;
        func_8009C93C(actor, sprite_arg, actor->facing, 1, 0);
        return 1;
    }
}

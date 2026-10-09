#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_800A9E70_arg0.h"

extern void func_80047784();
extern void func_8009C93C();
extern s32 func_800A0134();
extern s32 func_800A04F0();
extern s32 func_800A2B5C();
extern s32 func_800A2CB8();
extern void func_800C7930();
extern u8 D_80174AD4;

/* Checks whether the actor can transition and starts its directional effect. */
s32 func_80171F74(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, SpriteFrameState *sprite, EntityRec *actor)
{
    s32 target_angle;
    u16 status_flags;
    u8 actor_flags;
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */

    actor_flags = actor->unk_71;
    actor_flags &= 0x7F;
    actor->unk_71 = actor_flags;
    if (dungeonStatus.flags & 0x2000) {
        return -1;
    }

    target_angle = func_800A04F0(actor, sprite->unk_24, sprite->unk_25, actor->facing);
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

    func_800C7930((ObjectNodeHeader *)actor - 1, motion_param, 8, 0x300);
    if ((func_800A2B5C(actor) << 16) == 0) {
        action_state->unk_9A.as_u8 = 0x11;
        action_state->unk_9B.as_u8 = 0;
        action_state->unk_8C = 0;
        actor->unk_84 = 0x7C;
        actor->unk_85 = 0;
        sprite->frameTable = &D_80174AD4;
        func_80047784(sprite, (&D_80174AD4)[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        actor->unk_6D--;
        func_8009C93C(actor, sprite, actor->facing, 1, 0);
        return 1;
    }
    return -1;
}

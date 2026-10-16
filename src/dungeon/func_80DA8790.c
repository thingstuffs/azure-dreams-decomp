/* Relink of matched dungeon/func_80D90790; every changed retail word is a paired relocation. */
#define D_8017386C D_8015B86C
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"

extern s32 func_800A2B5C();
extern void dungeonApplyCameraOffsetAndSelectTarget();
extern void func_80047784();
extern void dungeonPrepareDirectionalAttack();

extern u8 D_8015B86C[];

/* Update actor action state and select its directional animation. */
void func_80159F90(void *action_state, s32 update_arg, void *sprite, EntityRec *actor)
{
    actor->unk_71 &= 0x7F;

    if (!(dungeonStatus.flags & 0x2000) &&
        ((func_800A2B5C(actor) << 0x10) == 0) &&
        (dungeonApplyCameraOffsetAndSelectTarget((u8 *)actor - 0x20, update_arg, 8, 0x300),
         ((func_800A2B5C(actor) << 0x10) == 0))) {
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;

        if (((Rec_func_800A9E70_arg0 *)action_state)->unk_98 & 0x8000) {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_u8 = 0x17;
            actor->unk_84 = 0x10;
            actor->unk_85 = 0x10;
        } else {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_u8 = 0x11;
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
        }
        (*(u8 **)((u8 *)sprite + 0x2C)) = D_8015B86C;
        func_80047784(sprite,
                      D_8015B86C[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                      0);
        actor->unk_6D--;

        if (((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_u8 == 0x11) {
            dungeonPrepareDirectionalAttack(actor, sprite, actor->facing, 1, 0);
        }
    }
}

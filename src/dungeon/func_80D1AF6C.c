/* Relink of matched dungeon/func_80D14F6C; every changed retail word is a paired relocation. */
#define D_80174EC8 D_8016EEC8
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_func_800AA258_arg2.h"

typedef s32 M2C_UNK;


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void func_80047784();
s32 findEligibleActorAtTileAndHeight();
s32 func_800A2B5C();
s32 dungeonAdvanceStatusTimers();
s32 dungeonApplyCameraOffsetAndSelectTarget();
extern u8 D_8016EEC8;

/* Start the actor's directional action and record the adjacent tile result. */
void func_8016E76C(void *action_state, void *action_context, void *sprite, EntityRec *actor) {
    s32 direction;

    actor->unk_71 = (u8)(actor->unk_71 & 0x7F);
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)) {
        dungeonApplyCameraOffsetAndSelectTarget((u8 *)actor - 0x20, action_context, 8, 0x300);
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x17;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_96.as_s16 = 0xF;
            (*(s32 *)((u8 *)action_state + 0x8C)) = 0;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;
            (*(u8 **)((u8 *)sprite + 0x2C)) = &D_8016EEC8;
            func_80047784(
                sprite,
                *(&D_8016EEC8 + (((s32)(gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7)),
                0);
            ((Rec_func_800AA258_arg2 *)sprite)->unk_14 = (u16)(((Rec_func_800AA258_arg2 *)sprite)->unk_14 | 0x800);
            dungeonAdvanceStatusTimers(actor);
            actor->unk_6D = (u8)(((u8)actor->unk_6D) - 1);
            direction = ((u16)actor->facing >> 9) & 7;
            actor->target = findEligibleActorAtTileAndHeight(
                actor,
                (((Rec_func_800AA258_arg2 *)sprite)->unk_24 + ((u16 *)dirStepX)[direction]) & 0xFFFF,
                (((Rec_func_800AA258_arg2 *)sprite)->unk_25 + ((u16 *)dirStepY)[direction]) & 0xFFFF,
                actor->unk_88);
        }
    }
}

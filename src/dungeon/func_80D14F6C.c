#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_func_800AA258_arg2.h"

typedef s32 M2C_UNK;


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80047784();
s32 func_8009B25C();
s32 func_800A2B5C();
M2C_UNK func_800A4ACC();
M2C_UNK func_800C7930();
extern u8 D_80174EC8;

/* Start the actor's directional action and record the adjacent tile result. */
void func_8017476C(void *action_state, M2C_UNK action_context, void *sprite, EntityRec *actor) {
    s32 direction;

    actor->unk_71 = (u8)(actor->unk_71 & 0x7F);
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)) {
        func_800C7930((u8 *)actor - 0x20, action_context, 8, 0x300);
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x17;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_96.as_s16 = 0xF;
            (*(s32 *)((u8 *)action_state + 0x8C)) = 0;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;
            (*(u8 **)((u8 *)sprite + 0x2C)) = &D_80174EC8;
            func_80047784(
                sprite,
                *(&D_80174EC8 + (((s32)(gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7)),
                0);
            ((Rec_func_800AA258_arg2 *)sprite)->unk_14 = (u16)(((Rec_func_800AA258_arg2 *)sprite)->unk_14 | 0x800);
            func_800A4ACC(actor);
            actor->unk_6D = (u8)(((u8)actor->unk_6D) - 1);
            direction = ((u16)actor->facing >> 9) & 7;
            actor->target = func_8009B25C(
                actor,
                (((Rec_func_800AA258_arg2 *)sprite)->unk_24 + ((u16 *)dirStepX)[direction]) & 0xFFFF,
                (((Rec_func_800AA258_arg2 *)sprite)->unk_25 + ((u16 *)dirStepY)[direction]) & 0xFFFF,
                actor->unk_88);
        }
    }
}

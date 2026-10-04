#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"


void func_80047784();         /* extern */
typedef struct Ent Ent;
Ent *func_8009C93C(); /* extern */
s32 func_800A2B5C();                          /* extern */
s32 func_800C7930(); /* extern */
extern u8 D_80173C7C;

/* Clear the actor flag and start a directional animation when the action checks pass. */
void func_80171F64(void *action_state, void *action_context, void *sprite, EntityRec *actor) {
    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)) {
        func_800C7930((u8 *)actor - 0x20, action_context, 8, 0x300);
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x11;
            (*(s32 *)((u8 *)action_state + 0x8C)) = 0;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;
            (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_80173C7C;
            func_80047784(sprite, *((((s32) (gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7)
                + &D_80173C7C), 0);
            actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
            func_8009C93C(actor, sprite, actor->facing, 1, 0);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
        }
    }
}

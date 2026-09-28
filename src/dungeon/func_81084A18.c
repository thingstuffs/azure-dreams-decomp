#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"




M2C_UNK func_80047784();         /* extern */
M2C_UNK func_8009C93C(); /* extern */
s32 func_800A2B5C();                          /* extern */
M2C_UNK func_800C7930(); /* extern */
extern u8 D_80175F48;

/* Update actor action state and directional animation when eligible. */
void func_80172218(void *action_state, M2C_UNK action_context, void *sprite, void *actor) {
    ((EntityRec *)actor)->unk_71 = (u8) (((EntityRec *)actor)->unk_71 & 0x7F);
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)) {
        func_800C7930(actor - 0x20, action_context, 8, 0x300);
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x11;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
            (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_80175F48;
            func_80047784(sprite, *((((s32) (gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7) + &D_80175F48), 0);
            ((EntityRec *)actor)->unk_84 = 0x7C;
            ((EntityRec *)actor)->unk_85 = 4;
            ((EntityRec *)actor)->unk_6D = (u8) (((u8)((EntityRec *)actor)->unk_6D) - 1);
            func_8009C93C(actor, sprite, ((EntityRec *)actor)->facing, 1, 0);
        }
    }
}

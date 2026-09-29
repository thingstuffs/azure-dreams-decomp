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
extern u8 D_800E2378;

/* Resets an eligible entity's action state and starts its directional animation. */
void func_801730A4(void *action_state, M2C_UNK action_context, void *sprite, EntityRec *entity) {
    entity->unk_71 = (u8) (entity->unk_71 & 0x7F);
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2B5C(entity) << 0x10) == 0)) {
        func_800C7930((u8 *)entity - 0x20, action_context, 8, 0x300);
        if ((func_800A2B5C(entity) << 0x10) == 0) {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x11;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;
            entity->unk_6D = (u8) (((u8)entity->unk_6D) - 1);
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_98 =
                (u16) (((Rec_func_800A9E70_arg0 *)action_state)->unk_98 & 0xFFF7);
            entity->flags1C = (s32) (entity->flags1C & 0xFFFBFFFF);
            (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_800E2378;
            func_80047784(sprite, *((((s32) (gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7)
                + &D_800E2378), 0);
            func_8009C93C(entity, sprite, entity->facing, 1, 0);
            entity->unk_84 = 0x7C;
            entity->unk_85 = 0;
        }
    }
}

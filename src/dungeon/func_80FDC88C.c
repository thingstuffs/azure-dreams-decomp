#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"

M2C_UNK func_80047784();         /* extern */
M2C_UNK func_8009C93C(); /* extern */
s32 func_800A2B5C();                          /* extern */
s32 func_800C7930(); /* extern */
extern u8 D_80174038[];

/* Updates the actor's action state and directional animation when it can act. */
void func_8017208C(void *action_state, s32 context, void *sprite, void *actor) {
    ((EntityRec *)actor)->unk_71 = (u8) (((EntityRec *)actor)->unk_71 & 0x7F);
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)
        && (func_800C7930(actor - 0x20, context, 8, 0x300), ((func_800A2B5C(actor) << 0x10) == 0))) {
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;
        if (((Rec_func_800A9E70_arg0 *)action_state)->unk_98 & 0x8000) {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x17;
            if (((EntityRec *)actor)->flags1C & 0x1000) {
                ((Rec_func_800A9E70_arg0 *)action_state)->unk_98 =
                    (u16) (((Rec_func_800A9E70_arg0 *)action_state)->unk_98 | 0x4000);
            } else {
                ((Rec_func_800A9E70_arg0 *)action_state)->unk_98 =
                    (u16) (((Rec_func_800A9E70_arg0 *)action_state)->unk_98 & 0xBFFF);
            }
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_AC = (u8) (*(u8 *)((u8 *)&((EntityRec *)actor)->x + 3));
            (*(u8 *)((u8 *)&((EntityRec *)actor)->x + 3)) = 0xFFU;
            ((EntityRec *)actor)->unk_84 = 0x7E;
        } else {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x11;
            ((EntityRec *)actor)->unk_84 = 0x7C;
        }
        do {
            ((EntityRec *)actor)->unk_85 = 8;
        } while (0);
        (*(u8 **)((u8 *)sprite + 0x2C)) = D_80174038;
        func_80047784(sprite, D_80174038[((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);
        ((EntityRec *)actor)->unk_6D = (u8) (((u8)((EntityRec *)actor)->unk_6D) - 1);
        func_8009C93C(actor, sprite, ((EntityRec *)actor)->facing, 1, 0);
        if (!(((Rec_func_800A9E70_arg0 *)action_state)->unk_98 & 0x8000)) {
            ((EntityRec *)actor)->flags1C = (s32) (((EntityRec *)actor)->flags1C & 0xFEFFFFFF);
        }
    }
}


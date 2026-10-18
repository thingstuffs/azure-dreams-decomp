#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"
typedef struct Ent Ent;


void func_80047784();         /* extern */
Ent *prepare_directional_attack(); /* extern */
s32 try_claim_dungeon_action_slot();                          /* extern */
s32 apply_camera_offset_and_select_target(); /* extern */
extern u8 D_800E2378;

/* Resets an eligible entity's action state and starts its directional animation. */
void update_actor_status_and_motion(void *action_state, s32 action_context, void *sprite, EntityRec *entity) {
    entity->unk_71 = (u8) (entity->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(entity) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)entity - 0x20, action_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(entity) << 0x10) == 0) {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x11;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;
            entity->unk_6D = (u8) (((u8)entity->unk_6D) - 1);
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_98 =
                (u16) (((Rec_func_800A9E70_arg0 *)action_state)->unk_98 & 0xFFF7);
            entity->flags1C = (s32) (entity->flags1C & 0xFFFBFFFF);
            (*(u8 **)((u8 *)sprite + 0x2C)) = &D_800E2378;
            func_80047784(sprite, *((((s32) (g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7)
                + &D_800E2378), 0);
            prepare_directional_attack(entity, sprite, entity->facing, 1, 0);
            entity->unk_84 = 0x7C;
            entity->unk_85 = 0;
        }
    }
}

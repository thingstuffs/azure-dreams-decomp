#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"

typedef struct Ent Ent;
Ent *prepare_directional_attack(); /* extern */
s32 try_claim_dungeon_action_slot();                          /* extern */
s32 apply_camera_offset_and_select_target(); /* extern */


/* Clear the entity flag and advance its action state when the checks pass. */
void clear_entity_flag_and_advance_action(Rec_func_800A9E70_arg0 *action_state, void *effect_context, void *update_context,
    EntityRec *entity) {
    entity->unk_71 = (u8) (entity->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(entity) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)entity - 0x20, effect_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(entity) << 0x10) == 0) {
            action_state->unk_8C = 0;
            action_state->unk_9A.as_s8 = 0x11;
            action_state->unk_9B.as_s8 = 0;
            action_state->unk_96.as_s16 = 0;
            entity->unk_6D = (u8) (((u8)entity->unk_6D) - 1);
            prepare_directional_attack(entity, update_context, entity->facing, 1, 0);
            entity->unk_84 = 0x7C;
            entity->unk_85 = 0;
        }
    }
}

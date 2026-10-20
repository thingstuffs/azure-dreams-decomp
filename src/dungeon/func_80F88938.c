#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_800A9E70_arg0.h"

void prepare_directional_attack();
s32 try_claim_dungeon_action_slot();
/* Initialize action state and directional animation when the entity status permits. */
void initialize_bank_actor_action(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, SpriteFrameState *sprite,
    EntityRec *entity) {
    entity->unk_71 &= 0x7F;
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(entity) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((ObjectNodeHeader *)entity - 1, motion_param, 8, 0x300);
        if ((try_claim_dungeon_action_slot(entity) << 0x10) == 0) {
            action_state->unk_9A.as_s8 = 0x11;
            action_state->unk_8C = 0;
            action_state->unk_9B.as_s8 = 0;
            select_sprite_entry(sprite,
                          *((u8 *)sprite->frameTable + (((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7)),
                          0);
            entity->unk_6D--;
            prepare_directional_attack(entity, sprite, entity->facing, 1, 0);
            action_state->unk_98 |= 8;
            entity->unk_84 = 0x7C;
            entity->unk_85 = 0;
        }
    }
}


#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "engine/graphics.h"
typedef struct Ent Ent;

Ent *prepare_directional_attack(); /* extern */
s32 try_claim_dungeon_action_slot();                          /* extern */
s32 apply_camera_offset_and_select_target(); /* extern */
extern u8 baloon_attack_frames;

/*
 * Claims an action slot for Baloon, selects directional attack frames, consumes a pending turn,
 * and prepares damage.
 */
void update_actor_status_and_motion(void *action_state, s32 action_context, SpriteFrameState *sprite, EntityRec *entity) {
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
            (sprite->frameTable) = &baloon_attack_frames;
            select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7)
                + &baloon_attack_frames), 0);
            prepare_directional_attack(entity, sprite, entity->facing, 1, 0);
            entity->unk_84 = 0x7C;
            entity->unk_85 = 0;
        }
    }
}

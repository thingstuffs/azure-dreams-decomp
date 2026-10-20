#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_800A9E70_arg0.h"

extern void prepare_directional_attack();
extern s32 try_claim_dungeon_action_slot();
extern s32 check_entity_interaction_compatibility();

/* Checks whether the actor can transition and starts its directional effect. */
s32 begin_bank_directional_effect(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, SpriteFrameState *sprite, EntityRec *actor)
{
    s32 target_angle;
    u16 status_flags;
    u8 actor_flags;
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */

    actor_flags = actor->unk_71;
    actor_flags &= 0x7F;
    actor->unk_71 = actor_flags;
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    target_angle = place_actor_at_directional_neighbor(actor, sprite->unk_24, sprite->unk_25, actor->facing);
    if ((check_entity_interaction_compatibility(actor, target_angle) << 16) == 0) {
        return 0;
    }

    status_flags = g_dungeon_status.flags;
    if (status_flags & 0x2000) {
        return -1;
    }
    if (!(actor->unk_46 & 0x8000) && (status_flags & 8)) {
        return -1;
    }
    if ((u16)(-get_actor_height_difference(target_angle, actor) + 0x40) >= 0x81U) {
        return 0;
    }
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }

    apply_camera_offset_and_select_target((ObjectNodeHeader *)actor - 1, motion_param, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 16) == 0) {
        action_state->unk_9A.as_u8 = 0x11;
        action_state->unk_9B.as_u8 = 0;
        action_state->unk_8C = 0;
        actor->unk_84 = 0x7C;
        actor->unk_85 = 0;
        sprite->frameTable = D_80174AD4;
        select_sprite_entry(sprite, (D_80174AD4)[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        actor->unk_6D--;
        prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
        return 1;
    }
    return -1;
}


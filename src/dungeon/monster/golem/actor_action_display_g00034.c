#include "shared/entity.h"
/* Actor action display (G00034).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00034 - CL:dungeon/func_81084A18@dungeon/bank_10a3000, CL:dungeon/func_81084A18@dungeon/bank_10a9000, CL:dungeon/func_81084A18@dungeon/bank_10af000, CL:dungeon/func_81084A18@dungeon/bank_10b5000, CL:dungeon/func_81084A18@dungeon/bank_10bb000, CL:dungeon/func_81084A18@dungeon/bank_10c1000.
 */
#include "dungeon/monster/golem/actor_action_display_g00034.h"
#include "dungeon/monster/golem.h"
#include "shared/sprite_frame_state.h"

/* Attempts an actor action and initializes its output and directional display on success. */
s32 attempt_actor_action_and_display(ActorRecord *action_out, ObjectPosition *action_param, SpriteFrameState *actor_info, ActorRecord *acting_actor) {
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */
    u8 *direction_table;
    s32 computed_angle;
    s32 result;
    s32 action_code;
    u16 state_flags;

    acting_actor->movement_queue_state &= 0x7F;
    if (g_dungeon_status.flags & 0x2000) {
        result = -1;
        return result;
    }

    computed_angle = probe_directional_neighbor(acting_actor, actor_info->tile_x,
        actor_info->tile_y, acting_actor->facing);
    if ((check_entity_interaction_compatibility(((void *)(acting_actor)), computed_angle) << 16) == 0) {
        result = 0;
        return result;
    }

    state_flags = g_dungeon_status.flags;
    if (state_flags & 0x2000) {
        result = -1;
        return result;
    }
    if (!(acting_actor->action_flags & 0x8000)) {
        if (state_flags & 8) {
            result = -1;
            return result;
        }
    }

    if ((u16)(-get_actor_height_difference(computed_angle, acting_actor) + 0x3F) >= 0x7F) {
        result = 0;
        return result;
    }
    if ((try_claim_dungeon_action_slot((s32)acting_actor) << 16) != 0) {
        result = -1;
        return result;
    }

    apply_camera_offset_and_select_target((u8 *)acting_actor - 0x20, (void *)action_param, 8, 0x300);
    if ((try_claim_dungeon_action_slot((s32)acting_actor) << 16) != 0) {
        result = -1;
    } else {
        action_out->action_id.s = 0x11;
        action_code = 0x7C;
        action_out->action_phase.s = 0;
        ((S_80172050_2 *)action_out)->unk_8C = 0;
        acting_actor->unk_84 = action_code;
        acting_actor->unk_85 = 4;
        direction_table = &golem_frame_set;
        (actor_info->frameTable) = direction_table;
        select_sprite_entry(actor_info,
            direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + acting_actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_80172050_3 *)acting_actor)->unk_6D--;
        prepare_directional_attack(acting_actor, actor_info, acting_actor->facing, 1, 0);
        result = 1;
    }
    return result;
}

/* Update actor action state and directional animation when eligible. */
void update_eligible_actor_action(ActorRecord *action_state, ObjectPosition *action_context, SpriteFrameState *sprite, ActorRecord *actor) {
    actor->movement_queue_state = (u8) (actor->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot((s32)actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, (void *)action_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot((s32)actor) << 0x10) == 0) {
            action_state->action_id.s = 0x11;
            action_state->action_phase.s = 0;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
            (sprite->frameTable) = &golem_frame_set;
            select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)
                + &golem_frame_set), 0);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 4;
            actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
            prepare_directional_attack((Ent *)actor, (Pos *)sprite, actor->facing, 1, 0);
        }
    }
}

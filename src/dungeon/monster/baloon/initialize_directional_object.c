#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_800A9E70_arg0.h"
typedef struct Ent Ent;

void select_sprite_entry();
Ent *prepare_directional_attack();
s32 get_actor_height_difference();
s32 probe_directional_neighbor();
s32 try_claim_dungeon_action_slot();
s32 check_entity_interaction_compatibility();
s32 apply_camera_offset_and_select_target();

extern u8 baloon_attack_frames;

/* Checks action readiness and initializes the actor state and directional animation. */
s32 initialize_directional_object(void *action_state, s32 action_param, SpriteFrameState *sprite, void *actor) {
    s32 result;
    s32 action_ready;
    s32 direction;
    s32 action_flags;
    u8 *anim_table;

    ((ActorRecord *)actor)->movement_queue_state &= 0x7F;
    action_ready = 0;
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    direction = probe_directional_neighbor(actor, sprite->unk_24,
                         sprite->unk_25,
                         ((ActorRecord *)actor)->facing);
    result = 0;
    if ((check_entity_interaction_compatibility(actor, direction) << 16) == 0) {
        return 0;
    }

    result = -1;
    action_flags = g_dungeon_status.flags;
    if (action_flags & 0x2000) {
        return result;
    }
    if (!(((ActorRecord *)actor)->action_flags & ACTOR_ACTION_PENDING)) {
        if (action_flags & 8) {
            return result;
        }
    }

    if ((u16)((0 - get_actor_height_difference(direction, actor)) + 0x40) >= 0x81U) {
        return action_ready;
    }

    action_ready = 1;
    if (!(((ActorRecord *)actor)->action_flags & ACTOR_ACTION_PENDING)) {
        if (g_dungeon_status.flags & 8) {
            return -1;
        }
    }
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }

    apply_camera_offset_and_select_target((s8 *)actor - 0x20, action_param, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }

    result = action_ready;
    ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_u8 = 0;
    if (result != 0) {
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_u8 = 0x11;
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
        ((ActorRecord *)actor)->unk_84 = 0x7C;
        ((ActorRecord *)actor)->unk_85 = 0;
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_98 &= 0xFFF7;
        ((ActorRecord *)actor)->flags1C &= 0xFFFBFFFF;
        anim_table = &baloon_attack_frames;
        sprite->frameTable = anim_table;
        select_sprite_entry(sprite,
                      anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7],
                      0);
        ((ActorRecord *)actor)->pending_turn_updates--;
        prepare_directional_attack(actor, sprite, ((ActorRecord *)actor)->facing, 1, 0);
    }
    return result;
}

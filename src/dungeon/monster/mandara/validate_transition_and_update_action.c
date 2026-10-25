#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_80172314_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_80172314_2;   /* arg0 in validate_transition_and_update_action */

extern s32 prepare_directional_attack();
extern s32 get_actor_height_difference();
extern s32 probe_directional_neighbor();
extern s32 try_claim_dungeon_action_slot();
extern s32 check_entity_interaction_compatibility();
extern s32 apply_camera_offset_and_select_target();
#include "dungeon/monster/mandara.h"
#include "engine/graphics.h"

/* Validate an actor transition and update its state and directional animation on success. */
s32 validate_transition_and_update_action(void *state, s32 transition_id, SpriteFrameState *sprite, ActorRecord *actor)
{
    s16 transitioned;
    s32 target_heading;

    actor->movement_queue_state &= 0x7F;
    transitioned = 0;
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }
    target_heading = probe_directional_neighbor(actor, sprite->tile_x,
                           sprite->tile_y, actor->facing);
    if ((check_entity_interaction_compatibility(actor, target_heading) << 16) == 0) {
        return 0;
    }
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }
    if (!(actor->action_flags & ACTOR_ACTION_PENDING) && (g_dungeon_status.flags & 8)) {
        return -1;
    }
    if ((u16)(-get_actor_height_difference(target_heading, actor) + 0x40) >= 0x81U) {
        return transitioned;
    }

    transitioned = 1;
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }
    apply_camera_offset_and_select_target((u8 *)actor - 0x20, transition_id, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }
    {
        u16 state_flags;

        state_flags = ((S_80172314_2 *)state)->unk_98;
        ((S_80172314_2 *)state)->unk_9B = 0;
        ((S_80172314_2 *)state)->unk_8C = 0;
        if (state_flags & 0x8000) {
            ((S_80172314_2 *)state)->unk_9A = 0x17;
            actor->unk_84 = 0x28;
            actor->unk_85 = 0x10;
        } else {
            ((S_80172314_2 *)state)->unk_9A = 0x11;
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
        }
    }

    (sprite->frameTable) = mandara_direction_frames;
    select_sprite_entry(sprite,
                  mandara_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                  0);
    actor->pending_turn_updates--;
    prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
    return transitioned;
}

/* MECHANISM: True-rowbase 0x80172484/0x801724E8 are local joins; placing the abort label before the
   success body reproduces the branch polarity and exact 0x38-frame CFG. */

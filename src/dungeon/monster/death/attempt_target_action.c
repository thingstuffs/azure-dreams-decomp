#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"






extern void prepare_directional_attack(void *, void *, s16, s32, s32);
extern s32 get_actor_height_difference(s32, void *);
extern s32 probe_directional_neighbor(void *, u8, u8, s16);
extern s16 try_claim_dungeon_action_slot(ActorRecord *actor);
extern s32 check_entity_interaction_compatibility(void *, s32);
extern void apply_camera_offset_and_select_target(void *,void *, s32, s32);

/* Attempt an action toward the target and update actor state on success. */
s32 attempt_target_action(ActorRecord *action_state, ObjectPosition *effect_arg, SpriteFrameState *target, ActorRecord *actor) {
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */
    s32 target_direction;

    actor->movement_queue_state &= 0x7F;

    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    target_direction = probe_directional_neighbor(
        actor,
        target->tile_x,
        target->tile_y,
        actor->facing);

    if ((check_entity_interaction_compatibility(actor, target_direction) << 16) == 0) {
        return 0;
    }

    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    if (!(actor->action_flags & ACTOR_ACTION_PENDING) &&
        (g_dungeon_status.flags & 8)) {
        return -1;
    }

    if ((u32)(((0 - get_actor_height_difference(target_direction, actor)) + 0x40) & 0xFFFF) >= 0x81U) {
        return 0;
    }

    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }

    apply_camera_offset_and_select_target((u8 *)actor - 0x20, effect_arg, 8, 0x300);

    if ((try_claim_dungeon_action_slot(actor) << 16) == 0) {
        action_state->action_id.u = 0x11;
        action_state->action_phase.u = 0;
        action_state->unk_8C.run = 0;
        actor->unk_84 = 0x7C;
        actor->unk_85 = 4;
        actor->pending_turn_updates--;

        prepare_directional_attack(actor, target, actor->facing, 1, 0);
        return 1;
    }

    return -1;
}

/* MECHANISM: An unused 8-byte local (unused[2]) plus the natural long-lived
   args/result/global base produce the retail 0x40 frame and s0-s5 roles.
   The early failure paths return -1 directly and the success block sits inside the
   final test's true arm (a failure-first `!= 0` return measured dist 9); explicit (0 - call) + 0x40 emits retail's negu/addiu arithmetic in v0. */

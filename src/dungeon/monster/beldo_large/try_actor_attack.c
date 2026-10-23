#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_800A9E70_arg0.h"

extern void prepare_directional_attack(void *, void *, s16, s32, s32);
extern s32 get_actor_height_difference(s32, void *);
extern s32 probe_directional_neighbor(void *, u8, u8, s16);
extern s32 try_claim_dungeon_action_slot(void *);
extern s32 check_entity_interaction_compatibility(void *, s32);
extern void apply_camera_offset_and_select_target(void *, s32, s32, s32);

/* Attempts an action toward the target and initializes the action state on success. */
/* Starts Beldo's attack against a compatible neighbor within 64 height units; returns 1, 0 if unsuitable,
 * or -1 if busy. */
s32 try_actor_attack(Rec_func_800A9E70_arg0 *action_state, s32 action_id, SpriteFrameState *target, ActorRecord *actor) {
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

    apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_id, 8, 0x300);

    if ((try_claim_dungeon_action_slot(actor) << 16) == 0) {
        action_state->unk_9A.as_s8 = 0x11;
        action_state->unk_9B.as_s8 = 0;
        action_state->unk_8C = 0;
        *(unsigned char *)&actor->unk_84 = 0x80;
        actor->unk_85 = 32;
        actor->pending_turn_updates--;

        prepare_directional_attack(actor, target, actor->facing, 1, 0);
        return 1;
    }

    return -1;
}

/* MECHANISM: An unused 8-byte local (unused[2]) plus the natural long-lived
   args/result/global base produce the retail 0x40 frame and s0-s5 roles.
   A shared mid-function failure block restores both branch targets and polarity;
   explicit (0 - call) + 0x40 emits retail's negu/addiu arithmetic in v0. */

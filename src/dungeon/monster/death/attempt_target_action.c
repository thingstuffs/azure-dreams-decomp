#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_80172920_1 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80172920_1;   /* flags in attempt_target_action */


typedef struct S_80172920_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_80172920_3;   /* arg0 in attempt_target_action */


extern void prepare_directional_attack(void *, void *, s16, s32, s32);
extern s32 get_actor_height_difference(s32, void *);
extern s32 probe_directional_neighbor(void *, u8, u8, s16);
extern s32 try_claim_dungeon_action_slot(void *);
extern s32 check_entity_interaction_compatibility(void *, s32);
extern void apply_camera_offset_and_select_target(void *, s32, s32, s32);

/* Attempt an action toward the target and update actor state on success. */
s32 attempt_target_action(S_80172920_3 *action_state, s32 effect_arg, Rec_D_80082E80 *target, void *actor) {
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */
    s32 target_direction;

    ((ActorRecord *)actor)->movement_queue_state &= 0x7F;

    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    target_direction = probe_directional_neighbor(
        actor,
        target->unk_24,
        target->unk_25,
        ((ActorRecord *)actor)->facing);

    if ((check_entity_interaction_compatibility(actor, target_direction) << 16) == 0) {
        return 0;
    }

    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    if (!(((ActorRecord *)actor)->action_flags & ACTOR_ACTION_PENDING) &&
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
        action_state->unk_9A = 0x11;
        action_state->unk_9B = 0;
        action_state->unk_8C = 0;
        ((ActorRecord *)actor)->unk_84 = 0x7C;
        ((ActorRecord *)actor)->unk_85 = 4;
        ((ActorRecord *)actor)->pending_turn_updates--;

        prepare_directional_attack(actor, target, ((ActorRecord *)actor)->facing, 1, 0);
        return 1;
    }

    return -1;
}

/* MECHANISM: An unused 8-byte local (unused[2]) plus the natural long-lived
   args/result/global base produce the retail 0x40 frame and s0-s5 roles.
   The early failure paths return -1 directly and the success block sits inside the
   final test's true arm (a failure-first `!= 0` return measured dist 9); explicit (0 - call) + 0x40 emits retail's negu/addiu arithmetic in v0. */

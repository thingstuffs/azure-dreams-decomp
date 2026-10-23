#include "shared/actor_property_flags.h"
#include "shared/actor_status_flags.h"
/* Actor motion rendering (G00340). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800ACDDC. */
#include "dungeon/effect/actor_motion_rendering_g00340.h"

/* Updates actor state from pending entity flags when entity processing is allowed. */
void update_pending_entity_action(Rec_func_800A9E70_arg0 *actor, s32 update_arg1, s32 update_arg2, EntityRec *entity) {
    void *active_entity;
    s32 entity_flags;
    s32 next_state;

    if ((entity->flags1C & ACTOR_PLAYER_SIDE) || (entity->flags14 & ACTOR_PARTY_MEMBER)) {
        if ((u32)(actor->unk_9A.as_u8 - 0x13) >= 2U) {
            if (entity->unk_6D == 0) {
                if (pending_marked_actor_count == 0) {
                    if ((has_pending_dungeon_activity(entity) << 0x10) != 0) {
                        return;
                    }
                } else {
                    active_entity = g_dungeon_status.active_actor;
                    if (active_entity != entity) {
                        if (!((((s32)g_dungeon_status.pending_display_owner) == 0) && (active_entity == 0) &&
                              (g_dungeon_status.activity_counts.parts.pending_movement_count == 0) &&
                              !(g_dungeon_status.flags & 0x2008) &&
                              (entity->unk_43 == 0xFD))) {
                            return;
                        }
                        g_dungeon_status.active_actor = entity;
                    }
                    if (entity->unk_43 != 0xFD) {
                        return;
                    }
                }
                if (entity->flags1C & 0x400000) {
                    actor->unk_8C = 0;
                    entity_flags = entity->flags14;
                    entity->flags1C &= 0xFFBFFFFF;
                    if (entity_flags & 0x20000000) {
                        entity->flags14 = entity_flags | 0x400000;
                        actor->unk_AD = 0;
                        begin_actor_flagged_action(actor, update_arg1, update_arg2, entity);
                        return;
                    }
                    entity->flags14 = entity_flags & 0xFFBFFFFF;
                    next_state = entity_flags & ACTOR_PARTY_MEMBER;
                    if (!next_state) {
                        next_state = 2;
                    } else {
                        next_state = 1;
                    }
                    actor->unk_9A.as_u8 = next_state;
                    actor->unk_9B.as_u8 = 0;
                } else if (entity->flags1C & 0x02000000) {
                    actor->unk_8C = 0;
                    entity->unk_71 = 0;
                    entity->flags1C &= 0xFDFFFFFF;
                    if (entity->flags14 & 0x20000000) {
                        initialize_actor_object_action(actor, update_arg1, update_arg2, entity);
                        return;
                    }
                    actor->unk_9A.as_u8 = 0;
                    actor->unk_9B.as_u8 = 0;
                }
            }
        }
    }
}

/* Runs actor callbacks, advances motion, and updates ground contact and rendering. */
void update_actor_motion_and_rendering(u8 *actor, u8 *motion, u8 *render) {
    u16 global_flags = g_dungeon_status.flags;
    u8 *actor_alias = actor;
    s16 old_state;
    ActorCallback callback;
    s16 ground_height;
    u16 old_height;

    if (global_flags & 0x2000) {
        U8_AT(actor, 0x71) &= 0x7F;
        return;
    }

    old_state = (s8)U8_AT(actor, 0x6D);
    U16_AT(actor, 0x98) &= 0xFBFF;

    if (U32_AT(actor, 0x14) & 0x00100000) {
        return;
    }

    update_pending_entity_action(actor, motion, render, actor);

    callback = *(ActorCallback *)(actor + 0x8C);
    if (callback != 0) {
        callback(actor, motion, render, actor);
    }

    actor_render_callbacks[U8_AT(actor, 0x9A)](actor, motion, render, actor);

    if ((s16)old_state != S8_AT(actor, 0x6D)) {
        try_move_actor_to_valid_position(actor, motion, render, actor);
    }

    if (!(U16_AT(render, 0x14) & 0x8000)) {
        apply_monster_koyaw_data((void *)U32_AT(actor, 0x1C), render + 0xC);
    }
    U16_AT(render, 0x14) |= 0x7000;

    S32_AT(motion, 0x0) += S32_AT(motion, 0xC);
    S32_AT(motion, 0x4) += S32_AT(motion, 0x10);

    if (U16_AT(actor, 0x98) & 8) {
        U8_AT(actor, 0x9D) = 0;
    } else {
        S32_AT(motion, 0x14) += (S8_AT(actor, 0x9D) * 5) << 14;
        U8_AT(actor, 0x9D)++;
    }

    S32_AT(actor, 0x90) += S32_AT(motion, 0x14);

    if (!(U16_AT(actor, 0x98) & 4) &&
        (ground_height = sample_terrain_surface_height(
             U16_AT(motion, 2),
             U16_AT(motion, 6),
             (s16)(U16_AT(actor_alias, 0x88) - 0x20))) < 0x200) {
        old_height = U16_AT(actor_alias, 0x88);
        if ((S16_AT(actor, 0x92) + S16_AT(actor_alias, 0x88)) < (s16)ground_height) {
            U32_AT(actor_alias, 0x1C) &= 0xF7FFFFFF;
        } else {
            if ((s16)ground_height >= S16_AT(actor_alias, 0x88)) {
                S32_AT(actor, 0x90) = 0;
            } else {
                S16_AT(actor, 0x92) = (s16)ground_height - old_height;
            }
            U8_AT(actor, 0x9D) = 0;
            S32_AT(motion, 0x14) = 0;
            U32_AT(actor_alias, 0x1C) |= 0x08000000;
        }
        if (U32_AT(actor_alias, 0x1C) & 0x40000000) {
            U32_AT(actor_alias, 0x1C) &= 0xBFFFFFFF;
            ground_height = sample_terrain_surface_height(
                (U8_AT(render, 0x24) << 6) | 0x20,
                (U8_AT(render, 0x25) << 6) | 0x20,
                (s16)(U16_AT(actor_alias, 0x88) - 0x20));
            S16_AT(actor, 0x92) += U16_AT(actor_alias, 0x88) - (s16)ground_height;
            U16_AT(actor_alias, 0x88) = ground_height;
        }
    } else {
        U32_AT(actor_alias, 0x1C) &= 0xF7FFFFFF;
    }

    U16_AT(motion, 0xA) = U16_AT(actor_alias, 0x88) + U16_AT(actor, 0x92);
    U16_AT(render, 0x14) |= 0x40;
}

#include "shared/actor_status_flags.h"
/* Unicorn directional movement, tile recentering, and sprite removal. */
#include "shared/dungeon_status.h"
#include "dungeon/monster/unicorn/update_directional_motion_and_recenter_actor.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"

/* Updates directional movement, decelerates it, and recenters the actor on its tile. */
void update_directional_motion_and_recenter_actor(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, void *actor)
{
    s16 timer;
    s32 direction;
    s32 tracked_entity;

    direction = (((EntityRec *)actor)->unk_6A >> 9) & 7;
    switch (body->action_phase.u) {
    case 0:
        apply_clamped_actor_value_delta(actor);
        motion->velocity_x =
            *(s16 *)((u8 *)((s8 *)dir_step_x) + (direction * 2)) << 19;
        motion->velocity_y =
            *(s16 *)((u8 *)((s8 *)dir_step_y) + (direction * 2)) << 19;
        body->action_phase.u++;

        if (((EntityRec *)actor)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(body, motion, sprite, &D_80174D5C);
            return;
        }
        if (sprite->flags & 0x8000) {
            body->action_timer.s = 0;
            body->action_phase.u = 2;
            return;
        }
        if (((EntityRec *)actor)->flags1C & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            timer = 8;
        } else {
            timer = -1;
        }
        body->action_timer.s = timer;
        motion->velocity_x -= motion->velocity_x / 4;
        motion->velocity_y -= motion->velocity_y / 4;
                        /* fall through */

    case 1:
        motion->velocity_x -=
            *(s16 *)((u8 *)((s8 *)dir_step_x) + (direction * 2)) << 14;
        motion->velocity_y -=
            *(s16 *)((u8 *)((s8 *)dir_step_y) + (direction * 2)) << 14;
        if (body->action_timer.s > 0) {
            body->action_timer.s = body->action_timer.u - 1;
        } else if (sprite->flags & 0x6000) {
            body->action_timer.s = 0;
        }
        if (body->action_timer.s != 0) {
            return;
        }
        if (((EntityRec *)actor)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(body, motion, sprite, &D_80174D5C);
            return;
        }
        body->action_timer.s = 8;
        body->action_phase.u++;
        return;

    case 2:
        if (body->action_timer.s != 0) {
            {
                s32 tile_x;
                s32 current_x;

                tile_x = sprite->tile_x << 6;
                current_x = motion->x.w.i - 0x20;
                motion->velocity_x =
                    ((tile_x - current_x) << 15) >> 1;
            }
            {
                s32 tile_y;
                s32 current_y;

                tile_y = sprite->tile_y << 6;
                current_y = motion->y.w.i - 0x20;
                motion->velocity_y =
                    ((tile_y - current_y) << 15) >> 1;
            }
        }
        timer = body->action_timer.u - 1;
        body->action_timer.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);

        tracked_entity = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_entity == (s32)((u8 *)actor - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_entity & 0x7FFFFFFF;
        }
        body->unk_8C.address = &unicorn_action_continuation_address;
        return;

    default:
        return;
    }
}

/* Fade the entity sprite, then remove the entity and update its tile flags. */
void fade_and_remove_entity_sprite(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, SpriteFrameState *entity)
{
    s32 state;
    s32 entity_flags;
    u16 fade_delay;
    s32 tracked_entity;
    s32 tile_x;
    s32 tile_y;
    s32 tile_mask;

    state = body->action_phase.u;
    switch (state) {
    case 0:
        if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
            return;
        }
        body->action_phase.u = 1;
                        /* fallthrough */
    case 1:
        entity_flags = *(s32 *)&entity->flags;
        if (entity_flags & 0x4000) {
            if (!(entity_flags & 0x20000000)) {
                announce_familiar_defeat(entity);
            }
        }
        play_sound_if_enabled(0x805);
        body->action_timer.u = 4;
        body->action_phase.u++;
        sprite->clut -= 0x80;
                        /* fallthrough */
    case 2:
        break;
    default:
        return;
    }

    *(s32 *)&entity->scale_x |= 0x10000000;
    fade_delay = body->action_timer.u - 1;
    body->action_timer.u = fade_delay;
    if ((s16)fade_delay <= 0) {
        if (sprite->color.c.r >= 0x10) {
            sprite->color.word += 0xFFEFEFF0;
        }
        sprite->tpage_abr = 0x20;
        sprite->flags |= 0xC;
    } else {
        sprite->color.word = 0x808080;
    }

    if (!(sprite->flags & 0x8000)) {
        if (sprite->color.c.r >= 0x10) {
            return;
        }
    }

    tracked_entity = ((s32)g_dungeon_status.pending_display_owner);
    if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
        g_dungeon_status.pending_display_owner = tracked_entity & 0x7FFFFFFF;
    }
    distribute_experience_and_report_gains(entity);
    detach_record_and_update_slot_state(entity);

    tile_x = sprite->tile_x;
    tile_y = sprite->tile_y;
    tile_mask = 0x3000;
    if (*(s32 *)&entity->scale_x & 0x2000) {
        tile_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(tile_x, tile_y, tile_mask);
    unlink_entity_node(entity);
    (*(u16 *)((u8 *)entity + -2)) |= NODE_REMOVE;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;

    return;
}

#include "shared/actor_status_flags.h"
/* Unicorn directional movement, tile recentering, and sprite removal. */
#include "shared/dungeon_status.h"
#include "dungeon/monster/unicorn/update_directional_motion_and_recenter_actor.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"

/* Updates directional movement, decelerates it, and recenters the actor on its tile. */
void update_directional_motion_and_recenter_actor(ActorActionTimerView *action, ObjectPosition *motion, SpriteFrameState *actor, void *source)
{
    s16 timer;
    s32 direction;
    s32 tracked_entity;

    direction = (((EntityRec *)source)->unk_6A >> 9) & 7;
    switch (action->unk_9B) {
    case 0:
        apply_clamped_actor_value_delta(source);
        motion->velocity_x =
            *(s16 *)((u8 *)((s8 *)dir_step_x) + (direction * 2)) << 19;
        motion->velocity_y =
            *(s16 *)((u8 *)((s8 *)dir_step_y) + (direction * 2)) << 19;
        action->unk_9B++;

        if (((EntityRec *)source)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, actor, &D_80174D5C);
            return;
        }
        if (actor->flags & 0x8000) {
            action->unk_96.s = 0;
            action->unk_9B = 2;
            return;
        }
        if (((EntityRec *)source)->flags1C & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            timer = 8;
        } else {
            timer = -1;
        }
        action->unk_96.s = timer;
        motion->velocity_x -= motion->velocity_x / 4;
        motion->velocity_y -= motion->velocity_y / 4;
                        /* fall through */

    case 1:
        motion->velocity_x -=
            *(s16 *)((u8 *)((s8 *)dir_step_x) + (direction * 2)) << 14;
        motion->velocity_y -=
            *(s16 *)((u8 *)((s8 *)dir_step_y) + (direction * 2)) << 14;
        if (action->unk_96.s > 0) {
            action->unk_96.s = action->unk_96.u - 1;
        } else if (actor->flags & 0x6000) {
            action->unk_96.s = 0;
        }
        if (action->unk_96.s != 0) {
            return;
        }
        if (((EntityRec *)source)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, actor, &D_80174D5C);
            return;
        }
        action->unk_96.s = 8;
        action->unk_9B++;
        return;

    case 2:
        if (action->unk_96.s != 0) {
            {
                s32 tile_x;
                s32 current_x;

                tile_x = actor->unk_24 << 6;
                current_x = motion->x.w.i - 0x20;
                motion->velocity_x =
                    ((tile_x - current_x) << 15) >> 1;
            }
            {
                s32 tile_y;
                s32 current_y;

                tile_y = actor->unk_25 << 6;
                current_y = motion->y.w.i - 0x20;
                motion->velocity_y =
                    ((tile_y - current_y) << 15) >> 1;
            }
        }
        timer = action->unk_96.u - 1;
        action->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, actor->unk_24, actor->unk_25);

        tracked_entity = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_entity == (s32)((u8 *)source - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_entity & 0x7FFFFFFF;
        }
        action->unk_8C = &D_80170E7C;
        return;

    default:
        return;
    }
}

/* Fade the entity sprite, then remove the entity and update its tile flags. */
void fade_and_remove_entity_sprite(void *action, void *unused, void *sprite, SpriteFrameState *entity)
{
    s32 state;
    s32 entity_flags;
    u16 fade_delay;
    s32 tracked_entity;
    s32 tile_x;
    s32 tile_y;
    s32 tile_mask;

    state = ((T_80173450_S_80173450_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
            return;
        }
        ((T_80173450_S_80173450_0 *)action)->unk_9B = 1;
                        /* fallthrough */
    case 1:
        entity_flags = *(s32 *)&entity->flags;
        if (entity_flags & 0x4000) {
            if (!(entity_flags & 0x20000000)) {
                announce_familiar_defeat(entity);
            }
        }
        play_sound_if_enabled(0x805);
        ((T_80173450_S_80173450_0 *)action)->unk_96 = 4;
        ((T_80173450_S_80173450_0 *)action)->unk_9B++;
        ((T_80173450_S_80173450_2 *)sprite)->unk_12 -= 0x80;
                        /* fallthrough */
    case 2:
        break;
    default:
        return;
    }

    *(s32 *)&entity->scale_x |= 0x10000000;
    fade_delay = ((T_80173450_S_80173450_0 *)action)->unk_96 - 1;
    ((T_80173450_S_80173450_0 *)action)->unk_96 = fade_delay;
    if ((s16)fade_delay <= 0) {
        if (((T_80173450_S_80173450_2 *)sprite)->unk_0C.u8 >= 0x10) {
            ((T_80173450_S_80173450_2 *)sprite)->unk_0C.s32 += 0xFFEFEFF0;
        }
        ((T_80173450_S_80173450_2 *)sprite)->unk_10 = 0x20;
        ((T_80173450_S_80173450_2 *)sprite)->unk_14 |= 0xC;
    } else {
        ((T_80173450_S_80173450_2 *)sprite)->unk_0C.s32 = 0x808080;
    }

    if (!(((T_80173450_S_80173450_2 *)sprite)->unk_14 & 0x8000)) {
        if (((T_80173450_S_80173450_2 *)sprite)->unk_0C.u8 >= 0x10) {
            return;
        }
    }

    tracked_entity = ((s32)g_dungeon_status.pending_display_owner);
    if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
        g_dungeon_status.pending_display_owner = tracked_entity & 0x7FFFFFFF;
    }
    distribute_experience_and_report_gains(entity);
    detach_record_and_update_slot_state(entity);

    tile_x = ((T_80173450_S_80173450_2 *)sprite)->unk_24;
    tile_y = ((T_80173450_S_80173450_2 *)sprite)->unk_25;
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

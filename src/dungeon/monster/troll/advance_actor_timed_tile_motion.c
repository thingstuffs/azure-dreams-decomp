#include "dungeon/monster/troll/advance_actor_timed_tile_motion.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"

/* Updates timed movement toward the entity's tile and selects the next behavior. */
void advance_actor_timed_tile_motion(T_80174C44_S_80174C44_0 *controller, ObjectPosition *transform, SpriteFrameState *entity, void *actor)
{
    s32 actor_kind;
    s16 timer;
    u16 old_timer;
    s32 axis_pos;
    s32 axis_step;

    switch (controller->phase) {
    case 0:
        apply_clamped_actor_value_delta(actor);
        controller->timer.s = 6;
        controller->phase = controller->phase + 1;
        if (((EntityRec *)actor)->unk_28 == 0) {
            transform->velocity_z = 0;
            transform->velocity_y = 0;
            transform->velocity_x = 0;
            actor_kind = ((EntityRec *)actor)->unk_48;
            switch (actor_kind) {
            case 13:
                begin_actor_display_action(controller, transform, entity, troll_frame_set_5);
                break;
            case 14:
                begin_actor_display_action(controller, transform, entity, troll_frame_set_6);
                break;
            case 15:
                begin_actor_display_action(controller, transform, entity, troll_frame_set_7);
                break;
            }
        } else {
            if ((entity->flags & 0x8000) == 0) {
                return;
            }
            controller->timer.s = 0;
            controller->phase = 3;
        }
        break;
    case 1:
        timer = (u16)controller->timer.u - 1;
        controller->timer.s = timer;
        if (timer > 0) {
            transform->velocity_x =
                *(s16 *)((u8 *)((s8 *)dir_step_x) +
                    ((((EntityRec *)actor)->unk_6A >> 8) & 0xE)) << 18;
            transform->velocity_y =
                *(s16 *)((u8 *)((s8 *)dir_step_y) +
                    ((((EntityRec *)actor)->unk_6A >> 8) & 0xE)) << 18;
        } else if (timer == 0) {
            transform->velocity_x =
                *(s16 *)((u8 *)((s8 *)dir_step_x) +
                    ((((EntityRec *)actor)->unk_6A >> 8) & 0xE)) << 18;
            transform->velocity_y =
                *(s16 *)((u8 *)((s8 *)dir_step_y) +
                    ((((EntityRec *)actor)->unk_6A >> 8) & 0xE)) << 18;
            controller->timer.s = 12;
            controller->phase = controller->phase + 1;
        }
        break;
    case 2:
        if (((EntityRec *)actor)->unk_28 == 0) {
            transform->velocity_z = 0;
            transform->velocity_y = 0;
            transform->velocity_x = 0;
            actor_kind = ((EntityRec *)actor)->unk_48;
            switch (actor_kind) {
            case 13:
                begin_actor_display_action(controller, transform, entity, troll_frame_set_5);
                break;
            case 14:
                begin_actor_display_action(controller, transform, entity, troll_frame_set_6);
                break;
            case 15:
                begin_actor_display_action(controller, transform, entity, troll_frame_set_7);
                break;
            }
        } else {
            timer = controller->timer.s;
            if (timer != 0) {
                axis_step = entity->tile_x;
                axis_pos = transform->x.w.i;
                axis_step <<= 6;
                axis_pos -= 0x20;
                axis_step -= axis_pos;
                axis_step = (axis_step << 16) / timer;
                axis_pos = transform->y.w.i;
                transform->velocity_x = axis_step;
                axis_pos -= 0x20;
                axis_step = (entity->tile_y << 6) - axis_pos;
                axis_step = (axis_step << 16) / controller->timer.s;
                transform->velocity_y = axis_step;
            }

            old_timer = controller->timer.u;
            controller->timer.s = old_timer - 1;
            if ((s32)(old_timer << 16) <= 0) {
                transform->velocity_z = 0;
                transform->velocity_y = 0;
                transform->velocity_x = 0;
                controller->phase = controller->phase + 1;
            }
        }
        break;
    case 3:
        transform->velocity_z = 0;
        transform->velocity_y = 0;
        transform->velocity_x = 0;
        set_record_integer_tile_center(transform, entity->tile_x, entity->tile_y);
        if (((s32)g_dungeon_status.pending_display_owner) == (s32)actor - 0x20) {
            *(s32 *)&g_dungeon_status.pending_display_owner &= 0x7FFFFFFF;
        }
        controller->unk_8C = update_actor_behavior;
        break;
    }
}

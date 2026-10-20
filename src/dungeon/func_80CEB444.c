#include "dungeon/monster/troll/advance_actor_timed_tile_motion.h"

/* Updates timed movement toward the entity's tile and selects the next behavior. */
void advance_actor_timed_tile_motion(T_80174C44_S_80174C44_0 *controller, EntityRec *transform, Rec_D_80082E80 *entity, void *actor)
{
    s32 actor_kind;
    s16 timer;
    u16 old_timer;
    s32 axis_pos;
    s32 axis_step;

    switch (controller->unk_9B) {
    case 0:
        apply_clamped_actor_value_delta(actor);
        controller->unk_96.s = 6;
        controller->unk_9B = controller->unk_9B + 1;
        if (((EntityRec *)actor)->unk_28 == 0) {
            transform->flags14 = 0;
            transform->unk_10 = 0;
            transform->unk_0C = 0;
            actor_kind = ((EntityRec *)actor)->unk_48;
            switch (actor_kind) {
            case 13:
                begin_actor_display_action(controller, transform, entity, D_80175E3C);
                break;
            case 14:
                begin_actor_display_action(controller, transform, entity, D_80175E44);
                break;
            case 15:
                begin_actor_display_action(controller, transform, entity, D_80175E4C);
                break;
            }
        } else {
            if ((entity->unk_14.at00_u16.v & 0x8000) == 0) {
                return;
            }
            controller->unk_96.s = 0;
            controller->unk_9B = 3;
        }
        break;
    case 1:
        timer = (u16)controller->unk_96.u - 1;
        controller->unk_96.s = timer;
        if (timer > 0) {
            transform->unk_0C =
                *(s16 *)((u8 *)((s8 *)dir_step_x) +
                    ((((EntityRec *)actor)->unk_6A >> 8) & 0xE)) << 18;
            transform->unk_10 =
                *(s16 *)((u8 *)((s8 *)dir_step_y) +
                    ((((EntityRec *)actor)->unk_6A >> 8) & 0xE)) << 18;
        } else if (timer == 0) {
            transform->unk_0C =
                *(s16 *)((u8 *)((s8 *)dir_step_x) +
                    ((((EntityRec *)actor)->unk_6A >> 8) & 0xE)) << 18;
            transform->unk_10 =
                *(s16 *)((u8 *)((s8 *)dir_step_y) +
                    ((((EntityRec *)actor)->unk_6A >> 8) & 0xE)) << 18;
            controller->unk_96.s = 12;
            controller->unk_9B = controller->unk_9B + 1;
        }
        break;
    case 2:
        if (((EntityRec *)actor)->unk_28 == 0) {
            transform->flags14 = 0;
            transform->unk_10 = 0;
            transform->unk_0C = 0;
            actor_kind = ((EntityRec *)actor)->unk_48;
            switch (actor_kind) {
            case 13:
                begin_actor_display_action(controller, transform, entity, D_80175E3C);
                break;
            case 14:
                begin_actor_display_action(controller, transform, entity, D_80175E44);
                break;
            case 15:
                begin_actor_display_action(controller, transform, entity, D_80175E4C);
                break;
            }
        } else {
            timer = controller->unk_96.s;
            if (timer != 0) {
                axis_step = entity->unk_24;
                axis_pos = transform->x.w.i;
                axis_step <<= 6;
                axis_pos -= 0x20;
                axis_step -= axis_pos;
                axis_step = (axis_step << 16) / timer;
                axis_pos = transform->y.w.i;
                transform->unk_0C = axis_step;
                axis_pos -= 0x20;
                axis_step = (entity->unk_25 << 6) - axis_pos;
                axis_step = (axis_step << 16) / controller->unk_96.s;
                transform->unk_10 = axis_step;
            }

            old_timer = controller->unk_96.u;
            controller->unk_96.s = old_timer - 1;
            if ((s32)(old_timer << 16) <= 0) {
                transform->flags14 = 0;
                transform->unk_10 = 0;
                transform->unk_0C = 0;
                controller->unk_9B = controller->unk_9B + 1;
            }
        }
        break;
    case 3:
        transform->flags14 = 0;
        transform->unk_10 = 0;
        transform->unk_0C = 0;
        set_record_integer_tile_center(transform, entity->unk_24, entity->unk_25);
        if (((s32)g_dungeon_status.unk_10) == (s32)actor - 0x20) {
            *(s32 *)&g_dungeon_status.unk_10 &= 0x7FFFFFFF;
        }
        controller->unk_8C = update_actor_behavior;
        break;
    }
}

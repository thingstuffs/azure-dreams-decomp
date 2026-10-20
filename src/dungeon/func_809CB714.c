#include "modules/dungeon_resource03_slot0.h"
#include "shared/sprite_frame_state.h"

void slow_directional_movement_to_tile(R03_80172F14_S_80172F14_1 *controller, EntityRec *motion, SpriteFrameState *entity, void *source)
{
    s16 timer;
    s32 direction;
    s32 speed_limit;
    s32 tracked_object;

    direction = (((EntityRec *)source)->unk_6A >> 9) & 7;

    switch (controller->unk_9B) {
    case 0:
        apply_clamped_actor_value_delta(source);
        motion->unk_0C =
            *(s16 *)((u8 *)((s8 *)dir_step_x) + direction * 2) << 19;
        motion->unk_10 =
            *(s16 *)((u8 *)((s8 *)dir_step_y) + direction * 2) << 19;
        controller->unk_9B++;

        if (((EntityRec *)source)->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            begin_actor_display_action(controller, motion, entity, ((s32 *)D_80173CC4));
            return;
        }
        if (entity->flags & 0x8000) {
            controller->unk_96.s = 0;
            controller->unk_9B = 2;
            return;
        }

        timer = 5;
        if (((EntityRec *)source)->flags1C & 0x228) {
            timer = 8;
        }
        controller->unk_96.s = timer;

        {
            s32 velocity = motion->unk_0C;
            motion->unk_0C = velocity - velocity / 4;
        }
        {
            s32 velocity = motion->unk_10;
            motion->unk_10 = velocity - velocity / 4;
        }
                        /* fall through */

    case 1:
        speed_limit = 0x7FFF;
        {
            s32 velocity = motion->unk_0C;
            s32 magnitude = velocity;

            magnitude = abs(magnitude);
            if (speed_limit < magnitude) {
                motion->unk_0C = velocity -
                    (*(s16 *)((u8 *)((s8 *)dir_step_x) + direction * 2) << 15);
            }
        }
        {
            s32 velocity = motion->unk_10;
            s32 magnitude = velocity;

            magnitude = abs(magnitude);
            if (speed_limit < magnitude) {
                motion->unk_10 = velocity -
                    (*(s16 *)((u8 *)((s8 *)dir_step_y) + direction * 2) << 15);
            }
        }

        if (controller->unk_96.s > 0) {
            controller->unk_96.s = controller->unk_96.u - 1;
        } else {
            if (entity->flags & 0x6000) {
                controller->unk_96.s = 0;
            }

            if (((EntityRec *)source)->unk_28 != 0) {
                {
                    s32 tile_pos = entity->unk_24 << 6;
                    s32 current_pos = motion->x.w.i - 0x20;

                    motion->unk_0C = (tile_pos - current_pos) << 15;
                }
                {
                    s32 tile_pos = entity->unk_25 << 6;
                    s32 current_pos = motion->y.w.i - 0x20;

                    motion->unk_10 = (tile_pos - current_pos) << 15;
                }
            } else {
                motion->unk_0C = 0;
                motion->unk_10 = 0;
            }
        }

        if (controller->unk_96.s != 0) {
            return;
        }
        if (((EntityRec *)source)->unk_28 == 0) {
            motion->flags14 = 0;
            begin_actor_display_action(controller, motion, entity, ((s32 *)D_80173CC4));
            return;
        }
        controller->unk_96.s = 8;
        controller->unk_9B++;
        return;

    case 2:
        if (controller->unk_96.s != 0) {
            {
                s32 tile_pos = entity->unk_24 << 6;
                s32 current_pos = motion->x.w.i - 0x20;

                motion->unk_0C = (tile_pos - current_pos) << 16;
            }
            {
                s32 tile_pos = entity->unk_25 << 6;
                s32 current_pos = motion->y.w.i - 0x20;

                motion->unk_10 = (tile_pos - current_pos) << 16;
            }
        }

        timer = controller->unk_96.u - 1;
        controller->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, entity->unk_24,
                      entity->unk_25);

        tracked_object = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_object == (s32)((u8 *)source - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_object & 0x7FFFFFFF;
        }
        controller->unk_8C = ((void *)func_80170E54);
        return;

    default:
        return;
    }
}

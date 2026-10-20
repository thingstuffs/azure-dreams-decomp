#include "modules/dungeon_resource12_slot0.h"
#include "shared/sprite_frame_state.h"

void func_80172FE8(R12_80172FE8_S_801730B8_1 *action, EntityRec *motion, SpriteFrameState *entity, void *source)
{
    s16 timer;
    s32 direction;
    s32 tracked_addr;

    direction = (((EntityRec *)source)->unk_6A >> 9) & 7;
    switch (action->unk_9B) {
    case 0:
        apply_clamped_actor_value_delta(source);
        motion->unk_0C =
            *(s16 *)((u8 *)((s8 *)dir_step_x) + (direction * 2)) << 18;
        motion->unk_10 =
            *(s16 *)((u8 *)((s8 *)dir_step_y) + (direction * 2)) << 18;
        action->unk_9B++;

        if (((EntityRec *)source)->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            begin_actor_display_action(action, motion, entity, ((s32 *)D_80175A94));
            return;
        }
        if (entity->flags & 0x8000) {
            action->unk_96.s = 0;
            action->unk_9B = 2;
            return;
        }
        if (((EntityRec *)source)->flags1C & 0x228) {
            timer = 8;
        } else {
            timer = -1;
        }
        action->unk_96.s = timer;
        motion->unk_0C -= motion->unk_0C / 4;
        motion->unk_10 -= motion->unk_10 / 4;
                        /* fall through */

    case 1:
        motion->unk_0C -=
            *(s16 *)((u8 *)((s8 *)dir_step_x) + (direction * 2)) << 14;
        motion->unk_10 -=
            *(s16 *)((u8 *)((s8 *)dir_step_y) + (direction * 2)) << 14;
        if (action->unk_96.s > 0) {
            action->unk_96.s = action->unk_96.u - 1;
        } else if (entity->flags & 0x6000) {
            action->unk_96.s = 0;
        }
        if (action->unk_96.s != 0) {
            return;
        }
        if (((EntityRec *)source)->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            begin_actor_display_action(action, motion, entity, ((s32 *)D_80175A94));
            return;
        } else {
            action->unk_96.s = 8;
            action->unk_9B++;
        }
        return;

    case 2:
        if (action->unk_96.s != 0) {
            {
                s32 target_x = entity->unk_24 << 6;
                s32 current_x = motion->x.w.i - 0x20;

                motion->unk_0C = ((target_x - current_x) << 15) >> 1;
            }
            {
                s32 target_y = entity->unk_25 << 6;
                s32 current_y = motion->y.w.i - 0x20;

                motion->unk_10 = ((target_y - current_y) << 15) >> 1;
            }
        }
        timer = action->unk_96.u - 1;
        action->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, entity->unk_24, entity->unk_25);

        tracked_addr = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_addr == (s32)((u8 *)source - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_addr & 0x7FFFFFFF;
        }
        action->unk_8C = ((void *)update_actor_state_and_select_target);
        return;

    default:
        return;
    }
}

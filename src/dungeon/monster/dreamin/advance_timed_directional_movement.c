#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/monster/dreamin.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "engine/graphics.h"

typedef struct S_80172D24_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172D24_1;   /* arg0 in advance_timed_directional_movement */

extern void set_record_integer_tile_center();
extern void begin_actor_display_action();
extern void apply_clamped_actor_value_delta();

extern u8 dreamin_action_continuation_address;
extern u8 dreamin_frame_set_1[];

/* Updates timed directional movement and settles the entity at its grid position. */
void advance_timed_directional_movement(void *action, void *motion, SpriteFrameState *sprite, void *entity)
{
    s16 *direction_y;
    s16 *direction_x_table;
    s16 frames_left;
    s16 timer_or_state;
    s16 duration;
    s32 decel_offset;
    s32 velocity_y;
    s32 direction;
    s32 launch_offset;
    s32 velocity_x;
    s32 rounded_velocity_x;
    s32 rounded_velocity_y;
    s32 target_x;
    s32 position_x;
    s32 target_y;
    s32 position_y;
    s32 tracked_entity;
    u8 state;

    direction = (((EntityRec *)entity)->unk_6A >> 9) & 7;
    state = ((S_80172D24_1 *)action)->unk_9B;

    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        if (((EntityRec *)entity)->unk_28 == 0) {
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            begin_actor_display_action(action, motion, sprite, dreamin_frame_set_1);
            return;
        }
        if (sprite->flags & 0x8000) {
            ((S_80172D24_1 *)action)->unk_96.s = 0;
            ((S_80172D24_1 *)action)->unk_9B = 3;
            return;
        }
        ((S_80172D24_1 *)action)->unk_96.s = 12;
        ((S_80172D24_1 *)action)->unk_9B++;
    case 1:
        timer_or_state = ((S_80172D24_1 *)action)->unk_96.s - 1;
        ((S_80172D24_1 *)action)->unk_96.s = timer_or_state;
        if ((timer_or_state << 16) != 0) {
            return;
        }

        sprite->frameTable = dreamin_frame_set_1;
        select_sprite_entry(sprite,
            dreamin_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
            0);

        direction_x_table = (s16 *)((s8 *)dir_step_x);
        launch_offset = direction * 2;
        ((EntityRec *)motion)->unk_0C =
            *(s16 *)((u8 *)direction_x_table + launch_offset) << 19;
        ((EntityRec *)motion)->unk_10 =
            *(s16 *)((u8 *)((s8 *)dir_step_y) + launch_offset) << 19;

        duration = -1;
        if (((EntityRec *)entity)->flags1C & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            duration = 8;
        }
        ((S_80172D24_1 *)action)->unk_96.s = duration;

        velocity_x = ((EntityRec *)motion)->unk_0C;
        rounded_velocity_x = velocity_x;
        if (velocity_x < 0) {
            rounded_velocity_x = velocity_x + 3;
        }
        velocity_y = ((EntityRec *)motion)->unk_10;
        ((EntityRec *)motion)->unk_0C = velocity_x - (rounded_velocity_x >> 2);
        rounded_velocity_y = velocity_y;
        ((EntityRec *)motion)->unk_10 = velocity_y - (rounded_velocity_y / 4);
        timer_or_state = ((S_80172D24_1 *)action)->unk_9B + 1;
        ((S_80172D24_1 *)action)->unk_9B = timer_or_state;
        return;
    case 2:
        direction_x_table = (s16 *)((s8 *)dir_step_x);
        decel_offset = direction * 2;
        direction_y = (s16 *)((u8 *)((s8 *)dir_step_y) + decel_offset);
        ((EntityRec *)motion)->unk_0C -=
            *(s16 *)((u8 *)direction_x_table + decel_offset) << 16;
        ((EntityRec *)motion)->unk_10 -= *direction_y << 16;

        if (((S_80172D24_1 *)action)->unk_96.u > 0) {
            ((S_80172D24_1 *)action)->unk_96.s--;
        } else if (sprite->flags & 0x6000) {
            ((S_80172D24_1 *)action)->unk_96.s = 0;
        }
        if (((S_80172D24_1 *)action)->unk_96.u != 0) {
            return;
        }
        if (((EntityRec *)entity)->unk_28 == 0) {
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            begin_actor_display_action(action, motion, sprite, dreamin_frame_set_1);
        } else {
            duration = 8;
            timer_or_state = ((S_80172D24_1 *)action)->unk_9B + 1;
            ((S_80172D24_1 *)action)->unk_96.s = duration;
            ((S_80172D24_1 *)action)->unk_9B = timer_or_state;
        }
        return;
    case 3:
        frames_left = ((S_80172D24_1 *)action)->unk_96.u;
        if (frames_left != 0) {
            target_x = sprite->tile_x << 6;
            position_x = ((EntityRec *)motion)->x.w.i - 0x20;
            ((EntityRec *)motion)->unk_0C = ((target_x - position_x) << 15) / frames_left;

            target_y = sprite->tile_y << 6;
            position_y = ((EntityRec *)motion)->y.w.i - 0x20;
            ((EntityRec *)motion)->unk_10 =
                ((target_y - position_y) << 15) / ((S_80172D24_1 *)action)->unk_96.u;
        }

        timer_or_state = ((S_80172D24_1 *)action)->unk_96.s - 1;
        ((S_80172D24_1 *)action)->unk_96.s = timer_or_state;
        if ((timer_or_state << 16) > 0) {
            return;
        }

        ((EntityRec *)motion)->flags14 = 0;
        ((EntityRec *)motion)->unk_10 = 0;
        ((EntityRec *)motion)->unk_0C = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);

        tracked_entity = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_entity & 0x7FFFFFFF;
        }
        ((S_80172D24_1 *)action)->unk_8C = &dreamin_action_continuation_address;
        break;
    default:
        return;
    }
}

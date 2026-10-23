#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

typedef struct S_func_81325A04_0 {
    u8 pad_00[0x8C];
    void *unk_8C;
    u8 pad_90[0x06];
    union {
        s16 s;
        u16 u;
    } unk_96;
    u8 pad_98[0x03];
    u8 unk_9B;
    u8 pad_9C[0x17];
    u8 unk_B3;
    u8 unk_B4;
} S_func_81325A04_0;

typedef struct S_func_81325A04_1 {
    u8 pad_00[0x02];
    s16 unk_02;
    u8 pad_04[0x02];
    s16 unk_06;
    u8 pad_08[0x04];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_func_81325A04_1;

typedef struct S_func_81325A04_3 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 pad_29[0x01];
    s16 unk_2A;
    u8 pad_2C[0x3E];
    u16 unk_6A;
} S_func_81325A04_3;

extern u8 ghosh_action_resume_address[];
extern u8 ghosh_frame_set_3[];
extern u8 ghosh_frame_set_4[];
#include "dungeon/monster/ghosh.h"
extern u8 D_801746CC[];

extern s32 set_record_integer_tile_center();
extern s32 begin_actor_display_action();
extern s32 apply_clamped_actor_value_delta();
extern s32 select_sprite_entry();

/* Updates timed movement, returns the entity to its tile, and restores its animation. */
/* Applies Ghosh's pending HP change, animates damped recoil, then recenters it and updates its action
 * state. */
void update_timed_movement_and_restore_animation(S_func_81325A04_0 *action, S_func_81325A04_1 *motion, SpriteFrameState *entity,
    S_func_81325A04_3 *actor) {
    s32 state;
    s16 timer;
    s16 next_timer;
    u16 timer_bits;
    s32 facing;
    s32 anim_addr;
    s32 timer_ending;
    s32 velocity_x;
    s32 velocity_y;
    s32 tile_x;
    s32 offset_x;
    s32 tile_y;
    s32 offset_y;
    u8 *final_state;
    s32 state_bits;
    u16 saved_timer;
    s32 shifted_timer;
    u8 *anim_table;

    state = action->unk_9B;
    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(actor);
        action->unk_96.s = 12;
        action->unk_9B = (u8)(action->unk_9B + 1);
        if (actor->unk_28 == 0) {
            motion->unk_14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            if (action->unk_B4 != 0) {
                action->unk_9B = 0;
                action->unk_8C = ghosh_action_resume_address;
                return;
            }
            action->unk_9B = 0;
            begin_actor_display_action(action, motion, entity, D_801746CC);
            return;
        }
        final_state = (u8 *)3;
        if (!(entity->flags & 0x8000)) {
            return;
        }
        action->unk_96.s = 0;
        action->unk_9B = (u32)final_state;
        return;

    case 1:
        timer_bits = action->unk_96.u;
        timer_bits--;
        action->unk_96.u = timer_bits;
        timer = (s16)timer_bits;
        if (timer >= 11) {
            motion->unk_0C =
            *(s16 *)((u8 *)dir_step_x + ((actor->unk_6A >> 8) & 0xE)) << 20;
            motion->unk_10 =
            *(s16 *)((u8 *)dir_step_y + ((actor->unk_6A >> 8) & 0xE)) << 20;
            entity->flags |= 0x800;
            return;
        }
        if (timer >= 7) {
            velocity_x = motion->unk_0C;
            if (velocity_x < 0) {
                velocity_x += 3;
            }
            velocity_y = motion->unk_10;
            motion->unk_0C = velocity_x >> 2;
            motion->unk_10 = (velocity_y / 4);
            return;
        }
        timer_ending = timer < 2;
        if (!timer_ending) {
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            return;
        }
        if (timer == state) {
            entity->flags &= 0xF7FF;
            return;
        }
        if (timer != 0) {
            return;
        }
        timer = 4;
        state_bits = action->unk_9B;
        action->unk_96.s = timer;
        action->unk_9B = (u8)(state_bits + 1);
        return;
    case 2:
        timer = action->unk_96.s;
        if (timer != 0) {
            tile_x = entity->tile_x << 6;
            offset_x = motion->unk_02 - 32;
            motion->unk_0C = ((tile_x - offset_x) << 16) / timer;
            tile_y = entity->tile_y << 6;
            offset_y = motion->unk_06 - 32;
            motion->unk_10 =
            ((tile_y - offset_y) << 16) / action->unk_96.s;
        }
        saved_timer = action->unk_96.u;
        next_timer = (s16)(saved_timer - 1);
        shifted_timer = (s32)saved_timer << 16;
        action->unk_96.s = next_timer;
        if (shifted_timer > 0) {
            return;
        }
        motion->unk_14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        state_bits = action->unk_9B;
        action->unk_9B = (u8)(state_bits + 1);
        return;

    case 3:
        motion->unk_14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, entity->tile_x, entity->tile_y);
        if (actor->unk_28 == 0) {
            motion->unk_14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            if (action->unk_B4 == 0) {
                action->unk_9B = 0;
                begin_actor_display_action(action, motion, entity, D_801746CC);
                return;
            } else {
                u8 *result_bits = ghosh_action_resume_address;
                action->unk_9B = 0;
                action->unk_8C = result_bits;
                return;
            }
        }
        anim_addr = *(s32 *)&entity->frameTable;
        if (anim_addr == (s32)ghosh_ready_action_frames) {
            if (action->unk_B3 == 0) {
                anim_table = ghosh_frame_set_3;
            } else {
                anim_table = ghosh_frame_set_4;
            }
            if (anim_addr != (s32)anim_table) {
                entity->frameTable = (s32)anim_table;
                facing = g_game_work.view.camera_rotation.parts.viewAngle + actor->unk_2A;
                select_sprite_entry(entity, *(u8 *)((u32)(((facing + 0x100) >> 9) & 7) + (u32)anim_table), 0);
            }
        }
        if (((s32)g_dungeon_status.pending_display_owner) == (s32)((u8 *)actor - 0x20)) {
            *(s32 *)&g_dungeon_status.pending_display_owner &= 0x7FFFFFFF;
        }
        action->unk_8C = ghosh_action_resume_address;
        return;
    }
}

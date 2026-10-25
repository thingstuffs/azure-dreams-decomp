#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/monster/barong.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80154B4C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   /* accessed as both */
    u8 pad_A0[0x4];
    s32 unk_A4;
} S_80154B4C_0;   /* arg0 in update_actor_movement_animation_states_completes_timed_action */

extern void select_sprite_entry(void *, s32, s32);
extern s32 rsin(s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void advance_status_timers(void *);
extern void on_actor_status_updated(void *);
extern void spend_actor_mp(void *, s32);


extern u8 D_801536F4[];
extern u8 D_80157554[];
extern u8 D_80157574[];
extern u8 D_8015757C[];

/* Updates actor movement and animation states and completes the timed action. */
void update_actor_movement_animation_states_completes_timed_action(void *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    s32 state;
    s32 move_frames;
    s32 target_x;
    s32 world_x;
    s32 height;
    s32 height_offset;
    s32 world_y;
    s32 move_count;
    s32 action_timer;
    s32 actor_flags;
    u16 facing_aux;
    DungeonGlobalStatus *dungeon_state;
    u8 *idle_anims;

    state = ((S_80154B4C_0 *)action)->unk_9B;
    switch (state) {
    case 0:
    {
        u8 *state_anims;

        if (!(sprite->flags & 0x6000)) {
            break;
        }
        state_anims = D_80157574;
        sprite->frameTable = state_anims;
        select_sprite_entry(sprite,
            state_anims[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        sprite->scale_y = 0x1000;
        ((S_80154B4C_0 *)action)->unk_98 |= 8;
        actor->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        ((S_80154B4C_0 *)action)->unk_9E.s = 5;
        ((S_80154B4C_0 *)action)->unk_A4 = 0;
        ((S_80154B4C_0 *)action)->unk_9B++;
    }
                        /* fall through */
    case 1:
        move_frames = ((S_80154B4C_0 *)action)->unk_9E.s;
        ((S_80154B4C_0 *)action)->unk_90 -= ((S_80154B4C_0 *)action)->unk_A4;
        if (move_frames != 0) {
            target_x = sprite->tile_x;
            world_x = motion->x.w.i;
            target_x <<= 6;
            world_x -= 0x20;
            motion->velocity_x = ((target_x - world_x) << 16) / move_frames;

            world_y = motion->y.w.i;
            world_y -= 0x20;
            motion->velocity_y =
                (((sprite->tile_y << 6) - world_y) << 16) /
                ((S_80154B4C_0 *)action)->unk_9E.s;

            ((S_80154B4C_0 *)action)->unk_A4 =
                (-rsin(((S_80154B4C_0 *)action)->unk_9E.s * 0x199)) << 10;
        }

        height = ((S_80154B4C_0 *)action)->unk_90;
        height_offset = ((S_80154B4C_0 *)action)->unk_A4;
        move_count = ((S_80154B4C_0 *)action)->unk_9E.u;
        height += height_offset;
        move_count -= 1;
        ((S_80154B4C_0 *)action)->unk_9E.u = move_count;
        ((S_80154B4C_0 *)action)->unk_90 = height;
        if ((move_count << 16) < 0) {
            ((S_80154B4C_0 *)action)->unk_90 = 0;
            ((S_80154B4C_0 *)action)->unk_98 &= 0xFFF7;
            actor->flags1C |= ACTOR_GROUNDED;
            ((S_80154B4C_0 *)action)->unk_9B++;
        }
                        /* fall through */
    case 2:
    {
        u8 *state_anims;

        if (actor->flags1C & ACTOR_GROUNDED) {
            ((S_80154B4C_0 *)action)->unk_98 &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            state_anims = D_8015757C;
            sprite->frameTable = state_anims;
            select_sprite_entry(sprite,
                state_anims[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            sprite->scale_y = 0xC00;
            ((S_80154B4C_0 *)action)->unk_9B++;
        }
    }
        break;
    case 3:
        idle_anims = D_80157554;
        if (*(u8 * *)&sprite->frameTable != idle_anims) {
            sprite->frameTable = idle_anims;
            select_sprite_entry(sprite,
                idle_anims[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            sprite->scale_y = 0x1000;
        }
        break;
    default:
        break;
    }

    action_timer = ((S_80154B4C_0 *)action)->unk_96 - 1;
    ((S_80154B4C_0 *)action)->unk_96 = action_timer;
    if ((action_timer << 16) > 0) {
        return;
    }

    motion->velocity_z = 0;
    motion->velocity_y = 0;
    motion->velocity_x = 0;
    sprite->scale_y = 0x1000;
    set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
    spend_actor_mp(actor, 3);
    advance_status_timers(actor);

    dungeon_state = &g_dungeon_status;
    if (dungeon_state->activity_counts.parts.pending_movement_count != 0) {
        (*(u16 *)&dungeon_state->activity_counts.parts.pending_movement_count)--;
    }

    actor_flags = actor->flags1C;
    if (actor_flags & 0x2000) {
        if (actor->action_flags & ACTOR_ACTION_PENDING) {
            actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            actor->facing = get_rounded_facing_and_rounding_flag(
                sprite->tile_x,
                sprite->tile_y,
                reference_tile_object.tile_position.parts.tile_x,
                reference_tile_object.tile_position.parts.tile_y,
                &facing_aux);
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        ((S_80154B4C_0 *)action)->unk_8C = D_801536F4;
        on_actor_status_updated(actor);
    }
}

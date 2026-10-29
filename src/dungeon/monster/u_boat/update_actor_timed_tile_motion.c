#include "common.h"
#include "dungeon/actor.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "engine/graphics.h"

typedef struct S_801730C4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
    s16 unk_A8;
    u8 pad_AA[0x6];
    u8 unk_B0;
} S_801730C4_0;   /* arg0 in update_actor_timed_tile_motion */

typedef struct S_801730C4_2 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801730C4_2;   /* arg3 in update_actor_timed_tile_motion */


extern s32 rsin(s32);

void create_owner_linked_directional_object(ActorRecord *owner_data, ObjectPosition *source_position, SpriteFrameState *source_sprite);

extern u8 uboat_default_frames[];
extern u8 uboat_timed_motion_frames[];
extern u8 uboat_timed_motion_frames_alt[];
#include "dungeon/monster/u_boat.h"
#include "dungeon/item.h"

/* Updates timed actor movement, landing animations, and the next action. */
void update_actor_timed_tile_motion(void *action, ObjectPosition *motion, SpriteFrameState *sprite, void *actor)
{
    u16 target_distance;
    s32 phase;

    phase = ((S_801730C4_0 *)action)->unk_9B;
    switch (phase) {
    case 0:
        if (!(sprite->flags & 0x6000)) {
            break;
        }
        {
            u8 *anim_table = uboat_timed_motion_frames;

            sprite->frameTable = anim_table;
            select_sprite_entry(sprite,
                anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801730C4_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                1);
        }
        ((S_801730C4_0 *)action)->unk_98 |= 8;
        ((S_801730C4_2 *)actor)->unk_1C.s &= 0xF7FFFFFF;
        ((S_801730C4_0 *)action)->unk_A8 = 5;
        ((S_801730C4_0 *)action)->unk_A4 = 0;
        ((S_801730C4_0 *)action)->unk_9B++;
                        /* fallthrough */
    case 1:
    {
        s32 move_ticks;
        s16 next_move_ticks;

        move_ticks = ((S_801730C4_0 *)action)->unk_A8;
        ((S_801730C4_0 *)action)->unk_90.at00.v -= ((S_801730C4_0 *)action)->unk_A4;
        if (move_ticks != 0) {
            s32 tile_delta;
            s32 axis_pos;

            tile_delta = sprite->tile_x << 6;
            axis_pos = motion->x.w.i;
            axis_pos -= 0x20;
            tile_delta -= axis_pos;
            motion->velocity_x = (tile_delta << 16) / move_ticks;

            axis_pos = motion->y.w.i;
            tile_delta = sprite->tile_y << 6;
            axis_pos -= 0x20;
            tile_delta -= axis_pos;
            motion->velocity_y =
                (tile_delta << 16) / ((S_801730C4_0 *)action)->unk_A8;
            ((S_801730C4_0 *)action)->unk_A4 =
                -rsin(((S_801730C4_0 *)action)->unk_A8 * 0x199) << 9;
        }

        ((S_801730C4_0 *)action)->unk_90.at00.v += ((S_801730C4_0 *)action)->unk_A4;
        next_move_ticks = (u16)((S_801730C4_0 *)action)->unk_A8 - 1;
        ((S_801730C4_0 *)action)->unk_A8 = next_move_ticks;
        if (next_move_ticks < 0) {
            ((S_801730C4_0 *)action)->unk_90.at02.v = -0x10;
            ((S_801730C4_0 *)action)->unk_98 &= 0xFFF7;
            ((S_801730C4_2 *)actor)->unk_1C.s |= 0x08000000;
            ((S_801730C4_0 *)action)->unk_9B++;
        }
    }
                        /* fallthrough */
    case 2:
        if (((S_801730C4_2 *)actor)->unk_1C.s & 0x08000000) {
            ((S_801730C4_0 *)action)->unk_98 &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            {
                u8 *anim_table = uboat_timed_motion_frames_alt;

                sprite->frameTable = anim_table;
                select_sprite_entry(sprite,
                    anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801730C4_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                    0);
            }
            ((S_801730C4_0 *)action)->unk_9B++;
        }
        break;
    case 3:
    {
        u8 *anim_table = uboat_default_frames;

        if (*(u8 * *)&sprite->frameTable != anim_table) {
            sprite->frameTable = anim_table;
            select_sprite_entry(sprite,
                anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801730C4_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            if (((S_801730C4_0 *)action)->unk_B0 == 0) {
                create_owner_linked_directional_object(action, motion, sprite);
            }
        }
    }
        break;
    }

    {
        u16 action_ticks;

        action_ticks = ((S_801730C4_0 *)action)->unk_96 - 1;
        ((S_801730C4_0 *)action)->unk_96 = action_ticks;
        if ((action_ticks << 16) > 0) {
            return;
        }
    }

    motion->velocity_z = 0;
    motion->velocity_y = 0;
    motion->velocity_x = 0;
    set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
    spend_actor_mp(actor, 0x10);
    advance_status_timers(actor);
    {

        if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
            g_dungeon_status.activity_counts.parts.pending_movement_count = (u16)g_dungeon_status.activity_counts.parts.pending_movement_count - 1;
        }
    }
    {
        s32 actor_flags = ((S_801730C4_2 *)actor)->unk_1C.u;

        if (actor_flags & 0x2000) {
            if (((S_801730C4_2 *)actor)->unk_46 & 0x8000) {
                ((S_801730C4_2 *)actor)->unk_46 &= 0x7FFF;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                ((S_801730C4_2 *)actor)->unk_2A = get_rounded_facing_and_rounding_flag(
                    sprite->tile_x, sprite->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &target_distance);
            }
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) <= 0) {
        return;
    }
    ((S_801730C4_0 *)action)->unk_8C = uboat_behavior_entry;
    on_actor_status_updated(actor);
}

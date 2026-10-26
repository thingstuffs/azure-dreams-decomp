#include "common.h"
#include "dungeon/actor.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"

typedef struct S_801610E0_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { u16 s; s16 u; } unk_9E;   /* accessed as both */
    s32 unk_A0;
} S_801610E0_0;   /* arg0 in move_actor_to_tile_with_hop */

typedef struct S_801610E0_1 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801610E0_1;   /* arg3 in move_actor_to_tile_with_hop */

extern void select_sprite_entry(void *, s32, s32);
extern s32 rsin(s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void on_actor_status_updated(void *);
extern void spend_actor_mp(void *, s32);


extern s32 D_8015FCE8;
extern u8 D_80162EB8[];
extern u8 D_80162ED0[];
extern u8 weadog_frame_set_6[];

/* Moves an actor to its tile with a timed hop, updates animation, and completes the action. */
void move_actor_to_tile_with_hop(void *action, void *motion, void *sprite, void *actor)
{
    u16 direction_aux;
    s32 state;
    s32 move_ticks;
    s32 actor_flags;
    s32 target_x;
    s32 pos_x;
    s32 pos_y;
    s16 phase_ticks;
    u16 action_ticks;
    u8 *anim_table;

    state = ((S_801610E0_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        phase_ticks = ((S_801610E0_0 *)action)->unk_9E.s - 1;
        ((S_801610E0_0 *)action)->unk_9E.s = phase_ticks;
        if ((phase_ticks << 16) != 0) {
            break;
        }

        ((SpriteFrameState *)sprite)->frameTable = D_80162ED0;
        select_sprite_entry(
            sprite,
            D_80162ED0[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801610E0_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801610E0_0 *)action)->unk_98 |= 8;
        ((S_801610E0_1 *)actor)->unk_1C.s &= 0xF7FFFFFF;
        ((S_801610E0_0 *)action)->unk_9E.u = 5;
        ((S_801610E0_0 *)action)->unk_A0 = 0;
        ((S_801610E0_0 *)action)->unk_9B++;

    case 1:
        move_ticks = ((S_801610E0_0 *)action)->unk_9E.u;
        ((S_801610E0_0 *)action)->unk_90 -= ((S_801610E0_0 *)action)->unk_A0;
        if (move_ticks != 0) {
            target_x = ((SpriteFrameState *)sprite)->tile_x;
            pos_x = ((ObjectPosition *)motion)->x.w.i;
            target_x <<= 6;
            pos_x -= 0x20;
            ((ObjectPosition *)motion)->velocity_x = ((target_x - pos_x) << 16) / move_ticks;

            pos_y = ((ObjectPosition *)motion)->y.w.i;
            pos_y -= 0x20;
            ((ObjectPosition *)motion)->velocity_y =
                (((((SpriteFrameState *)sprite)->tile_y << 6) - pos_y) << 16) /
                ((S_801610E0_0 *)action)->unk_9E.u;
            ((S_801610E0_0 *)action)->unk_A0 =
                (-rsin(((S_801610E0_0 *)action)->unk_9E.u * 0x199)) << 10;
        }

        ((S_801610E0_0 *)action)->unk_90 += ((S_801610E0_0 *)action)->unk_A0;
        phase_ticks = ((S_801610E0_0 *)action)->unk_9E.s - 1;
        ((S_801610E0_0 *)action)->unk_9E.s = phase_ticks;
        if (phase_ticks < 0) {
            ((S_801610E0_0 *)action)->unk_90 = 0;
            ((S_801610E0_0 *)action)->unk_98 &= 0xFFF7;
            ((S_801610E0_1 *)actor)->unk_1C.s |= 0x08000000;
            ((S_801610E0_0 *)action)->unk_9B++;
        }

    case 2:
        if (((S_801610E0_1 *)actor)->unk_1C.s & 0x08000000) {
            ((S_801610E0_0 *)action)->unk_98 &= 0xFFF7;
            ((ObjectPosition *)motion)->velocity_z = 0;
            ((ObjectPosition *)motion)->velocity_y = 0;
            ((ObjectPosition *)motion)->velocity_x = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->tile_x, ((SpriteFrameState *)sprite)->tile_y);

            ((SpriteFrameState *)sprite)->frameTable = weadog_frame_set_6;
            select_sprite_entry(
                sprite,
                weadog_frame_set_6[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801610E0_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_801610E0_0 *)action)->unk_9B++;
        }
        break;

    case 3:
        anim_table = D_80162EB8;
        if (*(u8 * *)&((SpriteFrameState *)sprite)->frameTable != anim_table) {
            ((SpriteFrameState *)sprite)->frameTable = anim_table;
            select_sprite_entry(
                sprite,
                anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801610E0_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
        }

    default:
        break;
    }

    action_ticks = ((S_801610E0_0 *)action)->unk_96 - 1;
    ((S_801610E0_0 *)action)->unk_96 = action_ticks;
    if ((s16)action_ticks > 0) {
        return;
    }

    ((ObjectPosition *)motion)->velocity_z = 0;
    ((ObjectPosition *)motion)->velocity_y = 0;
    ((ObjectPosition *)motion)->velocity_x = 0;
    set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->tile_x, ((SpriteFrameState *)sprite)->tile_y);
    spend_actor_mp(actor, 4);
    advance_status_timers(actor);

    if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
        g_dungeon_status.activity_counts.parts.pending_movement_count--;
    }

    actor_flags = ((S_801610E0_1 *)actor)->unk_1C.u;
    if (actor_flags & 0x2000) {
        if (((S_801610E0_1 *)actor)->unk_46 & 0x8000) {
            ((S_801610E0_1 *)actor)->unk_46 &= 0x7FFF;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            ((S_801610E0_1 *)actor)->unk_2A = get_rounded_facing_and_rounding_flag(
                ((SpriteFrameState *)sprite)->tile_x, ((SpriteFrameState *)sprite)->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &direction_aux);
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        ((S_801610E0_0 *)action)->unk_8C = &D_8015FCE8;
        on_actor_status_updated(actor);
    }
}

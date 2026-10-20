#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80172158_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    s32 unk_A0;
} S_80172158_0;   /* arg0 in move_actor_with_vertical_arc */

extern void select_sprite_entry(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void advance_status_timers(void *);
extern void on_actor_status_updated(void *);
extern void reduce_actor_food_meter(void *, s32);
extern s32 check_actor_floor_trap(void *, void *);

extern u8 D_80170E9C[];
extern u8 D_80174EE0[];

/* Moves the actor to its tile with a vertical arc and completes the timed action. */
void move_actor_with_vertical_arc(void *action, EntityRec *motion, void *sprite, EntityRec *actor)
{
    s32 facing_aux;
    s32 move_ticks;
    s32 x_delta;
    s32 axis_pos;
    s32 position;
    s16 next_move_ticks;
    s32 actor_flags;
    u16 action_ticks;
    s32 phase;
    DungeonGlobalStatus *counter_base;

    phase = ((S_80172158_0 *)action)->unk_9B;
    switch (phase) {
    case 0:
        if (!((((SpriteFrameState *)sprite)->unk_04 == 1 &&
               (((SpriteFrameState *)sprite)->flags & 0x1000)) ||
              (((SpriteFrameState *)sprite)->flags & 0xE000))) {
            break;
        }
        ((S_80172158_0 *)action)->unk_98 |= 8;
        (*(u32 *)&actor->flags1C) &= 0xF7FFFFFF;
        ((S_80172158_0 *)action)->unk_9E = 6;
        ((S_80172158_0 *)action)->unk_A0 = 0;
        ((S_80172158_0 *)action)->unk_9B++;
                        /* fall through */
    case 1:
        move_ticks = ((S_80172158_0 *)action)->unk_9E;
        ((S_80172158_0 *)action)->unk_90 =
            ((S_80172158_0 *)action)->unk_90 - ((S_80172158_0 *)action)->unk_A0;
        if (move_ticks != 0) {
            x_delta = ((SpriteFrameState *)sprite)->unk_24;
            axis_pos = motion->x.w.i;
            x_delta <<= 6;
            axis_pos -= 0x20;
            x_delta -= axis_pos;
            x_delta <<= 16;
            motion->unk_0C = x_delta / move_ticks;
            axis_pos = motion->y.w.i - 0x20;
            motion->unk_10 =
                (((((SpriteFrameState *)sprite)->unk_25 << 6) - axis_pos) << 16) /
                (s16)((S_80172158_0 *)action)->unk_9E;
            ((S_80172158_0 *)action)->unk_A0 =
                (-func_800644B8(((S_80172158_0 *)action)->unk_9E * 0x155)) << 9;
        }
        ((S_80172158_0 *)action)->unk_90 += ((S_80172158_0 *)action)->unk_A0;
        next_move_ticks = --((S_80172158_0 *)action)->unk_9E;
        if (next_move_ticks < 0) {
            ((S_80172158_0 *)action)->unk_90 = 0;
            ((S_80172158_0 *)action)->unk_98 &= 0xFFF7;
            (*(u32 *)&actor->flags1C) |= 0x08000000;
            ((S_80172158_0 *)action)->unk_9B++;
        }

                        /* fall through */
    case 2:
        if (((u32)actor->flags1C) & 0x08000000) {
            ((S_80172158_0 *)action)->unk_98 &= 0xFFF7;
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
            ((SpriteFrameState *)sprite)->frameTable = D_80174EE0;
            select_sprite_entry(
                sprite,
                D_80174EE0[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_80172158_0 *)action)->unk_9B++;
        }

        break;
    default:
        break;
    }
    action_ticks = ((S_80172158_0 *)action)->unk_96 - 1;
    ((S_80172158_0 *)action)->unk_96 = action_ticks;
    if ((action_ticks << 16) <= 0) {
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
        reduce_actor_food_meter(actor, 3);
        advance_status_timers(actor);

        counter_base = &g_dungeon_status;
        if (counter_base->unk_08 != 0) {
            (*(u16 *)&counter_base->unk_08)--;
        }

        actor_flags = actor->flags1C;
        if (actor_flags & 0x2000) {
            if (actor->unk_46 & 0x8000) {
                actor->unk_46 &= 0x7FFF;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                actor->facing = get_rounded_facing_and_rounding_flag(
                    ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25,
                    D_80082E80.tileX, D_80082E80.tileY, &facing_aux);
            }
        }
        if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
            ((S_80172158_0 *)action)->unk_8C = D_80170E9C;
            on_actor_status_updated(actor);
        }
    }
}

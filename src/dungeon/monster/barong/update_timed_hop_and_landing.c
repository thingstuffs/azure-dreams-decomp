#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_8016CB4C_0 {
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
} S_8016CB4C_0;   /* arg0 in update_timed_hop_and_landing */

extern void select_sprite_entry(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void advance_status_timers(void *);
extern void on_actor_status_updated(void *);
extern void reduce_actor_food_meter(void *, s32);
extern s32 check_actor_floor_trap(void *, void *);

extern u8 D_8016B6F4[];
extern u8 D_8016F554[];
extern u8 D_8016F574[];
extern u8 D_8016F57C[];

/* Updates a timed hop toward a tile and handles landing and completion. */
void update_timed_hop_and_landing(void *action, void *motion, void *sprite, void *actor)
{
    s32 state;
    s32 move_ticks;
    s32 target_x;
    s32 pos_x;
    s32 height_offset;
    s32 arc_offset;
    s32 pos_y;
    s32 next_move_ticks;
    s32 action_ticks;
    s32 actor_flags;
    s32 facing_aux;
    DungeonGlobalStatus *global_base;
    u8 *idle_anims;

    state = ((S_8016CB4C_0 *)action)->unk_9B;
    switch (state) {
    case 0:
    {
        u8 *phase_anims;

        if (!(((SpriteFrameState *)sprite)->flags & 0x6000)) {
            break;
        }
        phase_anims = D_8016F574;
        ((SpriteFrameState *)sprite)->frameTable = phase_anims;
        select_sprite_entry(sprite,
            phase_anims[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);
        ((SpriteFrameState *)sprite)->scale_y = 0x1000;
        ((S_8016CB4C_0 *)action)->unk_98 |= 8;
        ((EntityRec *)actor)->flags1C &= 0xF7FFFFFF;
        ((S_8016CB4C_0 *)action)->unk_9E.s = 5;
        ((S_8016CB4C_0 *)action)->unk_A4 = 0;
        ((S_8016CB4C_0 *)action)->unk_9B++;
    }
    case 1:
        move_ticks = ((S_8016CB4C_0 *)action)->unk_9E.s;
        ((S_8016CB4C_0 *)action)->unk_90 -= ((S_8016CB4C_0 *)action)->unk_A4;
        if (move_ticks != 0) {
            target_x = ((SpriteFrameState *)sprite)->unk_24;
            pos_x = ((EntityRec *)motion)->x.w.i;
            target_x <<= 6;
            pos_x -= 0x20;
            ((EntityRec *)motion)->unk_0C = ((target_x - pos_x) << 16) / move_ticks;

            pos_y = ((EntityRec *)motion)->y.w.i;
            pos_y -= 0x20;
            ((EntityRec *)motion)->unk_10 =
                (((((SpriteFrameState *)sprite)->unk_25 << 6) - pos_y) << 16) /
                ((S_8016CB4C_0 *)action)->unk_9E.s;

            ((S_8016CB4C_0 *)action)->unk_A4 =
                (-func_800644B8(((S_8016CB4C_0 *)action)->unk_9E.s * 0x199)) << 10;
        }

        height_offset = ((S_8016CB4C_0 *)action)->unk_90;
        arc_offset = ((S_8016CB4C_0 *)action)->unk_A4;
        next_move_ticks = ((S_8016CB4C_0 *)action)->unk_9E.u;
        height_offset += arc_offset;
        next_move_ticks -= 1;
        ((S_8016CB4C_0 *)action)->unk_9E.u = next_move_ticks;
        ((S_8016CB4C_0 *)action)->unk_90 = height_offset;
        if ((next_move_ticks << 16) < 0) {
            ((S_8016CB4C_0 *)action)->unk_90 = 0;
            ((S_8016CB4C_0 *)action)->unk_98 &= 0xFFF7;
            ((EntityRec *)actor)->flags1C |= 0x08000000;
            ((S_8016CB4C_0 *)action)->unk_9B++;
        }
    case 2:
    {
        u8 *phase_anims;

        if (((EntityRec *)actor)->flags1C & 0x08000000) {
            ((S_8016CB4C_0 *)action)->unk_98 &= 0xFFF7;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
            phase_anims = D_8016F57C;
            ((SpriteFrameState *)sprite)->frameTable = phase_anims;
            select_sprite_entry(sprite,
                phase_anims[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
                0);
            ((SpriteFrameState *)sprite)->scale_y = 0xC00;
            ((S_8016CB4C_0 *)action)->unk_9B++;
        }
    }
        break;
    case 3:
        idle_anims = D_8016F554;
        if (*(u8 * *)&((SpriteFrameState *)sprite)->frameTable != idle_anims) {
            ((SpriteFrameState *)sprite)->frameTable = idle_anims;
            select_sprite_entry(sprite,
                idle_anims[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
                0);
            ((SpriteFrameState *)sprite)->scale_y = 0x1000;
        }
        break;
    }

    action_ticks = ((S_8016CB4C_0 *)action)->unk_96 - 1;
    ((S_8016CB4C_0 *)action)->unk_96 = action_ticks;
    if ((action_ticks << 16) > 0) {
        return;
    }

    ((EntityRec *)motion)->flags14 = 0;
    ((EntityRec *)motion)->unk_10 = 0;
    ((EntityRec *)motion)->unk_0C = 0;
    ((SpriteFrameState *)sprite)->scale_y = 0x1000;
    set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
    reduce_actor_food_meter(actor, 3);
    advance_status_timers(actor);

    global_base = &g_dungeon_status;
    if (global_base->activity_counts.parts.pending_movement_count != 0) {
        (*(u16 *)&global_base->activity_counts.parts.pending_movement_count)--;
    }

    actor_flags = ((EntityRec *)actor)->flags1C;
    if (actor_flags & 0x2000) {
        if (((EntityRec *)actor)->unk_46 & 0x8000) {
            ((EntityRec *)actor)->unk_46 &= 0x7FFF;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            ((EntityRec *)actor)->facing = get_rounded_facing_and_rounding_flag(
                ((SpriteFrameState *)sprite)->unk_24,
                ((SpriteFrameState *)sprite)->unk_25,
                D_80082E80.tile_position.parts.tile_x,
                D_80082E80.tile_position.parts.tile_y,
                &facing_aux);
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        ((S_8016CB4C_0 *)action)->unk_8C = D_8016B6F4;
        on_actor_status_updated(actor);
    }
}

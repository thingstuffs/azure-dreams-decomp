#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_8014EB4C_0 {
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
} S_8014EB4C_0;   /* arg0 in update_hop_motion_and_completion */

extern void select_sprite_entry(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void advance_status_timers(void *);
extern void on_actor_status_updated(void *);
extern void reduce_actor_food_meter(void *, s32);
extern s32 check_actor_floor_trap(void *, void *);

extern u8 D_8014D6F4[];
extern u8 D_80151554[];
extern u8 D_80151574[];
extern u8 D_8015157C[];

/* Updates hop motion and animations, then finishes the action when its timer expires. */
void update_hop_motion_and_completion(void *action, void *motion, void *sprite, void *actor)
{
    s32 state;
    s32 move_frames;
    s32 target_x;
    s32 pos_x;
    s32 height_offset;
    s32 arc_offset;
    s32 pos_y;
    s32 frame_count;
    s32 action_timer;
    s32 actor_flags;
    s32 direction_aux;
    DungeonGlobalStatus *global_state;
    u8 *anim_table;

    state = ((S_8014EB4C_0 *)action)->unk_9B;
    switch (state) {
    case 0:
    {
        u8 *state_anims;

        if (!(((SpriteFrameState *)sprite)->flags & 0x6000)) {
            break;
        }
        state_anims = D_80151574;
        ((SpriteFrameState *)sprite)->frameTable = state_anims;
        select_sprite_entry(sprite,
            state_anims[((g_game_work.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);
        ((SpriteFrameState *)sprite)->scale_y = 0x1000;
        ((S_8014EB4C_0 *)action)->unk_98 |= 8;
        ((EntityRec *)actor)->flags1C &= 0xF7FFFFFF;
        ((S_8014EB4C_0 *)action)->unk_9E.s = 5;
        ((S_8014EB4C_0 *)action)->unk_A4 = 0;
        ((S_8014EB4C_0 *)action)->unk_9B++;
    }
    case 1:
        move_frames = ((S_8014EB4C_0 *)action)->unk_9E.s;
        ((S_8014EB4C_0 *)action)->unk_90 -= ((S_8014EB4C_0 *)action)->unk_A4;
        if (move_frames != 0) {
            target_x = ((SpriteFrameState *)sprite)->unk_24;
            pos_x = ((EntityRec *)motion)->x.w.i;
            target_x <<= 6;
            pos_x -= 0x20;
            ((EntityRec *)motion)->unk_0C = ((target_x - pos_x) << 16) / move_frames;

            pos_y = ((EntityRec *)motion)->y.w.i;
            pos_y -= 0x20;
            ((EntityRec *)motion)->unk_10 =
                (((((SpriteFrameState *)sprite)->unk_25 << 6) - pos_y) << 16) /
                ((S_8014EB4C_0 *)action)->unk_9E.s;

            ((S_8014EB4C_0 *)action)->unk_A4 =
                (-func_800644B8(((S_8014EB4C_0 *)action)->unk_9E.s * 0x199)) << 10;
        }

        height_offset = ((S_8014EB4C_0 *)action)->unk_90;
        arc_offset = ((S_8014EB4C_0 *)action)->unk_A4;
        frame_count = ((S_8014EB4C_0 *)action)->unk_9E.u;
        height_offset += arc_offset;
        frame_count -= 1;
        ((S_8014EB4C_0 *)action)->unk_9E.u = frame_count;
        ((S_8014EB4C_0 *)action)->unk_90 = height_offset;
        if ((frame_count << 16) < 0) {
            ((S_8014EB4C_0 *)action)->unk_90 = 0;
            ((S_8014EB4C_0 *)action)->unk_98 &= 0xFFF7;
            ((EntityRec *)actor)->flags1C |= 0x08000000;
            ((S_8014EB4C_0 *)action)->unk_9B++;
        }
    case 2:
    {
        u8 *state_anims;

        if (((EntityRec *)actor)->flags1C & 0x08000000) {
            ((S_8014EB4C_0 *)action)->unk_98 &= 0xFFF7;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
            state_anims = D_8015157C;
            ((SpriteFrameState *)sprite)->frameTable = state_anims;
            select_sprite_entry(sprite,
                state_anims[((g_game_work.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
                0);
            ((SpriteFrameState *)sprite)->scale_y = 0xC00;
            ((S_8014EB4C_0 *)action)->unk_9B++;
        }
    }
        break;
    case 3:
        anim_table = D_80151554;
        if (*(u8 * *)&((SpriteFrameState *)sprite)->frameTable != anim_table) {
            ((SpriteFrameState *)sprite)->frameTable = anim_table;
            select_sprite_entry(sprite,
                anim_table[((g_game_work.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
                0);
            ((SpriteFrameState *)sprite)->scale_y = 0x1000;
        }
        break;
    }

    action_timer = ((S_8014EB4C_0 *)action)->unk_96 - 1;
    ((S_8014EB4C_0 *)action)->unk_96 = action_timer;
    if ((action_timer << 16) > 0) {
        return;
    }

    ((EntityRec *)motion)->flags14 = 0;
    ((EntityRec *)motion)->unk_10 = 0;
    ((EntityRec *)motion)->unk_0C = 0;
    ((SpriteFrameState *)sprite)->scale_y = 0x1000;
    set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
    reduce_actor_food_meter(actor, 3);
    advance_status_timers(actor);

    global_state = &g_dungeon_status;
    if (global_state->unk_08 != 0) {
        (*(u16 *)&global_state->unk_08)--;
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
                D_80082E80.tileX,
                D_80082E80.tileY,
                &direction_aux);
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        ((S_8014EB4C_0 *)action)->unk_8C = D_8014D6F4;
        on_actor_status_updated(actor);
    }
}

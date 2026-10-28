#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/actor.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"

typedef struct S_80154C54_0 {
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
} S_80154C54_0;   /* arg0 in update_timed_movement_arc */

extern void select_sprite_entry(void *, s32, s32);
extern s32 rsin(s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void on_actor_status_updated(void *);
extern void spend_actor_mp(void *, s32);


extern s32 D_801537F4;
extern u8 snowman_frame_set_5[];
extern u8 D_801579A8[];
extern u8 D_801579B8[];

/* Updates a timed movement arc, its animations, and the actor's completion state. */
void update_timed_movement_arc(void *action, void *motion, void *sprite, void *actor)
{
    s32 state;
    s32 move_frames;
    s32 target_x;
    s32 pos_x;
    s32 height_offset;
    s32 arc_offset;
    s32 pos_y;
    s32 next_frames;
    s32 action_timer;
    s32 actor_flags;
    u16 direction_aux;
    DungeonGlobalStatus *global_state;

    state = ((S_80154C54_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (!(((SpriteFrameState *)sprite)->flags & 0x6000)) {
            break;
        }
        ((SpriteFrameState *)sprite)->frameTable = D_801579A8;
        select_sprite_entry(
            sprite,
            D_801579A8[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7],
            0);
        ((S_80154C54_0 *)action)->unk_98 |= 8;
        ((ActorRecord *)actor)->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        ((S_80154C54_0 *)action)->unk_9E.s = 5;
        ((S_80154C54_0 *)action)->unk_A4 = 0;
        ((S_80154C54_0 *)action)->unk_9B++;
                        /* fallthrough */
    case 1:
        move_frames = ((S_80154C54_0 *)action)->unk_9E.s;
        ((S_80154C54_0 *)action)->unk_90 -= ((S_80154C54_0 *)action)->unk_A4;
        if (move_frames != 0) {
            target_x = ((SpriteFrameState *)sprite)->tile_x;
            pos_x = ((EntityRec *)motion)->x.w.i;
            target_x <<= 6;
            pos_x -= 0x20;

            ((EntityRec *)motion)->unk_0C = ((target_x - pos_x) << 16) / move_frames;

            pos_y = ((EntityRec *)motion)->y.w.i;
            pos_y -= 0x20;
            ((EntityRec *)motion)->unk_10 =
                (((((SpriteFrameState *)sprite)->tile_y << 6) - pos_y) << 16) /
                ((S_80154C54_0 *)action)->unk_9E.s;

            ((S_80154C54_0 *)action)->unk_A4 =
                (-rsin(((S_80154C54_0 *)action)->unk_9E.s * 0x199)) << 10;
        }

        height_offset = ((S_80154C54_0 *)action)->unk_90;
        arc_offset = ((S_80154C54_0 *)action)->unk_A4;
        next_frames = ((S_80154C54_0 *)action)->unk_9E.u;
        height_offset += arc_offset;
        next_frames -= 1;
        ((S_80154C54_0 *)action)->unk_9E.u = next_frames;
        ((S_80154C54_0 *)action)->unk_90 = height_offset;
        if ((next_frames << 16) < 0) {
            ((S_80154C54_0 *)action)->unk_90 = 0;
            ((S_80154C54_0 *)action)->unk_98 &= 0xFFF7;
            ((ActorRecord *)actor)->flags1C |= ACTOR_GROUNDED;
            ((S_80154C54_0 *)action)->unk_9B++;
        }
                        /* fallthrough */
    case 2:
        if (((ActorRecord *)actor)->flags1C & ACTOR_GROUNDED) {
            ((S_80154C54_0 *)action)->unk_98 &= 0xFFF7;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->tile_x, ((SpriteFrameState *)sprite)->tile_y);
            ((SpriteFrameState *)sprite)->frameTable = D_801579B8;
            select_sprite_entry(
                sprite,
                D_801579B8[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7],
                0);
            ((S_80154C54_0 *)action)->unk_9B++;
        }
        break;
    case 3:
        if (*(u8 * *)&((SpriteFrameState *)sprite)->frameTable != snowman_frame_set_5) {
            ((SpriteFrameState *)sprite)->frameTable = snowman_frame_set_5;
            select_sprite_entry(
                sprite,
                snowman_frame_set_5[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7],
                0);
        }
        break;
    }

    action_timer = ((S_80154C54_0 *)action)->unk_96 - 1;
    ((S_80154C54_0 *)action)->unk_96 = action_timer;
    if ((action_timer << 16) > 0) {
        return;
    }

    ((EntityRec *)motion)->flags14 = 0;
    ((EntityRec *)motion)->unk_10 = 0;
    ((EntityRec *)motion)->unk_0C = 0;
    set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->tile_x, ((SpriteFrameState *)sprite)->tile_y);
    spend_actor_mp(actor, 4);
    advance_status_timers(actor);

    global_state = &g_dungeon_status;
    if (global_state->activity_counts.parts.pending_movement_count != 0) {
        (*(u16 *)&global_state->activity_counts.parts.pending_movement_count)--;
    }

    actor_flags = ((ActorRecord *)actor)->flags1C;
    if (actor_flags & 0x2000) {
        if (((ActorRecord *)actor)->action_flags & ACTOR_ACTION_PENDING) {
            ((ActorRecord *)actor)->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
    } else {
        if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                ((ActorRecord *)actor)->facing = get_rounded_facing_and_rounding_flag(
                    ((SpriteFrameState *)sprite)->tile_x,
                    ((SpriteFrameState *)sprite)->tile_y,
                    reference_tile_object.tile_position.parts.tile_x,
                    reference_tile_object.tile_position.parts.tile_y,
                    &direction_aux);
            }
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        ((S_80154C54_0 *)action)->unk_8C = &D_801537F4;
        on_actor_status_updated(actor);
    }
}

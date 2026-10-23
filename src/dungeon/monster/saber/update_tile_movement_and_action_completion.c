#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/monster/saber.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_8016CBAC_0 {
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
} S_8016CBAC_0;   /* arg0 in update_tile_movement_and_action_completion */

extern void select_sprite_entry(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void advance_status_timers(void *);
extern void on_actor_status_updated(void *);
extern void spend_actor_mp(void *, s32);


extern s32 D_8016B728;
extern u8 D_8016EDEC[];
extern u8 D_8016EE0C[];
extern u8 D_8016EE14[];

/* Updates movement toward a tile, its animation, and action completion. */
void update_tile_movement_and_action_completion(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    s32 move_ticks;
    s32 target_x;
    s32 pos_x;
    s32 height_offset;
    s32 height_step;
    s32 pos_y;
    s32 next_tick;
    s32 action_ticks;
    s32 actor_flags;
    s32 facing_aux;
    DungeonGlobalStatus *global_state;

    switch (((S_8016CBAC_0 *)action)->unk_9B) {
    case 0:
        if (!(sprite->flags & 0x6000)) {
            break;
        }
        sprite->frameTable = D_8016EE0C;
        select_sprite_entry(
            sprite,
            D_8016EE0C[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_8016CBAC_0 *)action)->unk_98 |= 8;
        actor->flags1C &= 0xF7FFFFFF;
        ((S_8016CBAC_0 *)action)->unk_9E.s = 5;
        ((S_8016CBAC_0 *)action)->unk_A4 = 0;
        ((S_8016CBAC_0 *)action)->unk_9B++;
                        /* fall through */

    case 1:
        move_ticks = ((S_8016CBAC_0 *)action)->unk_9E.s;
        ((S_8016CBAC_0 *)action)->unk_90 -= ((S_8016CBAC_0 *)action)->unk_A4;
        if (move_ticks != 0) {
            target_x = sprite->unk_24;
            pos_x = ((EntityRec *)motion)->x.w.i;
            target_x <<= 6;
            pos_x -= 0x20;

            ((EntityRec *)motion)->unk_0C = ((target_x - pos_x) << 16) / move_ticks;

            pos_y = ((EntityRec *)motion)->y.w.i;
            pos_y -= 0x20;
            ((EntityRec *)motion)->unk_10 =
                (((sprite->unk_25 << 6) - pos_y) << 16) /
                ((S_8016CBAC_0 *)action)->unk_9E.s;

            ((S_8016CBAC_0 *)action)->unk_A4 =
                (-func_800644B8(((S_8016CBAC_0 *)action)->unk_9E.s * 0x199)) << 10;
        }

        height_offset = ((S_8016CBAC_0 *)action)->unk_90;
        height_step = ((S_8016CBAC_0 *)action)->unk_A4;
        next_tick = ((S_8016CBAC_0 *)action)->unk_9E.u;
        height_offset += height_step;
        next_tick -= 1;
        ((S_8016CBAC_0 *)action)->unk_9E.u = next_tick;
        ((S_8016CBAC_0 *)action)->unk_90 = height_offset;
        if ((next_tick << 16) < 0) {
            ((S_8016CBAC_0 *)action)->unk_90 = 0;
            ((S_8016CBAC_0 *)action)->unk_98 &= 0xFFF7;
            actor->flags1C |= 0x08000000;
            ((S_8016CBAC_0 *)action)->unk_9B++;
        }
                        /* fall through */

    case 2:
        if (actor->flags1C & 0x08000000) {
            ((S_8016CBAC_0 *)action)->unk_98 &= 0xFFF7;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            set_record_integer_tile_center(motion, sprite->unk_24, sprite->unk_25);
            sprite->frameTable = D_8016EE14;
            select_sprite_entry(
                sprite,
                D_8016EE14[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_8016CBAC_0 *)action)->unk_9B++;
        }
        break;

    case 3:
        if (*(u8 * *)&sprite->frameTable != D_8016EDEC) {
            sprite->frameTable = D_8016EDEC;
            select_sprite_entry(
                sprite,
                D_8016EDEC[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }
        break;

    default:
        break;
    }

decrement_timer:
    action_ticks = ((S_8016CBAC_0 *)action)->unk_96 - 1;
    ((S_8016CBAC_0 *)action)->unk_96 = action_ticks;
    if ((action_ticks << 16) > 0) {
        return;
    }

    ((EntityRec *)motion)->flags14 = 0;
    ((EntityRec *)motion)->unk_10 = 0;
    ((EntityRec *)motion)->unk_0C = 0;
    set_record_integer_tile_center(motion, sprite->unk_24, sprite->unk_25);
    spend_actor_mp(actor, 4);
    advance_status_timers(actor);

    global_state = &g_dungeon_status;
    if (global_state->activity_counts.parts.pending_movement_count != 0) {
        (*(u16 *)&global_state->activity_counts.parts.pending_movement_count)--;
    }

    actor_flags = actor->flags1C;
    if (actor_flags & 0x2000) {
        if (actor->action_flags & ACTOR_ACTION_PENDING) {
            actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            actor->facing = get_rounded_facing_and_rounding_flag(
                sprite->unk_24,
                sprite->unk_25,
                reference_tile_object.tile_position.parts.tile_x,
                reference_tile_object.tile_position.parts.tile_y,
                &facing_aux);
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        ((S_8016CBAC_0 *)action)->unk_8C = &D_8016B728;
        on_actor_status_updated(actor);
    }
}

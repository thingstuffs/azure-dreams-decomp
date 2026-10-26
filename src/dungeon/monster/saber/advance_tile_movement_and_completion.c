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

typedef struct S_80172BAC_0 {
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
} S_80172BAC_0;   /* arg0 in advance_tile_movement_and_completion */

extern void select_sprite_entry(void *, s32, s32);
extern s32 rsin(s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void on_actor_status_updated(void *);
extern void spend_actor_mp(void *, s32);


#include "dungeon/monster/saber.h"

extern u8 D_80174E0C[];
extern u8 D_80174E14[];

/* Advance movement toward a tile, update animation, and resolve completion. */
void advance_tile_movement_and_completion(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *map_entity, ActorRecord *actor) {
    s32 state;
    s32 move_ticks;
    s32 target_x;
    s32 pos_x;
    s32 height;
    s32 arc_offset;
    s32 pos_y;
    s32 next_move_ticks;
    s32 action_ticks;
    s32 actor_flags;
    u16 direction_aux;
    DungeonGlobalStatus *globals;

    state = action->action_phase;
    switch (state) {
    case 0:
        if (!(map_entity->flags & 0x6000)) {
            break;
        }
        map_entity->frameTable = D_80174E0C;
        select_sprite_entry(
            map_entity,
            D_80174E0C[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        action->action_state_flags |= 8;
        actor->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        ((S_80172BAC_0 *)action)->unk_9E.s = 5;
        ((S_80172BAC_0 *)action)->unk_A4 = 0;
        action->action_phase++;

    case 1:
        move_ticks = ((S_80172BAC_0 *)action)->unk_9E.s;
        ((S_80172BAC_0 *)action)->unk_90 -= ((S_80172BAC_0 *)action)->unk_A4;
        if (move_ticks != 0) {
            target_x = map_entity->tile_x;
            pos_x = ((EntityRec *)motion)->x.w.i;
            target_x <<= 6;
            pos_x -= 0x20;

            ((EntityRec *)motion)->unk_0C = ((target_x - pos_x) << 16) / move_ticks;

            pos_y = ((EntityRec *)motion)->y.w.i;
            pos_y -= 0x20;
            ((EntityRec *)motion)->unk_10 =
                (((map_entity->tile_y << 6) - pos_y) << 16) /
                ((S_80172BAC_0 *)action)->unk_9E.s;

            ((S_80172BAC_0 *)action)->unk_A4 =
                (-rsin(((S_80172BAC_0 *)action)->unk_9E.s * 0x199)) << 10;
        }

        height = ((S_80172BAC_0 *)action)->unk_90;
        arc_offset = ((S_80172BAC_0 *)action)->unk_A4;
        next_move_ticks = ((S_80172BAC_0 *)action)->unk_9E.u;
        height += arc_offset;
        next_move_ticks -= 1;
        ((S_80172BAC_0 *)action)->unk_9E.u = next_move_ticks;
        ((S_80172BAC_0 *)action)->unk_90 = height;
        if ((next_move_ticks << 16) < 0) {
            ((S_80172BAC_0 *)action)->unk_90 = 0;
            action->action_state_flags &= 0xFFF7;
            actor->flags1C |= ACTOR_GROUNDED;
            action->action_phase++;
        }

    case 2:
        if (actor->flags1C & ACTOR_GROUNDED) {
            action->action_state_flags &= 0xFFF7;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            set_record_integer_tile_center(motion, map_entity->tile_x, map_entity->tile_y);
            map_entity->frameTable = D_80174E14;
            select_sprite_entry(
                map_entity,
                D_80174E14[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            action->action_phase++;
        }
        break;

    case 3:
        if (*(u8 * *)&map_entity->frameTable == saber_direction_frames) {
            break;
        }
        map_entity->frameTable = saber_direction_frames;
        select_sprite_entry(
            map_entity,
            saber_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        break;
    }
    action_ticks = ((S_80172BAC_0 *)action)->unk_96 - 1;
    ((S_80172BAC_0 *)action)->unk_96 = action_ticks;
    if ((action_ticks << 16) > 0) {
        return;
    }

    ((EntityRec *)motion)->flags14 = 0;
    ((EntityRec *)motion)->unk_10 = 0;
    ((EntityRec *)motion)->unk_0C = 0;
    set_record_integer_tile_center(motion, map_entity->tile_x, map_entity->tile_y);
    spend_actor_mp(actor, 4);
    advance_status_timers(actor);

    globals = &g_dungeon_status;
    if (globals->activity_counts.parts.pending_movement_count != 0) {
        (*(u16 *)&globals->activity_counts.parts.pending_movement_count)--;
    }

    actor_flags = actor->flags1C;
    if (actor_flags & 0x2000) {
        if (actor->action_flags & ACTOR_ACTION_PENDING) {
            actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            actor->facing = get_rounded_facing_and_rounding_flag(
                map_entity->tile_x,
                map_entity->tile_y,
                reference_tile_object.tile_position.parts.tile_x,
                reference_tile_object.tile_position.parts.tile_y,
                &direction_aux);
        }
    }
    if ((check_actor_floor_trap(map_entity, actor) << 16) > 0) {
        ((S_80172BAC_0 *)action)->unk_8C = &saber_behavior_entry;
        on_actor_status_updated(actor);
    }
}

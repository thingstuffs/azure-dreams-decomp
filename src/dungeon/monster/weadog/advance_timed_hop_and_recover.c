#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/monster/weadog.h"
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
#include "dungeon/item.h"
#include "sdk/libgte.h"





extern s32 D_80165CE8;
extern u8 D_80168EB8[];
extern u8 D_80168ED0[];
extern u8 D_80168ED8[];

/* Updates a timed hop toward the target tile and handles actor recovery when the timer expires. */
void advance_timed_hop_and_recover(ActorRecord *motion_state, void *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    u16 direction_aux;
    s32 state;
    s32 hop_ticks;
    s32 actor_flags;
    s32 target_x;
    s32 position_x;
    s32 position_y;
    s16 phase_ticks;
    u16 action_ticks;
    u8 *anim_table;

    state = motion_state->action_phase;
    switch (state) {
    case 0:
        phase_ticks = motion_state->unk_9E - 1;
        motion_state->unk_9E = phase_ticks;
        if ((phase_ticks << 16) != 0) {
            break;
        }

        sprite->frameTable = D_80168ED0;
        select_sprite_entry(
            sprite,
            D_80168ED0[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        motion_state->action_state_flags |= 8;
        actor->flags1C &= 0xF7FFFFFF;
        motion_state->unk_9E = 5;
        motion_state->unk_A0.value = 0;
        motion_state->action_phase++;

    case 1:
        hop_ticks = ((s16)motion_state->unk_9E);
        motion_state->unk_90.value -= motion_state->unk_A0.value;
        if (hop_ticks != 0) {
            target_x = sprite->tile_x;
            position_x = ((EntityRec *)motion)->x.w.i;
            target_x <<= 6;
            position_x -= 0x20;
            ((EntityRec *)motion)->unk_0C = ((target_x - position_x) << 16) / hop_ticks;

            position_y = ((EntityRec *)motion)->y.w.i;
            position_y -= 0x20;
            ((EntityRec *)motion)->unk_10 =
                (((sprite->tile_y << 6) - position_y) << 16) /
                ((s16)motion_state->unk_9E);
            motion_state->unk_A0.value =
                (-rsin(((s16)motion_state->unk_9E) * 0x199)) << 10;
        }

        motion_state->unk_90.value += motion_state->unk_A0.value;
        phase_ticks = motion_state->unk_9E - 1;
        motion_state->unk_9E = phase_ticks;
        if (phase_ticks < 0) {
            motion_state->unk_90.value = 0;
            motion_state->action_state_flags &= 0xFFF7;
            actor->flags1C |= 0x08000000;
            motion_state->action_phase++;
        }

    case 2:
        if (actor->flags1C & 0x08000000) {
            motion_state->action_state_flags &= 0xFFF7;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);

            sprite->frameTable = D_80168ED8;
            select_sprite_entry(
                sprite,
                D_80168ED8[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            motion_state->action_phase++;
        }
        break;

    case 3:
        anim_table = D_80168EB8;
        if (*(u8 * *)&sprite->frameTable != anim_table) {
            sprite->frameTable = anim_table;
            select_sprite_entry(
                sprite,
                anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }

    default:
        break;
    }

    action_ticks = motion_state->action_timer - 1;
    motion_state->action_timer = action_ticks;
    if ((s16)action_ticks > 0) {
        return;
    }

    ((EntityRec *)motion)->flags14 = 0;
    ((EntityRec *)motion)->unk_10 = 0;
    ((EntityRec *)motion)->unk_0C = 0;
    set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
    spend_actor_mp(actor, 4);
    advance_status_timers(actor);

    if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
        g_dungeon_status.activity_counts.parts.pending_movement_count--;
    }

    actor_flags = ((s32)actor->flags1C);
    if (actor_flags & 0x2000) {
        if (actor->action_flags & 0x8000) {
            actor->action_flags &= 0x7FFF;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            actor->facing = get_rounded_facing_and_rounding_flag(
                sprite->tile_x, sprite->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &direction_aux);
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        motion_state->unk_8C.word_ptr = &D_80165CE8;
        on_actor_status_updated(actor);
    }
}

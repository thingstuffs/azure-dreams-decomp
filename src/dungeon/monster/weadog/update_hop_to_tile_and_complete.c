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
#include "dungeon/item.h"
#include "sdk/libgte.h"

extern s32 D_8016BCE8;
extern u8 D_8016EEB8[];
extern u8 D_8016EED0[];
extern u8 D_8016EED8[];

/* Updates an actor's hop to its tile and finishes the timed action. */
void update_hop_to_tile_and_complete(void *action, ObjectPosition *motion, SpriteFrameState *sprite, void *actor)
{
    u16 facing_aux;
    s32 state;
    s32 move_ticks;
    s32 actor_flags;
    s32 tile_x;
    s32 position_x;
    s32 position_y;
    s16 phase_timer;
    u16 action_timer;
    u8 *anim_table;

    state = ((ActorRecord *)action)->action_phase.u;
    switch (state) {
    case 0:
        phase_timer = ((ActorRecord *)action)->unk_9E.u - 1;
        ((ActorRecord *)action)->unk_9E.u = phase_timer;
        if ((phase_timer << 16) != 0) {
            break;
        }

        sprite->frameTable = D_8016EED0;
        select_sprite_entry(
            sprite,
            D_8016EED0[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7],
            0);
        ((ActorRecord *)action)->action_state_flags |= 8;
        ((ActorRecord *)actor)->flags1C &= 0xF7FFFFFF;
        ((ActorRecord *)action)->unk_9E.s = 5;
        ((ActorRecord *)action)->unk_A0.value = 0;
        ((ActorRecord *)action)->action_phase.u++;

    case 1:
        move_ticks = ((ActorRecord *)action)->unk_9E.s;
        ((ActorRecord *)action)->unk_90.value -= ((ActorRecord *)action)->unk_A0.value;
        if (move_ticks != 0) {
            tile_x = sprite->tile_x;
            position_x = motion->x.w.i;
            tile_x <<= 6;
            position_x -= 0x20;
            motion->velocity_x = ((tile_x - position_x) << 16) / move_ticks;

            position_y = motion->y.w.i;
            position_y -= 0x20;
            motion->velocity_y =
                (((sprite->tile_y << 6) - position_y) << 16) /
                ((ActorRecord *)action)->unk_9E.s;
            ((ActorRecord *)action)->unk_A0.value =
                (-rsin(((ActorRecord *)action)->unk_9E.s * 0x199)) << 10;
        }

        ((ActorRecord *)action)->unk_90.value += ((ActorRecord *)action)->unk_A0.value;
        phase_timer = ((ActorRecord *)action)->unk_9E.u - 1;
        ((ActorRecord *)action)->unk_9E.u = phase_timer;
        if (phase_timer < 0) {
            ((ActorRecord *)action)->unk_90.value = 0;
            ((ActorRecord *)action)->action_state_flags &= 0xFFF7;
            ((ActorRecord *)actor)->flags1C |= 0x08000000;
            ((ActorRecord *)action)->action_phase.u++;
        }

    case 2:
        if (((u32)((ActorRecord *)actor)->flags1C) & 0x08000000) {
            ((ActorRecord *)action)->action_state_flags &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);

            sprite->frameTable = D_8016EED8;
            select_sprite_entry(
                sprite,
                D_8016EED8[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7],
                0);
            ((ActorRecord *)action)->action_phase.u++;
        }
        break;

    case 3:
        anim_table = D_8016EEB8;
        if (*(u8 * *)&sprite->frameTable != anim_table) {
            sprite->frameTable = anim_table;
            select_sprite_entry(
                sprite,
                anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7],
                0);
        }

    default:
        break;
    }

    action_timer = ((ActorRecord *)action)->action_timer.u - 1;
    ((ActorRecord *)action)->action_timer.u = action_timer;
    if ((s16)action_timer > 0) {
        return;
    }

    motion->velocity_z = 0;
    motion->velocity_y = 0;
    motion->velocity_x = 0;
    set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
    spend_actor_mp(actor, 4);
    advance_status_timers(actor);

    if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
        g_dungeon_status.activity_counts.parts.pending_movement_count--;
    }

    actor_flags = ((ActorRecord *)actor)->flags1C;
    if (actor_flags & 0x2000) {
        if (((ActorRecord *)actor)->action_flags & 0x8000) {
            ((ActorRecord *)actor)->action_flags &= 0x7FFF;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            ((ActorRecord *)actor)->facing = get_rounded_facing_and_rounding_flag(
                sprite->tile_x, sprite->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &facing_aux);
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        ((ActorRecord *)action)->unk_8C.word_ptr = &D_8016BCE8;
        on_actor_status_updated(actor);
    }
}

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




extern s32 rsin(s32);

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

    state = ((ActorRecord *)action)->action_phase.u;
    switch (state) {
    case 0:
        phase_ticks = ((ActorRecord *)action)->unk_9E.u - 1;
        ((ActorRecord *)action)->unk_9E.u = phase_ticks;
        if ((phase_ticks << 16) != 0) {
            break;
        }

        ((SpriteFrameState *)sprite)->frameTable = D_80162ED0;
        select_sprite_entry(
            sprite,
            D_80162ED0[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7],
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
            target_x = ((SpriteFrameState *)sprite)->tile_x;
            pos_x = ((ObjectPosition *)motion)->x.w.i;
            target_x <<= 6;
            pos_x -= 0x20;
            ((ObjectPosition *)motion)->velocity_x = ((target_x - pos_x) << 16) / move_ticks;

            pos_y = ((ObjectPosition *)motion)->y.w.i;
            pos_y -= 0x20;
            ((ObjectPosition *)motion)->velocity_y =
                (((((SpriteFrameState *)sprite)->tile_y << 6) - pos_y) << 16) /
                ((ActorRecord *)action)->unk_9E.s;
            ((ActorRecord *)action)->unk_A0.value =
                (-rsin(((ActorRecord *)action)->unk_9E.s * 0x199)) << 10;
        }

        ((ActorRecord *)action)->unk_90.value += ((ActorRecord *)action)->unk_A0.value;
        phase_ticks = ((ActorRecord *)action)->unk_9E.u - 1;
        ((ActorRecord *)action)->unk_9E.u = phase_ticks;
        if (phase_ticks < 0) {
            ((ActorRecord *)action)->unk_90.value = 0;
            ((ActorRecord *)action)->action_state_flags &= 0xFFF7;
            ((ActorRecord *)actor)->flags1C |= 0x08000000;
            ((ActorRecord *)action)->action_phase.u++;
        }

    case 2:
        if (((u32)((ActorRecord *)actor)->flags1C) & 0x08000000) {
            ((ActorRecord *)action)->action_state_flags &= 0xFFF7;
            ((ObjectPosition *)motion)->velocity_z = 0;
            ((ObjectPosition *)motion)->velocity_y = 0;
            ((ObjectPosition *)motion)->velocity_x = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->tile_x, ((SpriteFrameState *)sprite)->tile_y);

            ((SpriteFrameState *)sprite)->frameTable = weadog_frame_set_6;
            select_sprite_entry(
                sprite,
                weadog_frame_set_6[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7],
                0);
            ((ActorRecord *)action)->action_phase.u++;
        }
        break;

    case 3:
        anim_table = D_80162EB8;
        if (*(u8 * *)&((SpriteFrameState *)sprite)->frameTable != anim_table) {
            ((SpriteFrameState *)sprite)->frameTable = anim_table;
            select_sprite_entry(
                sprite,
                anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7],
                0);
        }

    default:
        break;
    }

    action_ticks = ((ActorRecord *)action)->action_timer.u - 1;
    ((ActorRecord *)action)->action_timer.u = action_ticks;
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

    actor_flags = ((ActorRecord *)actor)->flags1C;
    if (actor_flags & 0x2000) {
        if (((ActorRecord *)actor)->action_flags & 0x8000) {
            ((ActorRecord *)actor)->action_flags &= 0x7FFF;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            ((ActorRecord *)actor)->facing = get_rounded_facing_and_rounding_flag(
                ((SpriteFrameState *)sprite)->tile_x, ((SpriteFrameState *)sprite)->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &direction_aux);
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        ((ActorRecord *)action)->unk_8C.word_ptr = &D_8015FCE8;
        on_actor_status_updated(actor);
    }
}

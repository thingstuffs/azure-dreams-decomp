#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/monster/unicorn.h"
#include "shared/object_node.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/sprite_frame_state.h"
#include "engine/cd.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
extern int abs(int);

typedef struct S_80172AB4_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172AB4_3;   /* record in update_actor_move_animation_and_recovery */

   /* arg2 in update_actor_move_animation_and_recovery */


extern void select_sprite_entry(void *, s32, s32);
extern void play_sound_if_enabled(s32);
extern void create_two_row_object_group(void *payload, s16 value_scale);

extern u8 D_80174D94[];
extern u8 unicorn_frame_set_1[];
extern u8 D_80174DA4[];

/* Updates the actor's move, animation, and recovery state. */
/* Animates Unicorn's vertical hop while casting a targeted spell with two effect rows, then restores idle
 * and status. */
void update_actor_move_animation_and_recovery(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    u8 *move_id;
    s32 state;
    s16 use_player;
    s32 move_kind;
    void *target;
    s32 target_x;
    u16 position[3];
    u16 ticks_left;

    state = body->action_phase.u;
    use_player = 0;
    switch (state) {
    case 0:
        if (actor->flags1C & ACTOR_PLAYER_SIDE) {
            move_kind = (actor->action_flags & 0x3FFF) - 1;
            switch (move_kind) {
            case 6:
                use_player = 1;
            case 2:
                move_id = (u8 *)actor + 0xE;
                break;
            case 5:
                use_player = 1;
            case 1:
                move_id = (u8 *)actor + 0xB;
                break;
            case 4:
                use_player = 1;
            case 0:
                move_id = (u8 *)actor + 8;
                break;
            default:
                move_id = 0;
                break;
            }
        } else {
            move_kind = actor->action_flags & 0x3FFF;
            switch (move_kind) {
            case 3:
                move_id = (u8 *)actor + 0xE;
                break;
            case 2:
                move_id = (u8 *)actor + 0xB;
                break;
            case 1:
                move_id = (u8 *)actor + 8;
                break;
            default:
                move_id = 0;
                break;
            }
        }
        if (*move_id != 0) {
            body->action_state_flags &= 0xFF7F;
            if (use_player != 0) {
                target = primary_actor_record;
                actor->target = target;
                move_kind = (s32)((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                actor->target_tile_x = ((S_80172AB4_3 *)(void *)move_kind)->unk_24;
                actor->target_tile_y = ((S_80172AB4_3 *)(void *)move_kind)->unk_25;
            } else if (item_action_definitions[*move_id].kind == 2) {
                target = actor->target;
                if (target != 0) {
                    move_kind = (s32)((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                    actor->target_tile_x = ((S_80172AB4_3 *)(void *)move_kind)->unk_24;
                    actor->target_tile_y = ((S_80172AB4_3 *)(void *)move_kind)->unk_25;
                }
            } else {
                actor->target =
                    scan_actor_along_heading(actor,
                                  sprite->tile_x,
                                  sprite->tile_y,
                                  actor->facing, 0x10);
                actor->target_tile_x = abs(actor->target_tile_x);
                actor->target_tile_y = abs(actor->target_tile_y);
            }

            position[0] = ((u16) motion->x.w.i);
            position[1] = ((u16) motion->y.w.i);
            position[2] = ((u16) motion->z.w.i);
            if (create_actor_spell_effect(actor, move_id, use_player,
                              (u16 *)((u8 *)body + 0x98)) == 0) {
                return;
            }
            sprite->flags &= 0xF7FF;
            play_sound_if_enabled(0x703);
            create_two_row_object_group(position, (s16)(((s32)*move_id - 1) % 3));
            body->action_phase.u++;
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        g_dungeon_status.active_actor = 0;
        primary_actor_record->unk_A4.halves.high.u--;
        advance_status_timers(actor);
        actor->pending_turn_updates--;
        body->unk_8C.address = &unicorn_action_continuation_address;
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= 0x7FFF;
        return;

    case 1:
        if (sprite->flags & 0x8000) {
            body->action_phase.u = 3;
            return;
        }
        if (!(sprite->flags & 0x6000)) {
            return;
        }
        (sprite->frameTable) = unicorn_frame_set_1;
        select_sprite_entry(
            sprite,
            unicorn_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        body->action_state_flags |= 8;
        actor->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        body->action_timer.u = 8;
        motion->velocity_z = 0xFFF00000;
        body->action_phase.u++;
        return;

    case 2:
        motion->velocity_z += 0x10000;
        ticks_left = body->action_timer.u - 1;
        body->action_timer.u = ticks_left;
        if ((s32)(ticks_left << 16) > 0) {
            return;
        }
        (sprite->frameTable) = D_80174DA4;
        select_sprite_entry(
            sprite,
            D_80174DA4[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        motion->velocity_z = 0;
        body->action_phase.u++;
        return;

    case 3:
        if (get_cd_command_queue_depth() != 0) {
            sprite->flags |= 0x800;
            return;
        }
        sprite->flags &= 0xF7FF;
        body->action_phase.u++;

    case 4:
        if (!(((sprite->unk_04 == 1) &&
               (sprite->flags & 0x1000)) ||
              (sprite->flags & 0xE000))) {
            return;
        }
        body->action_timer.u = 3;
        body->action_state_flags |= 0x80;
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        (sprite->frameTable) = unicorn_frame_set_1;
        select_sprite_entry(
            sprite,
            unicorn_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        body->action_state_flags &= 0xFFF7;
        actor->flags1C |= ACTOR_GROUNDED;

        body->action_phase.u++;
        return;

    case 5:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        (sprite->frameTable) = D_80174D94;
        select_sprite_entry(
            sprite,
            D_80174D94[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        body->action_phase.u = 0xFF;
        return;

    case 0xFF:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        if (*(unsigned char **)&sprite->frameTable != unicorn_frame_set) {
            (sprite->frameTable) = unicorn_frame_set;
            select_sprite_entry(
                sprite,
                unicorn_frame_set[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }
        {

            if ((g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        sprite->flags &= 0xF7FF;
        body->unk_8C.address = &unicorn_action_continuation_address;
        advance_status_timers(actor);
        if (actor->pending_turn_updates > 0) {
            actor->pending_turn_updates--;
        }
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= 0x7FFF;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);

        return;
    }
}

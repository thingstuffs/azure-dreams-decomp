#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/monster/baloon.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "engine/graphics.h"
#include "dungeon/item.h"


extern s32 rsin(s32);

extern u8 baloon_default_frames[];
extern u8 baloon_hop_frames[];
extern u8 D_800E2370[];

/* Advances the actor's hop animation and finishes the action when its timer expires. */
void advance_actor_hop_animation(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor)
{
    u16 facing_aux;
    s32 y_offset;
    u16 timer_value;
    s32 phase;

    phase = body->action_phase.u;
    switch (phase) {
    case 0:
        timer_value = body->unk_AA + 1;
        body->unk_AA = timer_value;
        if ((s16)timer_value < 2) {
            break;
        }
        sprite->frameTable = baloon_hop_frames;
        select_sprite_entry(sprite,
            baloon_hop_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        body->action_state_flags |= 8;
        actor->flags1C &= 0xF7FFFFFF;
        body->unk_AA = 5;
        body->unk_A4.value = 0;
        body->action_phase.u++;
                        /* fallthrough */
    case 1:
        body->unk_90.value -= body->unk_A4.value;
        if (body->unk_AA != 0) {
            position->velocity_x =
                (((sprite->tile_x << 6) -
                  ({ position->x.w.i - 0x20; })) << 16) /
                body->unk_AA;
            y_offset = position->y.w.i - 0x20;
            position->velocity_y =
                (((sprite->tile_y << 6) - y_offset) << 16) /
                body->unk_AA;
            body->unk_A4.value =
                (-rsin(body->unk_AA * 0x199)) << 10;
        }
        body->unk_90.value += body->unk_A4.value;
        timer_value = body->unk_AA - 1;
        body->unk_AA = timer_value;
        if ((s16)timer_value < 0) {
            body->unk_90.parts.high.s = -0x10;
            body->action_state_flags &= 0xFFF7;
            actor->flags1C |= 0x08000000;
            body->action_phase.u++;
        }
                        /* fallthrough */
    case 2:
        if (actor->flags1C & 0x08000000) {
            body->action_state_flags &= 0xFFF7;
            position->velocity_z = 0;
            position->velocity_y = 0;
            position->velocity_x = 0;
            set_record_integer_tile_center(position, sprite->tile_x, sprite->tile_y);
            sprite->frameTable = D_800E2370;
            select_sprite_entry(sprite,
                D_800E2370[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            body->action_phase.u++;
        }
        break;
        break;
    case 3:
        if (*(u8 * *)&sprite->frameTable != baloon_default_frames) {
            sprite->frameTable = baloon_default_frames;
            select_sprite_entry(sprite,
                baloon_default_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            body->unk_9E.s = 0;
        }
        break;
    }

    timer_value = body->action_timer.u - 1;
    body->action_timer.u = timer_value;
    if (((s32)timer_value << 16) <= 0) {
        s32 actor_flags;

        position->velocity_z = 0;
        position->velocity_y = 0;
        position->velocity_x = 0;
        set_record_integer_tile_center(position, sprite->tile_x, sprite->tile_y);
        spend_actor_mp(actor, 4);
        advance_status_timers(actor);
        if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
            g_dungeon_status.activity_counts.parts.pending_movement_count--;
        }
        actor_flags = actor->flags1C;
        if (actor_flags & 0x2000) {
            if (actor->action_flags & 0x8000) {
                actor->action_flags &= 0x7FFF;
            }
        } else {
            if (!(actor_flags & 0x410)) {
                if (actor_flags & 0x20000) {
                    actor->facing = get_rounded_facing_and_rounding_flag(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &facing_aux);
                }
            }
        }

        if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
            body->unk_8C.address = update_actor_turn_behavior;
            on_actor_status_updated(actor);
        }
    }
}

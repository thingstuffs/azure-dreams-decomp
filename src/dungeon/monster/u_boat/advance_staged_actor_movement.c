#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "engine/graphics.h"
#include "dungeon/system.h"


extern s32 rand(void);

extern void spawn_randomized_directional_effect(void *, s16, s32, s32); /* Unprototyped: retail call passes more arguments than the callee reads */
void create_owner_linked_directional_object(ActorRecord *owner_data, ObjectPosition *source_position, SpriteFrameState *source_sprite);

extern u8 uboat_default_frames[];
extern u8 u_boat_frame_set_1[];
#include "dungeon/monster/u_boat.h"
#include "dungeon/actor.h"
#include "dungeon/effect/screen.h"

typedef struct S_80173510_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x2];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    union { u8 n; u8 v; } unk_9B;   /* accessed as both */
    u8 pad_9C[0x14];
    u8 unk_B0;
} S_80173510_0;   /* arg0 in advance_staged_actor_movement */


/* Updates a staged movement animation and returns the entity to its tile center. */
/* Animates U-Boat's backward windup and forward strike, emits directional particles, applies damage, and
 * spends MP after returning. */
void advance_staged_actor_movement(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *record, ActorRecord *actor) {
    u8 state;

    state = action->action_phase.u;
    switch (state) {

    case 0:
        if (record->flags & 0x8000) {
            u8 *animation_ids;

            action->action_phase.u = 5;
            action->action_timer.u = 0;
            record->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, record, actor->facing, 1);

            animation_ids = uboat_default_frames;
            record->frameTable = animation_ids;
            select_sprite_entry(record,
                animation_ids[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            if (action->unk_B0.bytes[0] != 0) {
                return;
            }
            create_owner_linked_directional_object(action, motion, record);
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        action->action_timer.u = 2;
        action->action_state_flags &= 0xFFF7;
        action->action_phase.u++;
        return;

    case 1:
    {
        s16 *direction_x;
        s16 *direction_y;
        u16 timer;

        timer = action->action_timer.u;
        action->action_timer.u = timer - 1;
        if ((s16)timer > 0 && !(record->flags & 0x8000)) {
            return;
        }

        action->action_timer.u = 0x12;
        direction_x = (s16 *)((s8 *)dir_step_x);
        action->action_phase.u++;
        direction_y = (s16 *)((s8 *)dir_step_y);
        motion->velocity_x =
            -*(s16 *)((u8 *)direction_x +
              ((((u16)actor->facing) >> 8) & 0xE)) << 18;
        motion->velocity_y =
            -*(s16 *)((u8 *)direction_y +
              ((((u16)actor->facing) >> 8) & 0xE)) << 18;
        return;
    }

    case 2:
    {
        s16 *direction_x;
        s16 *direction_y;
        s32 eight;
        s8 entity_kind;
        u16 timer;

        if (action->action_timer.s == 0xB) {
            motion->velocity_x = 0;
            motion->velocity_y = 0;
        }

        eight = 8;
        if (action->action_timer.s == eight) {
            u8 *animation_ids;

            animation_ids = u_boat_frame_set_1;
            record->frameTable = animation_ids;
            select_sprite_entry(record,
                animation_ids[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                1);

            direction_x = (s16 *)((s8 *)dir_step_x);
            direction_y = (s16 *)((s8 *)dir_step_y);
            motion->velocity_x =
                *(s16 *)((u8 *)direction_x +
                  ((((u16)actor->facing) >> 8) & 0xE)) << 19;
            motion->velocity_y =
                *(s16 *)((u8 *)direction_y +
                  ((((u16)actor->facing) >> 8) & 0xE)) << 19;
        }

        entity_kind = record->unk_04;
        if (entity_kind == 4 || entity_kind == eight) {
            s32 particles_left;

            play_sound_if_enabled(0x706);
            particles_left = 0x14;
            do {
                s32 particle_random;

                particles_left--;
                particle_random = rand();
                spawn_randomized_directional_effect((u8 *)action - 0x20,
                    actor->facing, 0x8080FF,
                    (particle_random & 0xFF) | 0x80);
            } while (particles_left >= 0);
        }

        timer = action->action_timer.u;
        action->action_timer.u = timer - 1;
        if ((s16)timer <= 0 || (record->flags & 0x8000)) {
            action->action_timer.u = 4;
            action->action_phase.u++;
        }

        if (*(u8 * *)&record->frameTable != u_boat_frame_set_1) {
            return;
        }
        record->frame_ticks = 0;
        return;
    }

    case 3:
    {
        s16 timer;

        timer = action->action_timer.u - 1;
        action->action_timer.u = timer;
        if (timer == 3 || (record->flags & 0x8000)) {
            u8 *animation_ids;

            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            resolve_attack_damage_and_effects(actor, record, actor->facing, 1);

            animation_ids = uboat_default_frames;
            record->frameTable = animation_ids;
            select_sprite_entry(record,
                animation_ids[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            action->unk_90.parts.high.s = -0x20;
            if (action->unk_B0.bytes[0] == 0) {
                create_owner_linked_directional_object(action, motion, record);
            }
        }

        if (action->action_timer.s > 0 &&
            !(record->flags & 0x8000)) {
            return;
        }
        action->action_timer.u = 2;
        action->action_phase.u++;
        return;
    }

    case 4:
    {
        u16 timer;

        timer = action->action_timer.u;
        action->action_timer.u = timer - 1;
        if ((s16)timer > 0 && !(record->flags & 0x8000)) {
            return;
        }
        action->action_timer.u = 6;
        action->action_phase.u++;
        return;
    }

    case 5:
    {
        s32 distance;
        s32 axis_position;
        s16 timer;

        timer = action->action_timer.s;
        if (timer != 0) {
            distance = record->tile_x << 6;
            axis_position = motion->x.w.i;
            axis_position -= 0x20;
            distance -= axis_position;
            motion->velocity_x = (distance << 16) / timer;

            axis_position = motion->y.w.i;
            distance = record->tile_y << 6;
            axis_position -= 0x20;
            distance -= axis_position;
            motion->velocity_y =
                (distance << 16) / action->action_timer.s;
        }

        action->action_timer.u--;
        if (action->action_timer.s > 0 &&
            !(record->flags & 0x8000)) {
            return;
        }

        spend_actor_mp(actor, 0x100);
        action->unk_8C.address = uboat_behavior_entry;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        motion->velocity_x = 0;
        motion->velocity_y = 0;
        motion->x.w.i = record->tile_x * 0x40 + 0x20;
        motion->y.w.i = record->tile_y * 0x40 + 0x20;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
    }
    }
}

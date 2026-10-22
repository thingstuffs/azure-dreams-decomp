#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

extern void select_sprite_entry(void *, u8, s32);
extern s32 rand(void);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);
extern void spawn_randomized_directional_effect(void *, s16, s32, s32);
extern void create_owner_linked_directional_object(void *, void *, void *);

extern u8 uboat_default_frames[];
extern u8 D_800E2400[];
extern u8 D_80171A80[];

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

typedef struct S_80173510_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80173510_3;   /* arg1 in advance_staged_actor_movement */

/* Updates a staged movement animation and returns the entity to its tile center. */
/* Animates U-Boat's backward windup and forward strike, emits directional particles, applies damage, and
 * spends MP after returning. */
void advance_staged_actor_movement(void *action, void *motion, void *record, ActorRecord *actor)
{
    u8 state;

    state = ((S_80173510_0 *)action)->unk_9B.n;
    switch (state) {

    case 0:
        if (((SpriteFrameState *)record)->flags & 0x8000) {
            u8 *animation_ids;

            ((S_80173510_0 *)action)->unk_9B.n = 5;
            ((S_80173510_0 *)action)->unk_96.u = 0;
            ((SpriteFrameState *)record)->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, record, actor->facing, 1);

            animation_ids = uboat_default_frames;
            ((SpriteFrameState *)record)->frameTable = animation_ids;
            select_sprite_entry(record,
                animation_ids[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            if (((S_80173510_0 *)action)->unk_B0 != 0) {
                return;
            }
            create_owner_linked_directional_object(action, motion, record);
            return;
        }

        ((S_80173510_3 *)motion)->unk_14 = 0;
        ((S_80173510_3 *)motion)->unk_10 = 0;
        ((S_80173510_3 *)motion)->unk_0C = 0;
        ((S_80173510_0 *)action)->unk_96.u = 2;
        ((S_80173510_0 *)action)->unk_98 &= 0xFFF7;
        ((S_80173510_0 *)action)->unk_9B.n++;
        return;

    case 1:
    {
        s16 *direction_x;
        s16 *direction_y;
        u16 timer;

        timer = ((S_80173510_0 *)action)->unk_96.u;
        ((S_80173510_0 *)action)->unk_96.u = timer - 1;
        if ((s16)timer > 0 && !(((SpriteFrameState *)record)->flags & 0x8000)) {
            return;
        }

        ((S_80173510_0 *)action)->unk_96.u = 0x12;
        direction_x = (s16 *)((s8 *)dir_step_x);
        ((S_80173510_0 *)action)->unk_9B.n++;
        direction_y = (s16 *)((s8 *)dir_step_y);
        ((S_80173510_3 *)motion)->unk_0C =
            -*(s16 *)((u8 *)direction_x +
              ((((u16)actor->facing) >> 8) & 0xE)) << 18;
        ((S_80173510_3 *)motion)->unk_10 =
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

        if (((S_80173510_0 *)action)->unk_96.s == 0xB) {
            ((S_80173510_3 *)motion)->unk_0C = 0;
            ((S_80173510_3 *)motion)->unk_10 = 0;
        }

        eight = 8;
        if (((S_80173510_0 *)action)->unk_96.s == eight) {
            u8 *animation_ids;

            animation_ids = D_800E2400;
            ((SpriteFrameState *)record)->frameTable = animation_ids;
            select_sprite_entry(record,
                animation_ids[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                1);

            direction_x = (s16 *)((s8 *)dir_step_x);
            direction_y = (s16 *)((s8 *)dir_step_y);
            ((S_80173510_3 *)motion)->unk_0C =
                *(s16 *)((u8 *)direction_x +
                  ((((u16)actor->facing) >> 8) & 0xE)) << 19;
            ((S_80173510_3 *)motion)->unk_10 =
                *(s16 *)((u8 *)direction_y +
                  ((((u16)actor->facing) >> 8) & 0xE)) << 19;
        }

        entity_kind = ((SpriteFrameState *)record)->unk_04;
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

        timer = ((S_80173510_0 *)action)->unk_96.u;
        ((S_80173510_0 *)action)->unk_96.u = timer - 1;
        if ((s16)timer <= 0 || (((SpriteFrameState *)record)->flags & 0x8000)) {
            ((S_80173510_0 *)action)->unk_96.u = 4;
            ((S_80173510_0 *)action)->unk_9B.n++;
        }

        if (*(u8 * *)&((SpriteFrameState *)record)->frameTable != D_800E2400) {
            return;
        }
        ((SpriteFrameState *)record)->unk_05 = 0;
        return;
    }

    case 3:
    {
        s16 timer;

        timer = ((S_80173510_0 *)action)->unk_96.u - 1;
        ((S_80173510_0 *)action)->unk_96.u = timer;
        if (timer == 3 || (((SpriteFrameState *)record)->flags & 0x8000)) {
            u8 *animation_ids;

            ((S_80173510_3 *)motion)->unk_14 = 0;
            ((S_80173510_3 *)motion)->unk_10 = 0;
            ((S_80173510_3 *)motion)->unk_0C = 0;
            resolve_attack_damage_and_effects(actor, record, actor->facing, 1);

            animation_ids = uboat_default_frames;
            ((SpriteFrameState *)record)->frameTable = animation_ids;
            select_sprite_entry(record,
                animation_ids[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_80173510_0 *)action)->unk_92 = -0x20;
            if (((S_80173510_0 *)action)->unk_B0 == 0) {
                create_owner_linked_directional_object(action, motion, record);
            }
        }

        if (((S_80173510_0 *)action)->unk_96.s > 0 &&
            !(((SpriteFrameState *)record)->flags & 0x8000)) {
            return;
        }
        ((S_80173510_0 *)action)->unk_96.u = 2;
        ((S_80173510_0 *)action)->unk_9B.n++;
        return;
    }

    case 4:
    {
        u16 timer;

        timer = ((S_80173510_0 *)action)->unk_96.u;
        ((S_80173510_0 *)action)->unk_96.u = timer - 1;
        if ((s16)timer > 0 && !(((SpriteFrameState *)record)->flags & 0x8000)) {
            return;
        }
        ((S_80173510_0 *)action)->unk_96.u = 6;
        ((S_80173510_0 *)action)->unk_9B.n++;
        return;
    }

    case 5:
    {
        s32 distance;
        s32 axis_position;
        s16 timer;

        timer = ((S_80173510_0 *)action)->unk_96.s;
        if (timer != 0) {
            distance = ((SpriteFrameState *)record)->unk_24 << 6;
            axis_position = ((S_80173510_3 *)motion)->unk_02;
            axis_position -= 0x20;
            distance -= axis_position;
            ((S_80173510_3 *)motion)->unk_0C = (distance << 16) / timer;

            axis_position = ((S_80173510_3 *)motion)->unk_06;
            distance = ((SpriteFrameState *)record)->unk_25 << 6;
            axis_position -= 0x20;
            distance -= axis_position;
            ((S_80173510_3 *)motion)->unk_10 =
                (distance << 16) / ((S_80173510_0 *)action)->unk_96.s;
        }

        ((S_80173510_0 *)action)->unk_96.u--;
        if (((S_80173510_0 *)action)->unk_96.s > 0 &&
            !(((SpriteFrameState *)record)->flags & 0x8000)) {
            return;
        }

        spend_actor_mp(actor, 0x100);
        ((S_80173510_0 *)action)->unk_8C = D_80171A80;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        ((S_80173510_3 *)motion)->unk_0C = 0;
        ((S_80173510_3 *)motion)->unk_10 = 0;
        ((S_80173510_3 *)motion)->unk_02 = ((SpriteFrameState *)record)->unk_24 * 0x40 + 0x20;
        ((S_80173510_3 *)motion)->unk_06 = ((SpriteFrameState *)record)->unk_25 * 0x40 + 0x20;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
    }
    }
}

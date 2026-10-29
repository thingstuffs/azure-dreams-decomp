#include "shared/actor_status_flags.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"
#include "dungeon/level.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"

typedef struct S_801725D0_1 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_90;   /* overlapping accesses */
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xA];
    s16 unk_A6;
} S_801725D0_1;   /* arg0 in advance_actor_movement_sequence_and_resets */

typedef struct S_801725D0_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801725D0_4;   /* entry in advance_actor_movement_sequence_and_resets */

extern void select_sprite_entry(void *, s32, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void play_sound_if_enabled(s32);


extern void *actor_update_node_cursor;
extern s32 battnel_action_resume_address;
extern u8 D_80173D04[];
extern u8 D_80173D34[];

/* Advances the actor's movement sequence and resets motion and animation on landing. */
void advance_actor_movement_sequence_and_resets(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 direction_offset;
    s32 x_step;
    s32 y_step;
    s32 ticks_left;
    s32 state;
    s32 height_delta;

    direction_offset = (((u16)actor->facing) >> 8) & 0xE;
    x_step = *(s16 *)((u8 *)((s8 *)dir_step_x) + direction_offset);
    ticks_left = action->action_timer.u - 1;
    y_step = *(s16 *)((u8 *)((s8 *)dir_step_y) + direction_offset);
    state = action->action_phase.u;
    action->action_timer.u = ticks_left;

    switch (state) {
    case 0:
        if (sprite->flags & 0x8000) {
            action->action_phase.u = 0xFF;
            sprite->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }

        sprite->frameTable = D_80173D34;
        select_sprite_entry(
            sprite,
            D_80173D34[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);

        if (actor->target != 0) {
            void *linked = actor->target;
            void *height_entry = ((ObjectNodeHeader *)((u8 *)linked - 0x20))->position;
            ((S_801725D0_1 *)action)->unk_A6 = ((S_801725D0_4 *)height_entry)->unk_0A - 0x34;
        } else {
            ((S_801725D0_1 *)action)->unk_A6 =
                sample_terrain_surface_height(
                    ((sprite->tile_x + x_step) << 6) & 0xFFC0,
                    ((sprite->tile_y + y_step) << 6) & 0xFFC0,
                    (s16)(((u16)actor->ground_height) - 0xA0)) - 0x34;
        }
        action->action_timer.u = 2;
        action->action_phase.u++;
        return;

    case 1:
        action->unk_90.parts.high.u +=
            (((S_801725D0_1 *)action)->unk_A6 - motion->z.w.i) / 3;
        if (action->action_timer.s > 0) {
            return;
        }

        action->action_state_flags |= 8;
        actor->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        action->unk_90.parts.high.s = -0x18;
        action->action_timer.u = 4;
        motion->velocity_x =
            (x_step << 22) / action->action_timer.s;
        motion->velocity_y = (y_step << 22) / action->action_timer.s;
        action->action_phase.u++;
        return;

    case 2:
        action->unk_90.value +=
            ((((S_801725D0_1 *)action)->unk_A6 - motion->z.w.i) / 3) << 16;
        if (action->action_timer.s > 0) {
            return;
        }
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        action->action_timer.u = 10;
        action->action_phase.u++;
        return;

    case 3:
        height_delta = ((s32)(ticks_left << 16) >> 4) + 0x2000;
        action->unk_90.value -= height_delta;
        if (action->action_timer.s == 6) {
            play_sound_if_enabled(0x808);
        }
        if (action->action_timer.s == 2) {
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
        }
        if (action->action_timer.s > 0) {
            return;
        }
        motion->velocity_x = (0 - x_step) << 19;
        motion->velocity_y = (0 - y_step) << 19;
        motion->velocity_z = 0xFFF80000;
        action->action_phase.u = 0xFF;
        return;

    case 0xFF:
        motion->velocity_z += 0x18000;
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        action->action_state_flags &= 0xFFF7;
        actor->flags1C |= ACTOR_GROUNDED;
        action->unk_90.value = 0;
        sprite->frameTable = D_80173D04;
        select_sprite_entry(
            sprite,
            D_80173D04[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        spend_actor_mp(actor, 0x100);
        action->unk_8C.address = &battnel_action_resume_address;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        if (actor->pending_turn_updates == 0) {
            actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        } else {
            actor_update_node_cursor = (u8 *)actor - 0x20;
        }

        return;
    }
}

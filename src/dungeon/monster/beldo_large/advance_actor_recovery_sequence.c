#include "shared/audio_commands.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/item.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"

typedef struct S_func_8016C64C_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[6];
    u8 *unk_2C;
} S_func_8016C64C_2;

typedef struct S_func_8016C64C_5 {
    s16 unk_00;
} S_func_8016C64C_5;

extern void select_sprite_entry(void *, u8, s32);
extern void play_sound_if_enabled(s32);
extern void set_record_integer_tile_center(void *, u8, u8);

extern void beldo_large_action_resume_address(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);
extern u8 beldo_large_frame_set_2[];
extern u8 beldo_large_frame_set_5[];
extern u8 beldo_large_frame_set_1[];
extern u8 beldo_large_frame_set_3[];
extern u8 D_80173A20[];
extern u8 D_80173A28[];
extern u8 D_80173A30[];
extern u8 D_80173A38[];
extern u8 D_80175DC0;
extern u8 encounter_recovery_flag;

/* Move the actor back to its tile, update its animation, and advance its recovery state. */
void advance_actor_recovery_sequence(ActorRecord *body, ObjectPosition *motion, S_func_8016C64C_2 *sprite,
    ActorRecord *actor)
{
    s16 target_distance;
    s16 frame_count;
    s32 tile_pos;
    s32 offset_pos;
    u8 *anim_table;
    u8 *current_anim;
    DungeonGlobalStatus *world_state;

    switch (body->action_phase.u) {
    case 0:
        actor->hp_delta = 0;
        body->action_phase.u++;
        encounter_recovery_flag = 0;
        body->action_timer.s = 6;
        if (body->unk_B0.bytes[0] < 2) {
            return;
        }
        actor->facing = get_rounded_facing_and_rounding_flag(
            sprite->unk_24, sprite->unk_25,
            reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &target_distance);
        body->unk_94 = 1;
        return;

    case 1:
        frame_count = --body->action_timer.u;
        if (frame_count > 0) {
            motion->velocity_x =
                ((S_func_8016C64C_5 *)((u8 *)((s8 *)dir_step_x) + ((actor->movement_facing >> 8) & 0xE)))->unk_00 << 18;
            motion->velocity_y =
                ((S_func_8016C64C_5 *)((u8 *)((s8 *)dir_step_y) + ((actor->movement_facing >> 8) & 0xE)))->unk_00 << 18;
            return;
        }
        if (frame_count != 0) {
            return;
        }
        motion->velocity_x =
            ((S_func_8016C64C_5 *)((u8 *)((s8 *)dir_step_x) + ((actor->movement_facing >> 8) & 0xE)))->unk_00 << 18;
        motion->velocity_y =
            ((S_func_8016C64C_5 *)((u8 *)((s8 *)dir_step_y) + ((actor->movement_facing >> 8) & 0xE)))->unk_00 << 18;
        body->action_timer.s = 8;
        body->action_phase.u++;
        return;

    case 2:
        frame_count = body->action_timer.s;
        if (frame_count != 0) {
            tile_pos = sprite->unk_24 << 6;
            offset_pos = motion->x.w.i;
            offset_pos -= 0x20;
            motion->velocity_x =
                ((tile_pos - offset_pos) << 16) / frame_count;
            tile_pos = sprite->unk_25 << 6;
            offset_pos = motion->y.w.i;
            offset_pos -= 0x20;
            motion->velocity_y =
                ((tile_pos - offset_pos) << 16) / body->action_timer.s;
        }
        if (body->action_timer.s-- > 0) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        body->action_phase.u++;

        switch (body->unk_AC.byte) {
        case 0:
            anim_table = beldo_large_frame_set_2;
            if (sprite->unk_2C == anim_table) {
                return;
            }
            sprite->unk_2C = anim_table;
            select_sprite_entry(
                sprite,
                anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            return;
        case 1:
            current_anim = sprite->unk_2C;
            anim_table = beldo_large_frame_set_5;
            if (current_anim == anim_table) {
                return;
            }
            sprite->unk_2C = anim_table;
            select_sprite_entry(
                sprite,
                anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            return;
        case 2:
            current_anim = sprite->unk_2C;
            anim_table = beldo_large_frame_set_1;
            if (current_anim == anim_table) {
                return;
            }
            sprite->unk_2C = anim_table;
            select_sprite_entry(
                sprite,
                anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            return;
        case 3:
            anim_table = beldo_large_frame_set_3;
            if (sprite->unk_2C == anim_table) {
                return;
            }
            sprite->unk_2C = anim_table;
            select_sprite_entry(
                sprite,
                anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            return;
        default:
            return;
        }

    case 3:
        if (encounter_recovery_flag != 0) {
            if (D_80175DC0 == 0) {
                return;
            }
            if (actor->hp == 0) {
                body->action_timer.s = 0;
                body->action_phase.u += 2;
                return;
            }
            body->action_timer.s = 0;
            body->action_phase.u++;
            play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
            return;
        }
        body->action_phase.u += 2;
        return;

    case 4:
        frame_count = ++body->action_timer.u;
        if (frame_count < 0x50) {
            return;
        }
        body->action_phase.u++;
        return;

    case 5:
        if (actor->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            switch (body->unk_AC.byte) {
            case 0:
                begin_actor_display_action(body, motion, sprite, D_80173A20);
                return;
            case 1:
                begin_actor_display_action(body, motion, sprite, D_80173A28);
                return;
            case 2:
                begin_actor_display_action(body, motion, sprite, D_80173A30);
                return;
            case 3:
                begin_actor_display_action(body, motion, sprite, D_80173A38);
                return;
            default:
                return;
            }
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->unk_24, sprite->unk_25);
        world_state = &g_dungeon_status;
        if (((u8 *)world_state->pending_display_owner) == (u8 *)actor - 0x20) {
            (*(u32 *)&world_state->pending_display_owner) &= 0x7FFFFFFF;
        }
        body->unk_8C.byte_ptr = beldo_large_action_resume_address;
        return;
    }
}

#include "shared/entity.h"
#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "dungeon/monster/ghosh.h"
#include "slus.h"
#include "sdk/libc.h"
#include "sdk/libgte.h"
#include "dungeon/system.h"
#include "engine/graphics.h"
#include "engine/texture.h"
#include "dungeon/data.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct {
    s16 x;
    u16 y;
} InitPair;
typedef struct {
    InitPair pair[8];
} __attribute__((packed)) InitBlock;
void create_boss_display_variant(); /* extern */
void create_boss_randomized_effect(); /* extern */
extern InitBlock ghosh_effect_direction_vectors;

/* Byte +0xB6 of the scripted actor's ActorRecord (inside its unk_B4 scratch word): a signed flag the descent clears. */
typedef struct GhoshScriptedFlagView {
    u8 pad_00[0xB6];
    s8 unk_B6;
} GhoshScriptedFlagView;

typedef struct S_func_8132B8AC_1 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[2];
    u16 unk_0A;
    union {
        s32 unk_0C;
        struct { u8 pad_0C[2]; s16 unk_0E; } unk_0E;
    } unk_0C;
    union {
        s32 unk_10;
        struct { u8 pad_10[2]; s16 unk_12; } unk_12;
    } unk_10;
} S_func_8132B8AC_1;

typedef struct S_func_8132B8AC_2 {
    u8 pad_00[4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0x16];
    u8 *unk_2C;
} S_func_8132B8AC_2;

typedef struct S_func_8132B8AC_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_func_8132B8AC_3;

/* Updates Beldo's scripted movement, idle animation, and particle effects. */
/* Runs Beldo's stored flight path, timed turns and particle bursts, then releases the secondary overlay
 * object. */
void advance_scripted_actor_motion(ActorRecord *actor, S_func_8132B8AC_1 *motion, S_func_8132B8AC_2 *sprite) {

    InitBlock direction_vectors;
    s32 path_angle;
    s32 final_direction;
    s16 sprite_direction;
    s16 next_angle;
    s16 spin_timer;
    s16 sprite_angle_base;
    s16 sprite_angle_delta;
    InitPair *start_vector;
    InitPair *path_vector;
    s32 start_direction;
    s32 velocity_x;
    s32 velocity_y;
    s32 position_x;
    s32 position_y;
    s32 path_direction;
    s32 path_particle_count;
    s32 end_particle_count;
    s32 wait_particle_count;
    s32 move_particle_count;
    s32 wait_particle_mode;
    s32 move_particle_mode;
    u16 initial_timer;
    u16 idle_timer;
    u16 final_timer;
    u16 pause_timer;
    u16 rise_timer;
    u16 path_start_timer;
    u16 path_end_timer;
    u16 turn_timer;
    u16 animation_timer;
    u16 particle_timer;
    u16 move_timer;
    u16 bob_phase;
    u16 previous_angle;
    u8 state;
    u8 *path_step;
    u8 *path_start;
    u8 *path_table;
    S_func_8132B8AC_3 *beldo;
    s32 tail_test;
    void *particle_a0;
    s32 particle_color;

    direction_vectors = ghosh_effect_direction_vectors;
    beldo = NODE_BODY(ghosh_scripted_actor);
    advance_sprite_animation_and_textures(sprite);
    state = actor->action_id;
    switch (state) {
    case 0:
        initial_timer = actor->action_timer;
        actor->action_timer = initial_timer + 1;
        if ((s16) initial_timer < 0x1E) {
            break;
        }
        actor->action_timer = 0U;
        actor->action_id = (u8) (actor->action_id + 1);
        motion->unk_0C.unk_0C = 0xFFF80000;
        break;
    case 1:
        motion->unk_00 = (s32) (motion->unk_00 + motion->unk_0C.unk_0C);
        tail_test = (u16)actor->action_timer + 1;
        actor->action_timer = tail_test;
        tail_test = (s16) tail_test < 0x28;
        if (!tail_test) {
            actor->action_timer = 0U;
            actor->action_id = (u8) (actor->action_id + 1);
            motion->unk_0C.unk_0C = 0;
        }
        break;
    case 3:
        sprite->unk_14 = (u16) (sprite->unk_14 & 0xFF7F);
        tail_test = (u16)actor->action_timer + 1;
        pause_timer = (u16) tail_test;
        actor->action_timer = pause_timer;
        tail_test = (s16) tail_test < 0xA;
        if (!tail_test) {
            actor->action_timer = 0U;
            actor->action_id = (u8) (actor->action_id + 1);
            motion->unk_0C.unk_0C = 0;
        }
        break;
    case 5:
        sprite->unk_2C = ghosh_frame_set_5;
        select_sprite_entry(sprite, ghosh_frame_set_5[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + beldo->unk_2A + 0x100) >> 9) & 7], 0);
        play_sound_if_enabled(0x801);
        actor->action_timer = 0U;
        actor->action_id = (u8) (actor->action_id + 1);
        break;
    case 6:
        if (!(sprite->unk_14 & 0x6000)) {
            break;
        }
        ((GhoshScriptedFlagView *)actor)->unk_B6 = 0;
        beldo->unk_88 = (u16) motion->unk_0A;
        if (sprite->unk_2C == ghosh_frame_set_6) {
            break;
        }
        sprite->unk_2C = ghosh_frame_set_6;
        select_sprite_entry(sprite, ghosh_frame_set_6[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + beldo->unk_2A + 0x100) >> 9) & 7], 0);
        actor->action_timer = 0U;
        actor->action_id = (u8) (actor->action_id + 1);
        create_boss_child_effect(actor, motion, sprite);
        break;
    case 7:
        motion->unk_0A = (u16) (motion->unk_0A - 8);
        rise_timer = actor->action_timer + 1;
        actor->action_timer = rise_timer;
        if ((s16) rise_timer < 4) {
            break;
        }
        actor->action_timer = 0U;
        actor->action_id = (u8) (actor->action_id + 1);
        motion->unk_0C.unk_0C = 0;
        actor->unk_9E = 0U;
        actor->unk_A0.parts.high = 0U;
        actor->unk_90.parts.high = -0x20;
        break;
    case 9:
        path_start_timer = actor->action_timer;
        actor->action_timer = path_start_timer + 1;
        if ((s16) path_start_timer < 7) {
            break;
        }
        actor->action_id = (u8) (actor->action_id + 1);
        sprite->unk_2C = ghosh_frame_set_2;
        select_sprite_entry(sprite, ghosh_frame_set_2[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + beldo->unk_2A + 0x100) >> 9) & 7], 0);
        motion->unk_0C.unk_0C = 0xFFF80000;
        actor->unk_B4.halves.low.s = 5;
        actor->action_timer = 0x10U;
        path_start = ghosh_motion_path;
        path_step = path_start + actor->unk_B4.halves.low.s * 2;
        start_direction = path_step[1] & 7;
        start_vector = &direction_vectors.pair[start_direction];
        motion->unk_0C.unk_0E.unk_0E = (s16) (start_vector->x * 0x10);
        motion->unk_10.unk_12.unk_12 = (s16) (start_vector->y * 0x10);
        beldo->unk_2A = (s16) (start_direction << 9);
        break;
    case 10:
        if (actor->action_timer <= 0) {
            path_table = ghosh_motion_path;
            actor->action_timer = (path_table[actor->unk_B4.halves.low.s * 2] * 4) + 1;
            path_direction = path_table[actor->unk_B4.halves.low.s * 2 + 1] & 7;
            path_vector = &direction_vectors.pair[path_direction];
            motion->unk_0C.unk_0E.unk_0E = (s16) (path_vector->x * 0x10);
            motion->unk_10.unk_12.unk_12 = (s16) (path_vector->y * 0x10);
            path_angle = path_direction << 9;
            if (path_angle == beldo->unk_2A) {
                motion->unk_00 = (s32) (motion->unk_00 + motion->unk_0C.unk_0C);
                motion->unk_04 = (s32) (motion->unk_04 + motion->unk_10.unk_10);
                actor->action_timer = actor->action_timer - 1;
            }
            beldo->unk_2A = path_angle;
            if ((path_table[actor->unk_B4.halves.low.s * 2 + 1] & 0xF8) == 0xF8) {
                actor->action_timer = 0x13U;
                actor->action_id = (u8) (actor->action_id + 1);
                motion->unk_00 = (s32) (motion->unk_00 + motion->unk_0C.unk_0C);
                motion->unk_04 = (s32) (motion->unk_04 + motion->unk_10.unk_10);
            }
            actor->unk_B4.halves.low.u = (u16) (actor->unk_B4.halves.low.u + 1);
        } else {
            motion->unk_00 = (s32) (motion->unk_00 + motion->unk_0C.unk_0C);
            motion->unk_04 = (s32) (motion->unk_04 + motion->unk_10.unk_10);
        }
        if (sprite->unk_04 == 5) {
            particle_a0 = sprite;
            sprite->unk_2C = ghosh_frame_set_2;
            select_sprite_entry(particle_a0, ghosh_frame_set_2[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + beldo->unk_2A + 0x100)
                >> 9) & 7], 0);
            path_particle_count = 0;
            play_sound_if_enabled(0x706);
            do {
                create_boss_directional_effect((u8 *)actor - 0x20, beldo->unk_2A, 0x8080FF, (rand() & 0xFF) | 0x80, 0);
                path_particle_count += 1;
            } while (path_particle_count < 0x14);
            actor->action_timer = actor->action_timer - 1;
        } else {
            actor->action_timer = actor->action_timer - 1;
        }
        break;
    case 11:
        motion->unk_00 = (s32) (motion->unk_00 + motion->unk_0C.unk_0C);
        motion->unk_04 = (s32) (motion->unk_04 + motion->unk_10.unk_10);
        if (sprite->unk_04 == 5) {
            sprite->unk_2C = ghosh_frame_set_2;
            select_sprite_entry(sprite, ghosh_frame_set_2[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + beldo->unk_2A + 0x100) >> 9) & 7], 0);
            end_particle_count = 0;
            play_sound_if_enabled(0x706);
            do {
                create_boss_directional_effect((u8 *)actor - 0x20, beldo->unk_2A, 0x8080FF, (rand() & 0xFF) | 0x80, 0);
                end_particle_count += 1;
            } while (end_particle_count < 0x14);
        }
        path_end_timer = actor->action_timer - 1;
        actor->action_timer = path_end_timer;
        if ((path_end_timer << 0x10) > 0) {
            break;
        }
        actor->action_timer = 0x2EU;
        actor->action_id++;
        if (sprite->unk_2C == ghosh_frame_set_6) {
            break;
        }
        sprite->unk_2C = ghosh_frame_set_6;
        select_sprite_entry(sprite, ghosh_frame_set_6[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + beldo->unk_2A + 0x100) >> 9) & 7], 0);
        break;
    case 12:
        turn_timer = actor->action_timer - 1;
        actor->action_timer = turn_timer;
        if ((turn_timer << 0x10) <= 0) {
            actor->action_timer = 6U;
            if (beldo->unk_2A < 0x800) {
                beldo->unk_2A = (s16) (((u16)beldo->unk_2A) + 0x200);
            } else {
                actor->action_timer = 0U;
                actor->action_id = (u8) (actor->action_id + 1);
            }
        }
        if (actor->action_timer == 0x28) {
            beldo->unk_2A = 0xE00;
        }
        if (actor->action_timer == 0x1E) {
            beldo->unk_2A = 0;
        }
        if (actor->action_timer == 0x1D) {
            beldo->unk_2A = 0x200;
        }
        if (actor->action_timer == 0x12) {
            beldo->unk_2A = 0;
        }
        if (actor->action_timer == 0x11) {
            beldo->unk_2A = 0xE00;
        }
        if (actor->action_timer == 0xA) {
            beldo->unk_2A = 0;
        }
        break;
    case 8:
    case 13:
        bob_phase = actor->unk_9E;
        actor->unk_9E = bob_phase + 1;
        actor->unk_A0.value = (s32) (actor->unk_A0.value + (rsin((s16) bob_phase * 0x55) * 0x10));
        motion->unk_0A = (u16) (beldo->unk_88
            + actor->unk_90.parts.high - actor->unk_A0.parts.high);
        break;
    case 14:
        animation_timer = actor->action_timer + 1;
        actor->action_timer = animation_timer;
        if ((s16) animation_timer < 3) {
            break;
        }
        actor->action_timer = 0U;
        actor->action_id++;
        sprite->unk_2C = ghosh_frame_set_2;
        select_sprite_entry(sprite, ghosh_frame_set_2[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + beldo->unk_2A + 0x100) >> 9) & 7], 0);
        break;
    case 15:
        if (sprite->unk_04 == 5) {
            particle_a0 = sprite;
            particle_color = 0;
            sprite->unk_2C = ghosh_frame_set_2;
            sprite_angle_base = g_game_work.view.camera_rotation.parts.viewAngle;
            sprite_angle_delta = beldo->unk_2A;
            select_sprite_entry(particle_a0, ghosh_frame_set_2[((s32) (sprite_angle_base + sprite_angle_delta + 0x100) >> 9) & 7],
                particle_color);
            wait_particle_count = particle_color;
            play_sound_if_enabled(0x706);
            wait_particle_mode = 1;
            do {
                create_boss_directional_effect((u8 *)actor - 0x20, beldo->unk_2A, 0x8080FF, (rand() & 0xFF) | 0x80, wait_particle_mode);
                wait_particle_count += 1;
            } while (wait_particle_count < 0x14);
        }
        particle_timer = actor->action_timer + 1;
        actor->action_timer = particle_timer;
        if ((s16) particle_timer < 0x19) {
            break;
        }
        actor->action_timer = 0U;
        actor->action_id = (u8) (actor->action_id + 1);
        motion->unk_0C.unk_0E.unk_0E = -0x10;
        motion->unk_10.unk_12.unk_12 = 0;
        break;
    case 16:
        move_timer = actor->action_timer + 1;
        actor->action_timer = move_timer;
        if ((s16) move_timer >= 0xA) {
            actor->action_timer = 0U;
            actor->action_id = (u8) (actor->action_id + 1);
            motion->unk_0C.unk_0E.unk_0E = 4;
            motion->unk_10.unk_12.unk_12 = 0;
            create_boss_display_variant(motion, -0x50, 0, -0x10, 0);
            create_boss_display_variant(motion, -0x28, 0, -8, 0);
            create_boss_display_variant(motion, -0x1C, 0, -0x1E, 0);
            initialize_timed_motion_step(6, 0xC);
            play_sound_if_enabled(0x601);
        }
        if (actor->action_timer == 8) {
            create_boss_display_variant(motion, -0x30, 0, -0xA, 1);
            create_boss_display_variant(motion, -0x18, 0, -0x18, 1);
            create_boss_display_variant(motion, 0, 0, -0x10, 1);
            initialize_timed_motion_step(6, 0xC);
            play_sound_if_enabled(0x601);
        }
        motion->unk_00 = (s32) (motion->unk_00 + motion->unk_0C.unk_0C);
        motion->unk_04 = (s32) (motion->unk_04 + motion->unk_10.unk_10);
        if (sprite->unk_04 == 5) {
            particle_a0 = sprite;
            particle_color = 0;
            sprite->unk_2C = ghosh_frame_set_2;
            sprite_angle_base = g_game_work.view.camera_rotation.parts.viewAngle;
            sprite_angle_delta = beldo->unk_2A;
            select_sprite_entry(particle_a0, ghosh_frame_set_2[((s32) (sprite_angle_base + sprite_angle_delta + 0x100) >> 9) & 7],
                particle_color);
            move_particle_count = particle_color;
            play_sound_if_enabled(0x706);
            move_particle_mode = 1;
            do {
                create_boss_directional_effect((u8 *)actor - 0x20, beldo->unk_2A, 0x8080FF, (rand() & 0xFF) | 0x80, move_particle_mode);
                move_particle_count += 1;
            } while (move_particle_count < 0x14);
        }
        break;
    case 17:
        spin_timer = actor->action_timer + 1;
        actor->action_timer = spin_timer;
        if (spin_timer < 0xE) {
            if (!(spin_timer & 1)) {
                previous_angle = (u16) beldo->unk_2A;
                next_angle = previous_angle + 0x200;
                beldo->unk_2A = next_angle;
                if (next_angle >= 0x1000) {
                    beldo->unk_2A = (s16) (previous_angle - 0xE00);
                }
            }
        }
        position_x = motion->unk_00;
        velocity_x = motion->unk_0C.unk_0C;
        position_y = motion->unk_04;
        velocity_y = motion->unk_10.unk_10;
        motion->unk_00 = position_x + velocity_x;
        motion->unk_04 = position_y + velocity_y;
        if ((s16) motion->unk_0A < (s16) beldo->unk_88) {
            motion->unk_0A = (u16) (motion->unk_0A + 6);
        }
        if (actor->action_timer >= 0x13) {
            actor->action_timer = 0U;
            actor->action_id = (u8) (actor->action_id + 1);
            motion->unk_10.unk_12.unk_12 = 0;
            motion->unk_0C.unk_0E.unk_0E = 0;
        }
        if ((actor->action_timer & 3) == 1) {
            create_boss_randomized_effect(motion, -0x10, 0, -4);
            create_boss_randomized_effect(motion, 0xC, 0, -0xC);
        }
        break;
    case 18:
        idle_timer = actor->action_timer + 1;
        actor->action_timer = idle_timer;
        if ((s16) idle_timer >= 0x3C) {
            actor->action_timer = 4U;
            actor->action_id = (u8) (actor->action_id + 1);
            create_boss_linked_effect(actor, motion, sprite);
            sprite->unk_2C = ghosh_frame_set_11;
            select_sprite_entry(sprite, ghosh_frame_set_11[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + beldo->unk_2A + 0x100) >> 9) & 7], 0);
            play_sound_if_enabled(0x800);
        }
        if ((actor->action_timer & 3) == 1) {
            create_boss_randomized_effect(motion, -0x10, 0, -4);
            create_boss_randomized_effect(motion, 0xC, 0, -0xC);
        }
        break;
    case 19:
        final_timer = actor->action_timer - 1;
        actor->action_timer = final_timer;
        if ((final_timer << 0x10) > 0) {
            break;
        }
        actor->action_id++;
        sprite->unk_2C = ghosh_frame_set_1;
        select_sprite_entry(sprite, ghosh_frame_set_1[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + beldo->unk_2A + 0x100) >> 9) & 7], 0);
        break;
    case 20:
        release_secondary_overlay_object();
        break;
    default:
        break;
    }
    if (ghosh_scripted_actor == 0) {
        return;
    }
    final_direction = ((s32) (g_game_work.view.camera_rotation.parts.viewAngle + beldo->unk_2A + 0x100) >> 9) & 7;
    sprite_direction = final_direction;
    if (actor->unk_94 != sprite_direction) {
        select_indirect_table_entry(sprite, sprite->unk_2C[sprite_direction], sprite->unk_04);
        actor->unk_94 = sprite_direction;
    }
    if (dir_sprite_flag[sprite_direction] != 0) {
        tail_test = sprite->unk_14 | 1;
    } else {
        tail_test = sprite->unk_14 & 0xFFFE;
    }
    sprite->unk_14 = (u16) tail_test;
    return;
}

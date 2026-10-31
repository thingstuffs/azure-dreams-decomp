#include "shared/dungeon_status.h"
#include "shared/actor_status_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/player.h"
#include "dungeon/system.h"
#include "dungeon/level.h"

typedef struct S_8008B9FC_1 {
    u8 pad_00[0x8C];
    union { s32 s; void * u; } unk_8C;   /* accessed as both */
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    s8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
} S_8008B9FC_1;   /* arg0 in try_move_player */

   /* callback_obj in try_move_player */

   /* callback_obj_f0 in try_move_player */

typedef struct S_8008B9FC_7_pre {
    s16 unk_00;
    u8 pad_02[0x23A];
} S_8008B9FC_7_pre;   /* the 0x23C bytes before D_80083464 in try_move_player, addressed as D_80083464[-1] */

extern s16 D_80083464[];
extern u8 player_wait_frames[];
extern u8 player_push_start_frames[];
extern u8 player_move_frames[];
extern u8 player_damage_frames[];
extern u8 actor_attack_frames[];
extern u8 player_put_down_frames[];
extern u8 active_actor_command_code[];

#include "engine/graphics.h"
#include "dungeon/item.h"
#include "dungeon/player/motion.h"
#include "dungeon/player/position.h"

extern void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
extern s16 classify_adjacent_tile_height();

/* Update movement state, position, and animation from the movement result. */
void try_move_player(S_8008B9FC_1 *move_state, s32 actor_id, SpriteFrameState *sprite, EntityRec *actor) {
    GameWork *dungeon_state = &g_game_work;
    u8 *alt_anim;
    DungeonGlobalStatus *flags;
    DungeonGlobalStatus *flags_2;
    DungeonGlobalStatus *check_flags;
    s16 move_result;
    u16 direction_index;
    register s32 update_mask;
    s32 actor_flags;
    u16 blocked_ticks;

    move_result = classify_adjacent_tile_height(actor->facing, actor_id, sprite,
                                actor->unk_88, 0x20);
    if (move_result > 0) {
        move_state->unk_9B = 0;
        update_map_cell_flags_with_item_limit(sprite->tile_x, sprite->tile_y, 0x300);
        direction_index = ((u16)actor->facing >> 8) & 0xE;
        {
            u8 x = sprite->tile_x;
            u8 *movement_x = ((u8 *)dir_step_x);
            x = (u8)(x + movement_x[direction_index]);
            sprite->tile_x = x;
        }
        sprite->tile_y =
            (u8)(sprite->tile_y + ((u8 *)dir_step_y)[direction_index]);
        cycle_map_cell_flags(sprite->tile_x, sprite->tile_y, 0x300);
        flags = &g_dungeon_status;
        flags->flags |= 8;
        move_state->unk_8C.s = 0;

        if (move_result != 4) {
            if ((system_update_flags & 2) ||
                (((dungeon_state->buttons & 0x20) != 0) &&
                 ((move_state->unk_A2 & 0x100) == 0) &&
                 check_action_available_without_nearby_actor())) {
                flags->flags |= 0x80;
                if (sprite->frameTable != player_move_frames) {
                    sprite->frameTable = player_move_frames;
                    set_sprite_animation_frame(
                        sprite,
                        player_move_frames[((s32)(dungeon_state->view.camera_rotation.parts.viewAngle +
                                          actor->facing + 0x100) >> 9) & 7],
                        0, 1);
                }
            }
        }

        check_flags = &g_dungeon_status;
        if ((check_flags->flags & 0x80) || (move_result == 1)) {
            process_unflagged_linked_entries_alt(actor->unk_5C);
            process_unflagged_linked_entries(actor->unk_5C);
            if (!(check_flags->flags & 0x80) &&
                ((active_actor_command_code[0] == 8) || (active_actor_command_code[0] == 0))) {
                if (sprite->frameTable != player_push_start_frames) {
                    void *anim_sprite;
                    anim_sprite = sprite;
                    sprite->frameTable = player_push_start_frames;
                    set_sprite_animation_frame(
                        anim_sprite,
                        player_push_start_frames[((s32)(g_game_work.view.camera_rotation.parts.viewAngle +
                                          actor->facing + 0x100) >> 9) & 7],
                        0, 1);
                }
            }
            move_state->unk_9A = 0xF;
            D_80083464[0] = 8;
        } else {
            move_state->unk_98 |= 0xC;
            if (move_result < 4) {
                move_state->unk_A2 |= 1;
            } else if ((move_result == 2) || (move_result == 4)) {
                move_state->unk_9B = 8;
            }
            check_tile_entry_at_adjusted_height(move_state, actor_id, sprite, actor);
            D_80083464[0] = 8;
            if (sprite->frameTable == player_push_start_frames) {
                sprite->flags |= 0x6000;
                update_player_height_step(move_state, actor_id, sprite, actor);
            } else {
                sprite->frameTable = actor_attack_frames;
                set_sprite_animation_frame(
                    sprite,
                    actor_attack_frames[((s32)(g_game_work.view.camera_rotation.parts.viewAngle + actor->facing +
                                      0x100) >> 9) & 7],
                    0, 1);
            }
            move_state->unk_9A = 0x10;
            {
                register EntityRec *flag_actor;
                flag_actor = actor;
                flag_actor->flags1C |= ACTOR_REFRESH_GROUND;
            }
            append_packed_action_record(actor, 8, 0, 0);
            return;
        }
        append_packed_action_record(actor, 8, 0, 0);
        update_mask = 0x40000000;
    } else {
        if (move_result < 0) {
            if ((system_update_flags & 1) ||
                (blocked_ticks = move_state->unk_96 + 1,
                 move_state->unk_96 = blocked_ticks,
                 (s16)blocked_ticks >= 0x15)) {
                begin_player_push(move_state, actor_id, sprite, actor, (s32)move_result);
                if (move_state->unk_9B >= 0x10) {
                    actor->flags1C |= ACTOR_REFRESH_GROUND;
                    return;
                }
            }
            return;
        }

        {
            register void *idle_sprite;
            idle_sprite = sprite;
            ((SpriteAnimationTableView *)idle_sprite)->frame_table = player_wait_frames;
            set_sprite_animation_frame(
                idle_sprite,
                player_wait_frames[((s32)(dungeon_state->view.camera_rotation.parts.viewAngle +
                                  actor->facing + 0x100) >> 9) & 7],
                0, 1);
        }
        move_state->unk_8C.u =handle_player_input;
        return;
    }
    actor_flags = actor->flags1C | update_mask;
    actor->flags1C = actor_flags;
    flags_2 = &g_dungeon_status;
    flags_2->flags |= 0x812;
    clear_pending_item_action_state();
    check_tile_entry_at_adjusted_height(move_state, actor_id, sprite, actor);
    if (!(system_update_flags & 8)) {
        return;
    }

    if (active_actor_command_code[0] == 0xF0) {
        if (sprite->frameTable == player_move_frames) {
            flags_2->movement_frames_left = (s16)flags_2->movement_frames_left >> 1;
            return;
        }
        {
            void *turn_sprite;
            turn_sprite = sprite;
            ((SpriteAnimationTableView *)turn_sprite)->frame_table = player_move_frames;
            set_sprite_animation_frame(
                turn_sprite,
                *(player_move_frames +
                        (((s32)(((S_8008B9FC_7_pre *)D_80083464)[-1].unk_00 +
                                actor->facing + 0x100) >> 9) & 7)),
                0, 1);
        }
        flags_2->movement_frames_left = (s16)flags_2->movement_frames_left >> 1;
        return;
    }

    if (active_actor_command_code[0] == 0xF8) {
        alt_anim = player_push_start_frames + 8;
        move_state->unk_A2 |= 0x100;
        flags_2->activity_counts.parts.pending_action_count = (u16) flags_2->activity_counts.parts.pending_action_count + 1;
        if (sprite->frameTable == alt_anim) {
            flags_2->movement_frames_left = (s16)flags_2->movement_frames_left >> 1;
            return;
        }
        sprite->frameTable = alt_anim;
        set_sprite_animation_frame(
            sprite,
            alt_anim[((s32)(g_game_work.view.camera_rotation.parts.viewAngle + actor->facing +
                                 0x100) >> 9) & 7],
            0, 1);
        flags_2->movement_frames_left = (s16)flags_2->movement_frames_left >> 1;
        return;
    }

    if (active_actor_command_code[0] == 0xE8) {
        sprite->frameTable = player_damage_frames;
        set_sprite_animation_frame(
            sprite,
            player_damage_frames[((s32)(g_game_work.view.camera_rotation.parts.viewAngle + actor->facing +
                              0x100) >> 9) & 7],
            1, 1);
        update_map_cell_flags_with_item_limit(sprite->tile_x, sprite->tile_y, 0x300);
        direction_index = ((u16)actor->facing >> 8) & 0xE;
        sprite->tile_x -= ((s16 *)(void *)((u8 *)dir_step_x))[direction_index / 2] * 2;
        sprite->tile_y -= ((s16 *)(void *)((u8 *)dir_step_y))[direction_index / 2] * 2;
        cycle_map_cell_flags(sprite->tile_x, sprite->tile_y, 0x300);
        flags_2->movement_frames_left = (s16)flags_2->movement_frames_left >> 1;
        return;
    }

    if (active_actor_command_code[0] == 0xE0) {
        sprite->frameTable = player_put_down_frames;
        set_sprite_animation_frame(
            sprite,
            player_put_down_frames[((s32)(g_game_work.view.camera_rotation.parts.viewAngle + actor->facing +
                              0x100) >> 9) & 7],
            1, 1);
        update_map_cell_flags_with_item_limit(sprite->tile_x, sprite->tile_y, 0x300);
        direction_index = ((u16)actor->facing >> 8) & 0xE;
        {
            u8 x = sprite->tile_x;
            u8 *movement_x = ((u8 *)dir_step_x);
            x = (u8)(x - movement_x[direction_index]);
            sprite->tile_x = x;
        }
        sprite->tile_y -= ((u8 *)dir_step_y)[direction_index];
        cycle_map_cell_flags(sprite->tile_x, sprite->tile_y, 0x300);
    }
}

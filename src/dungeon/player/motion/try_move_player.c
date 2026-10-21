#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"


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


typedef struct S_8008B9FC_5 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_8008B9FC_5;   /* callback_obj in try_move_player */

typedef struct S_8008B9FC_6 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_8008B9FC_6;   /* callback_obj_f0 in try_move_player */

typedef struct S_8008B9FC_7_pre {
    s16 unk_00;
    u8 pad_02[0x23A];
} S_8008B9FC_7_pre;   /* the 0x23C bytes before D_80083464 in try_move_player, addressed as D_80083464[-1] */


extern u16 D_80083460[];
extern s16 D_80083464[];
extern u8 player_wait_frames[];
extern u8 D_800DCFB8[];
extern u8 D_800DCFC0[];
extern u8 D_800DCFE8[];
extern u8 D_800DD030[];
extern u8 D_800DD0D0[];
extern u8 active_actor_command_code[];

extern void set_sprite_animation_frame();
extern void begin_player_push();
extern void update_player_height_step();
extern void check_tile_entry_at_adjusted_height();
extern void process_unflagged_linked_entries();
extern void process_unflagged_linked_entries_alt();
extern void cycle_map_cell_flags();
extern void update_map_cell_flags_with_item_limit();
extern s16 classify_adjacent_tile_height();
extern void append_packed_action_record();
extern s32 check_action_available_without_nearby_actor();
extern void clear_pending_item_action_state();

/* Update movement state, position, and animation from the movement result. */
void try_move_player(S_8008B9FC_1 *move_state, s32 actor_id, Rec_D_80082E80 *sprite, EntityRec *actor) {
    GameWork *dungeon_state = &g_game_work;
    u8 *alt_anim;
    u16 *flags;
    u16 *flags_2;
    u16 *check_flags;
    s16 move_result;
    u16 direction_index;
    register s32 update_mask;
    s32 actor_flags;
    u16 blocked_ticks;

    move_result = classify_adjacent_tile_height(actor->facing, actor_id, sprite,
                                actor->unk_88, 0x20);
    if (move_result > 0) {
        move_state->unk_9B = 0;
        update_map_cell_flags_with_item_limit(sprite->unk_24, sprite->unk_25, 0x300);
        direction_index = ((u16)actor->facing >> 8) & 0xE;
        {
            u8 x = sprite->unk_24;
            u8 *movement_x = ((u8 *)dir_step_x);
            x = (u8)(x + movement_x[direction_index]);
            sprite->unk_24 = x;
        }
        sprite->unk_25 =
            (u8)(sprite->unk_25 + ((u8 *)dir_step_y)[direction_index]);
        cycle_map_cell_flags(sprite->unk_24, sprite->unk_25, 0x300);
        flags = D_80083460;
        flags[1] |= 8;
        move_state->unk_8C.s = 0;

        if (move_result != 4) {
            if ((system_update_flags & 2) ||
                (((dungeon_state->buttons & 0x20) != 0) &&
                 ((move_state->unk_A2 & 0x100) == 0) &&
                 check_action_available_without_nearby_actor())) {
                flags[1] |= 0x80;
                if (sprite->unk_2C.as_pu8 != D_800DCFC0) {
                    sprite->unk_2C.as_pu8 = D_800DCFC0;
                    set_sprite_animation_frame(
                        sprite,
                        D_800DCFC0[((s32)(dungeon_state->view.camera_rotation.parts.viewAngle +
                                          actor->facing + 0x100) >> 9) & 7],
                        0, 1);
                }
            }
        }

        check_flags = D_80083460;
        if ((check_flags[1] & 0x80) || (move_result == 1)) {
            process_unflagged_linked_entries_alt(actor->unk_5C);
            process_unflagged_linked_entries(actor->unk_5C);
            if (!(check_flags[1] & 0x80) &&
                ((active_actor_command_code[0] == 8) || (active_actor_command_code[0] == 0))) {
                if (sprite->unk_2C.as_pu8 != D_800DCFB8) {
                    void *anim_sprite;
                    anim_sprite = sprite;
                    sprite->unk_2C.as_pu8 = D_800DCFB8;
                    set_sprite_animation_frame(
                        anim_sprite,
                        D_800DCFB8[((s32)(g_game_work.view.camera_rotation.parts.viewAngle +
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
            if (sprite->unk_2C.as_pu8 == D_800DCFB8) {
                sprite->unk_14.at00_u16.v |= 0x6000;
                update_player_height_step(move_state, actor_id, sprite, actor);
            } else {
                sprite->unk_2C.as_pu8 = D_800DD030;
                set_sprite_animation_frame(
                    sprite,
                    D_800DD030[((s32)(g_game_work.view.camera_rotation.parts.viewAngle + actor->facing +
                                      0x100) >> 9) & 7],
                    0, 1);
            }
            move_state->unk_9A = 0x10;
            {
                register EntityRec *flag_actor;
                flag_actor = actor;
                flag_actor->flags1C |= 0x40000000;
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
                    actor->flags1C |= 0x40000000;
                    return;
                }
            }
            return;
        }

        {
            register void *idle_sprite;
            idle_sprite = sprite;
            ((S_8008B9FC_5 *)idle_sprite)->unk_2C = player_wait_frames;
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
    flags_2 = D_80083460;
    flags_2[1] |= 0x812;
    clear_pending_item_action_state();
    check_tile_entry_at_adjusted_height(move_state, actor_id, sprite, actor);
    if (!(system_update_flags & 8)) {
        return;
    }

    if (active_actor_command_code[0] == 0xF0) {
        if (sprite->unk_2C.as_pu8 == D_800DCFC0) {
            flags_2[2] = (s16)flags_2[2] >> 1;
            return;
        }
        {
            void *turn_sprite;
            turn_sprite = sprite;
            ((S_8008B9FC_6 *)turn_sprite)->unk_2C = D_800DCFC0;
            set_sprite_animation_frame(
                turn_sprite,
                *(u8 *)(D_800DCFC0 +
                        (((s32)(((S_8008B9FC_7_pre *)D_80083464)[-1].unk_00 +
                                actor->facing + 0x100) >> 9) & 7)),
                0, 1);
        }
        flags_2[2] = (s16)flags_2[2] >> 1;
        return;
    }

    if (active_actor_command_code[0] == 0xF8) {
        alt_anim = D_800DCFB8 + 8;
        move_state->unk_A2 |= 0x100;
        flags_2[5]++;
        if (sprite->unk_2C.as_pu8 == alt_anim) {
            flags_2[2] = (s16)flags_2[2] >> 1;
            return;
        }
        sprite->unk_2C.as_pu8 = alt_anim;
        set_sprite_animation_frame(
            sprite,
            alt_anim[((s32)(g_game_work.view.camera_rotation.parts.viewAngle + actor->facing +
                                 0x100) >> 9) & 7],
            0, 1);
        flags_2[2] = (s16)flags_2[2] >> 1;
        return;
    }

    if (active_actor_command_code[0] == 0xE8) {
        sprite->unk_2C.as_pu8 = D_800DCFE8;
        set_sprite_animation_frame(
            sprite,
            D_800DCFE8[((s32)(g_game_work.view.camera_rotation.parts.viewAngle + actor->facing +
                              0x100) >> 9) & 7],
            1, 1);
        update_map_cell_flags_with_item_limit(sprite->unk_24, sprite->unk_25, 0x300);
        direction_index = ((u16)actor->facing >> 8) & 0xE;
        sprite->unk_24 -= ((s16 *)(void *)((u8 *)dir_step_x))[direction_index / 2] * 2;
        sprite->unk_25 -= ((s16 *)(void *)((u8 *)dir_step_y))[direction_index / 2] * 2;
        cycle_map_cell_flags(sprite->unk_24, sprite->unk_25, 0x300);
        flags_2[2] = (s16)flags_2[2] >> 1;
        return;
    }

    if (active_actor_command_code[0] == 0xE0) {
        sprite->unk_2C.as_pu8 = D_800DD0D0;
        set_sprite_animation_frame(
            sprite,
            D_800DD0D0[((s32)(g_game_work.view.camera_rotation.parts.viewAngle + actor->facing +
                              0x100) >> 9) & 7],
            1, 1);
        update_map_cell_flags_with_item_limit(sprite->unk_24, sprite->unk_25, 0x300);
        direction_index = ((u16)actor->facing >> 8) & 0xE;
        {
            u8 x = sprite->unk_24;
            u8 *movement_x = ((u8 *)dir_step_x);
            x = (u8)(x - movement_x[direction_index]);
            sprite->unk_24 = x;
        }
        sprite->unk_25 -= ((u8 *)dir_step_y)[direction_index];
        cycle_map_cell_flags(sprite->unk_24, sprite->unk_25, 0x300);
    }
}

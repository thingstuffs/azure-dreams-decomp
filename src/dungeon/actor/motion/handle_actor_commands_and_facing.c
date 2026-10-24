#include "shared/actor_status_flags.h"

struct SpriteFrameState;
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/sys_flags.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor.h"

extern void select_record_entry_and_value();
extern void request_scene_dispatch_state(s32);
extern void apply_pending_byte_increase();
extern void begin_player_menu_action();
extern s16 resolve_player_input_facing();
extern s32 has_action_input_without_modifier(void);
extern void reset_record_to_state_34();
extern s32 begin_actor_attack();
extern void finish_paralyzed_actor_action();
#include "dungeon/item.h"

#include "dungeon/player/object/action_state.h"

extern s32 lookup_definition_pair_value();
extern void play_sound_if_enabled();
extern s32 generate_random_value(void);

extern u8 player_menu_action_data[];
extern u8 D_8004F5F4[];
extern void *actor_default_frames[];
extern void (*actor_command_handlers[])();
extern u8 active_actor_command_code[];
extern s32 menu_action_argument[];

typedef struct S_80096384_5 {
    u8 unk_00;
    u8 unk_01;
} S_80096384_5;   /* temp_v0_2 in handle_actor_commands_and_facing */

/* Handles actor commands, turns toward the requested direction, and updates the sprite. */
void handle_actor_commands_and_facing(void *actor, s32 actor_id, SpriteFrameState *sprite, ActorRecord *actor_data)
{
    s16 status_value;
    s16 input_angle;
    s32 status_flags;
    s32 turn_angle;
    s32 direction;
    s32 wrapped_angle;
    s32 signed_target;
    s32 signed_angle;
    s32 angle;
    u32 angle_2;
    s32 next_angle;
    s32 action_bit;
    s32 data_flags;
    s32 angle_distance;
    u32 input_flags;
    u16 old_angle;
    u16 actor_flags;
    u16 move_flags;
    u16 tail_flags;
    u8 *flags_ptr;
    S_80096384_5 *command;
    GameWork *input = &g_game_work;
    u16 *flags_page;
    s32 command_flags;
    s32 idle_state = 0x32; /* MATCH: preserve retail register allocation after sharing the internal tails. */
    s32 command_state;

    if (((Rec_func_8008ACDC_arg0 *)actor)->unk_9A.as_u8 != idle_state) {
        sprite->frameTable = actor_default_frames;
        select_record_entry_and_value(sprite,
            *(void **)((u8 *)actor_default_frames +
                ((((s32)(input->view.camera_rotation.parts.viewAngle +
                    actor_data->facing + 0x100)) >> 7) & 0x1C)),
            0);
        ((Rec_func_8008ACDC_arg0 *)actor)->unk_9A.as_u8 = idle_state;
        ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 &= 0xFEFF;
        sprite->flags &= 0xF7FF;
        ((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_s8 = 0;
        ((Rec_func_8008ACDC_arg0 *)actor)->unk_96.as_s16 = 0;
        select_position_data_and_update_owner(sprite, actor_data);
    }

    g_dungeon_status.flags &= 0xFF7F;
    status_value = actor_data->hp_delta;
    if (status_value < 0) {
        run_saved_actor_action(actor, actor_id, sprite, actor_data);
        return;
    }
    if (status_value > 0) {
        apply_pending_byte_increase(actor, actor_id, sprite, actor_data);
    }

    data_flags = actor_data->flags14;
    if (data_flags & 0x20000) {
        actor_data->flags14 = data_flags & 0xFFFDFFFF;
    }

    actor_flags = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2;
    if (!(actor_flags & 0x10)) {
        reset_record_to_state_34(actor, actor_id, sprite, actor_data);
        return;
    }

    status_flags = actor_data->flags1C;
    if (status_flags & 0x200) {
        finish_paralyzed_actor_action(actor, actor_id, sprite, actor_data);
        return;
    }

    if (!(g_dungeon_status.flags & 4)) {
        if (status_flags & 0x20) {
            begin_action_33_and_dispatch(actor, actor_id, sprite, actor_data);
            return;
        }
        flags_page = (u16 *)0x80010000;
        command_flags = flags_page[0x1B8A];
        if (command_flags & 1) {
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = actor_flags & 0xFFFE;
            if (actor_flags & 0x200) {
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = actor_flags & 0xFDFE;
            }

            command = advance_monster_timed_sequence();
            if (command != 0) {
                struct { signed int value : 24; } target_angle = {0};
                direction = command->unk_01 & 7;
                old_angle = ((u16)actor_data->facing);
                if ((s8)direction < 0) {
                    direction = -direction;
                }
                direction &= 0xFF;
                turn_angle = direction << 9;
                target_angle.value = turn_angle;
                angle = old_angle & 0xFFF;
                actor_data->facing = angle;

                if (angle != target_angle.value) {
                    wrapped_angle = old_angle & 0x800;
                    if (!wrapped_angle) {
                        wrapped_angle = old_angle & 0x7FF;
                    } else {
                        wrapped_angle = angle | 0xF800;
                    }
                    actor_data->facing = wrapped_angle;

                    wrapped_angle = turn_angle & 0x800;
                    if (!wrapped_angle) {
                        wrapped_angle = turn_angle & 0x7FF;
                    } else {
                        wrapped_angle = turn_angle | 0xF800;
                    }
                    turn_angle = wrapped_angle;
                    angle = turn_angle << 16;
                    signed_target = angle >> 16;
                    signed_angle = actor_data->facing;
                    angle = ((u16)actor_data->facing);
                    angle_distance = signed_angle - signed_target;
                    if (angle_distance < 0) {
                        angle_distance = 0 - angle_distance;
                    }
                    if (angle_distance >= 0x801) {
                        actor_data->facing = (u16)
                        ((turn_angle & ~0xFFF) | (angle & 0xFFF));
                    }
                    signed_angle = actor_data->facing;
                    angle_2 = ((u16)actor_data->facing);
                    next_angle = signed_target < signed_angle;
                    if (!next_angle) {
                        next_angle = angle_2 + 0x200;
                    } else {
                        next_angle = angle_2 - 0x200;
                    }
                    actor_data->facing = next_angle;
                    read_monster_script_entry();
                } else {
                    active_actor_command_code[0] = command->unk_01 & 0xF8;
                    command_state = active_actor_command_code[0];
                    switch (command_state) {
                    case 8:
                        update_actor_movement_and_map_flags(actor, actor_id, sprite, actor_data);
                        return;
                    case 0x10:
                        begin_action_33_and_dispatch(actor, actor_id, sprite, actor_data);
                        return;
                    case 0x18:
                        begin_actor_attack(actor, actor_id, sprite, actor_data);
                        break;
                    case 0xD8:
                        actor_command_handlers[command->unk_00 & 0x7F]();
                        break;
                    }
                }
            } else {
                return;
            }
        } else {
            active_actor_command_code[0] = 0;
            if (command_flags & 4) {
                request_scene_dispatch_state(3);
                return;
            }

            if ((has_action_input_without_modifier() << 16) != 0) {
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_A4.as_s16 = 0;
            }

            if ((((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0x200) &&
                ((has_pending_actor_or_turn_action(actor_data) << 16) == 0) &&
                !(g_dungeon_status.flags & 4) &&
                ((lookup_definition_pair_value(sprite->tile_x,
                    sprite->tile_y) << 16) != 0)) {
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 &= 0xFDFF;
                begin_player_menu_action(actor, actor_id, sprite, player_menu_action_data);
                return;
            }

            if (input->buttons & 0x80) {
                actor_data->unk_8A = 2;
                menu_action_argument[0] = 2;
                begin_player_menu_action(actor, actor_id, sprite, D_8004F5F4);
                reference_tile_object.selected_item = 0;
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_C8 = 0;
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_104 = 0;
                return;
            }

            flags_ptr = (u8 *)actor + 0xA2;
            if (input->buttons & 3) {
                play_sound_if_enabled(0x506, flags_ptr);
                return;
            }

            input_angle = resolve_player_input_facing(((Rec_func_8008ACDC_arg0 *)actor)->unk_9E,
                flags_ptr, (u8 *)actor_data + 0x2A);
            if (input_angle != 0xFFF) {
                actor_data->facing = input_angle;
                if (!(input->buttons & 0x10)) {
                    move_flags = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2;
                    if (!(move_flags & 0x400)) {
                        ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = move_flags & 0xFFFE;
                        if (actor_data->flags1C & ACTOR_CONFUSED) {
                            actor_data->facing =
                                ((u16)actor_data->facing) +
                                (generate_random_value() & 0xE00);
                        }
                        update_actor_movement_and_map_flags(actor, actor_id, sprite, actor_data);
                        if (((Rec_func_8008ACDC_arg0 *)actor)->unk_9A.as_u8 != 0x32) {
                            return;
                        }
                    } else {
                        ((Rec_func_8008ACDC_arg0 *)actor)->unk_96.as_s16 = 0;
                    }
                } else {
                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_96.as_s16 = 0;
                }
            }

            input_flags = ((u32)input->buttons);
            if ((input_flags & 0x30) == 0x30) {
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 &= 0xFFFE;
                begin_action_33_and_dispatch(actor, actor_id, sprite, actor_data);
                return;
            }

            tail_flags = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2;
            action_bit = tail_flags & 0x40;
            if (action_bit != 0) {
                action_bit = input_flags & 0x40;
                if (action_bit == 0) {
                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = tail_flags & 0xFFBF;
                }
            } else {
                action_bit = input_flags & 0x40;
                if (action_bit != 0) {
                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = tail_flags & 0xFFFE;
                    if ((begin_actor_attack(actor, actor_id, sprite, actor_data) << 16) != 0) {
                        return;
                    }
                }
            }
        }
    }
    tail_flags = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2;
    if (tail_flags & 1) {
        ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = tail_flags & 0xFFFE;
        sprite->frameTable = actor_default_frames;
        select_record_entry_and_value(sprite,
            *(void **)((u8 *)actor_default_frames +
                ((((s32)(g_game_work.view.camera_rotation.parts.viewAngle + actor_data->facing +
                    0x100)) >> 7) & 0x1C)),
            0);
    }
}

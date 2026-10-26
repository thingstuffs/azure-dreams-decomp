/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "engine/menu.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "shared/sys_flags.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "dungeon/item.h"
#include "dungeon/player.h"
#include "dungeon/player/item.h"
#include "dungeon/player/motion.h"
#include "dungeon/player/position.h"
#include "dungeon/player/state.h"

typedef struct S_8008ACDC_4 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x24];
    s16 unk_8A;
} S_8008ACDC_4;   /* arg3 in handle_player_input */

typedef struct S_8008ACDC_6 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_8008ACDC_6;

typedef struct S_8008ACDC_7 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_8008ACDC_7;   /* (void *) case50_bits in handle_player_input */

   /* (void *) case88_index in handle_player_input */

typedef struct S_8008ACDC_9 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_8008ACDC_9;

void func_8002534C(); /* extern */
void try_move_player(); /* extern */
void begin_player_jump(); /* extern */
s32 try_begin_lift_object(struct S_8008C5C4_2 *action, void *unused, SpriteAnimationTableView *position, EntityRec *actor);  /* extern */
void apply_pending_byte_increase(); /* extern */
void begin_parameterized_actor_action(); /* extern */
s32 resolve_player_input_facing(s16 direction_offset, u16 *flags, u16 *angle);             /* extern */
s32 request_familiar_deployment_change(); /* extern */
#include "dungeon/player/input.h"
s32 dispatch_selected_item_use(Rec_func_8008ACDC_arg0 *actor, s16 item_id, s16 other_item_id);                /* extern */
void resolve_familiar_deployment_request(); /* extern */


void *select_item_record_pointer(); /* Unprototyped: one or two arguments; the second register argument is ignored. */                      /* extern */
s32 can_entity_gain_level(void *entity);                  /* extern */
void set_record_integer_tile_center(ObjectPosition *record, s32 tile_x, s32 tile_y);              /* extern */
#include "dungeon/player/object/action_state.h"
#include "engine/graphics.h"
#include "engine/resource.h"
struct S_8008C5C4_2;
              /* extern */
s32 lookup_definition_pair_value(s16 firstKey, s16 secondKey);                          /* extern */
s32 generate_random_value(void);                      /* extern */
extern M2C_UNK player_menu_action_data;
void submit_enabled_saved_display_value(void);
extern u8 player_wait_frames[8];
extern u8 player_landing_frame_set[];
extern M2C_UNK D_800DD148;
extern void (*actor_command_handlers[])(void);
extern u8 active_actor_command_code;
extern s8 dungeon_button_latch[9];
extern s32 menu_action_argument;

/* Handles actor commands, movement, and facing updates. */
void handle_player_input(void *actor, void *motion, register void *sprite, void *stats) {
    s16 input_angle;
    s16 status_count;
    s32 target_angle;
    s32 requested_angle;
    s32 normalized;
    s32 angle_bits;
    s32 signed_target;
    s32 angle_or_flags;
    u32 angle_raw;
    s32 angle_delta;
    u16 old_angle;
    u16 idle_ticks;
    u16 action_flags;
    u16 move_flags;
    u16 button_flags;
    u16 turn_flags;
    s32 next_angle;
    u16 *flags_page;
    s32 input_flags;
    s32 slot_addr;
    void *selected_target;
    u8 mode_cmd;
    u8 spell_cmd;
    u8 order_cmd;
    u8 item_cmd;
    u8 action_state;
    void *command;
    void *target;
    void *action_actor;
    void *call_actor;
    void *call_motion;
    void *call_sprite;
    u32 button_bits;
    GameWork *input;

    input = &g_game_work;
    action_state = ((Rec_func_8008ACDC_arg0 *)actor)->unk_9A.as_u8;
    if (action_state != 0xE) {
        if (action_state != 0x17) {
            if (((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0x100) {
                begin_wake_nearby_monsters(actor, (s32)motion, sprite, stats);
                return;
            }
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_9A.as_u8 = 0xEU;
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = (u16) (((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0xFEFF);
            ((SpriteFrameState *)sprite)->flags = (u16) (((SpriteFrameState *)sprite)->flags & 0xF7FF);
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_9B.as_s8 = 0;
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_A4.as_u16 = 0U;
            ((ObjectPosition *)motion)->velocity_y = 0;
            ((ObjectPosition *)motion)->velocity_x = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->tile_x, ((SpriteFrameState *)sprite)->tile_y);
        }
        ((Rec_func_8008ACDC_arg0 *)actor)->unk_96.as_s16 = 0;
        select_position_data_and_update_owner(sprite, stats);
    }
    g_dungeon_status.flags = (u16) (g_dungeon_status.flags & 0xFF7F);
    status_count = ((S_8008ACDC_4 *)stats)->unk_64;
    if ((status_count < 0) || (((Rec_func_8008ACDC_arg0 *)actor)->unk_10C & 1)) {
        begin_player_damage_reaction(actor, motion, sprite, stats);
        return;
    }
    if (status_count > 0) {
        apply_pending_byte_increase(actor, motion, sprite, stats);
    }
    if (((S_8008ACDC_4 *)stats)->unk_14 & 0x20000) {
        begin_actor_turn_toward_target(actor, motion, sprite, stats);
        return;
    }
    if (!(((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0x10)) {
        select_state_16_directional_animation(actor, motion, sprite, stats);
        return;
    }
    if (((S_8008ACDC_4 *)stats)->unk_1C & 0x200) {
        begin_player_sleep_action(actor, motion, sprite, stats);
        return;
    }
    if (((can_entity_gain_level(stats) << 0x10) == 0) || (begin_selected_target_level_up(actor, motion, sprite, stats) == 0)) {
        action_flags = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2;
        if (action_flags & 0x80) {
            begin_player_pickup_animation(actor, motion, sprite, stats);
            return;
        }
        switch (g_dungeon_status.flags & 4) {
        case 0:
            if (((S_8008ACDC_4 *)stats)->unk_1C & 0x20) {
                if (!((*(u16 *)0x80013714) & 1) && (((u32)input->buttons) & 0x80)) {
                    ((S_8008ACDC_4 *)stats)->unk_8A = 2;
                    menu_action_argument = 2;
                    begin_player_menu_action(actor, motion, sprite, &D_8004F5F4);
                    reference_tile_object.selected_item = 0;
                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_C8 = 0;
                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_104 = 0;
                    return;
                }
                begin_player_wait_turn(actor, motion, sprite, stats);
                return;
            }
            flags_page = (u16 *) 0x80010000;
            input_flags = flags_page[0x1B8A];
            if (input_flags & 1) {
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = (u16) (action_flags & 0xFFFE);
                if (action_flags & 0x200) {
                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = (u16) (action_flags & 0xFDFE);
                    command = advance_monster_timed_sequence();
                    if (command == NULL) {
                        return;
                    }
                    normalized = ((S_8008ACDC_6 *)command)->unk_01 & 7;
                    old_angle = ((S_8008ACDC_4 *)stats)->unk_2A.s;
                } else {
                    command = advance_monster_timed_sequence();
                    if (command == NULL) {
                        return;
                    }
                    normalized = ((S_8008ACDC_6 *)command)->unk_01 & 7;
                    old_angle = ((S_8008ACDC_4 *)stats)->unk_2A.s;
                }
                normalized &= 0xFF;
                target_angle = normalized << 9;
                angle_bits = old_angle & 0xFFF;
                requested_angle = ((u32)normalized << 10) >> 1;
                ((S_8008ACDC_4 *)stats)->unk_2A.s = angle_bits;
                if (angle_bits != requested_angle) {
                    normalized = old_angle & 0x800;
                    if (!normalized) {
                        normalized = old_angle & 0x7FF;
                    } else {
                        normalized = angle_bits | 0xF800;
                    }
                    ((S_8008ACDC_4 *)stats)->unk_2A.s = normalized;
                    normalized = target_angle & 0x800;
                    if (!normalized) {
                        normalized = target_angle & 0x7FF;
                    } else {
                        normalized = target_angle | 0xF800;
                    }
                    target_angle = normalized;
                    angle_raw = target_angle << 16;
                    signed_target = (s32)angle_raw >> 16;
                    angle_or_flags = ((S_8008ACDC_4 *)stats)->unk_2A.u;
                    angle_raw = ((S_8008ACDC_4 *)stats)->unk_2A.s;
                    angle_delta = angle_or_flags - signed_target;
                    if (angle_delta < 0) {
                        angle_delta = 0 - angle_delta;
                    }
                    if (angle_delta >= 0x801) {
                        ((S_8008ACDC_4 *)stats)->unk_2A.s = (u16) ((target_angle & ~0xFFF) | (angle_raw & 0xFFF));
                    }
                    angle_or_flags = ((S_8008ACDC_4 *)stats)->unk_2A.u;
                    angle_raw = ((S_8008ACDC_4 *)stats)->unk_2A.s;
                    next_angle = signed_target < angle_or_flags;
                    if (!next_angle) {
                        next_angle = angle_raw + 0x200;
                    } else {
                        next_angle = angle_raw - 0x200;
                    }
                    ((S_8008ACDC_4 *)stats)->unk_2A.s = next_angle;
                    read_monster_script_entry();
                } else {
                    active_actor_command_code = (u8) (((S_8008ACDC_6 *)command)->unk_01 & 0xF8);
                    switch (active_actor_command_code) {
                    default:
                        return;
                    case 0x08:
                    case 0xE0:
                    case 0xE8:
                    case 0xF0:
                    case 0xF8:
                        action_actor = actor;
                        try_move_player(action_actor, motion, sprite, stats);
                        return;
                    case 0x10:
                        begin_player_wait_turn(actor, motion, sprite, stats);
                        return;
                    case 0x18:
                        begin_front_tile_attack(actor, motion, sprite, stats);
                        return;
                    case 0x20:
                        try_begin_lift_object(actor, motion, sprite, stats);
                        return;
                    case 0x30:
                        begin_player_jump(actor, motion, sprite, stats);
                        return;
                    case 0x48:
                        if ((s16) dispatch_selected_item_use(actor, ((S_8008ACDC_6 *)command)->unk_00 & 0x1F,
                            ((S_8008ACDC_6 *)command)->unk_02 & 0x1F) < 0) {
                            read_monster_script_entry();
                            return;
                        }
                        initialize_monster_script_counter();
                        return;
                    case 0x50:
                    {
                        u8 target_cmd;
                        s32 target_slot_addr;
                        s32 action_kind;
                        void *slot_target;

                        target_cmd = ((S_8008ACDC_6 *)command)->unk_00;
                        target_slot_addr = target_cmd & 0x60;
                        command = (void *) ((u32) target_slot_addr >> 5);

                        action_kind = 0x15;

                        if (dispatch_dungeon_category_action(((S_8008ACDC_7 *)((((s32)command << 2) + (long)actor)))->unk_AC,
                            select_item_record_pointer(target_cmd & 0x1F), action_kind, 0) >= 0) {
                            return;
                        }
                    }
                        read_monster_script_entry();
                        return;
                    case 0x58:
                        begin_holding_item(actor, motion, sprite, select_item_record_pointer(((S_8008ACDC_6 *)command)->unk_00 & 0x1F));
                        return;
                    case 0x68:
                        selected_target = select_item_record_pointer(((S_8008ACDC_6 *)command)->unk_00 & 0x1F);
                        call_actor = actor;
                        call_motion = motion;
                        call_sprite = sprite;
                        angle_bits = (s32)(((S_8008ACDC_6 *)command)->unk_00);
                        target = selected_target;
                        angle_bits = (s32)(((u32)angle_bits) & (0x60));
                        angle_bits = (s32)(((u32)angle_bits) >> (5));
                        request_familiar_deployment_change(call_actor, call_motion, call_sprite, target, (u32)angle_bits);
                        return;
                    case 0x88:
                        call_actor = actor;
                        angle_bits = ((S_8008ACDC_6 *)command)->unk_00;
                        angle_bits &= 0x60;
                        angle_bits = (u32)angle_bits >> 5;
                        call_motion = motion;
                        slot_addr = (u32)angle_bits << 2;
                        slot_addr = slot_addr + (s32) call_actor;
                        target = (void *) ((FamiliarItemSlotView *)((void *) slot_addr))->item_address;
                        call_sprite = sprite;
                        request_familiar_deployment_change(call_actor, call_motion, call_sprite, target, (u32)angle_bits);
                        return;
                    case 0x70:
                        mode_cmd = ((S_8008ACDC_6 *)command)->unk_00;
                        set_linked_actor_octant_facing((u32) (mode_cmd & 0x60) >> 5, mode_cmd & 7);
                        return;
                    case 0x78:
                        item_cmd = ((S_8008ACDC_6 *)command)->unk_00;
                        set_linked_actor_code_and_mirror((u32) (item_cmd & 0x60) >> 5, item_cmd & 0x1F);
                        return;
                    case 0x80:
                        spell_cmd = ((S_8008ACDC_6 *)command)->unk_00;
                        set_linked_actor_pending_halfword((u32) (spell_cmd & 0x60) >> 5, spell_cmd & 0x1F);
                        return;
                    case 0x90:
                        order_cmd = ((S_8008ACDC_6 *)command)->unk_00;
                        set_familiar_formation_offset((u32) (order_cmd & 0x60) >> 5, order_cmd & 7);
                        return;
                    case 0x98:
                        target = select_item_record_pointer(((S_8008ACDC_6 *)command)->unk_00 & 0x1F, old_angle);
                        if (((S_8008ACDC_9 *)target)->unk_03 & 0x20) {
                            resolve_familiar_deployment_request(actor, motion, sprite, target);
                        } else {
                            begin_familiar_summoning(actor, motion, sprite, target);
                        }
                        return;
                    case 0xA0:
                        func_8002534C(actor, motion, sprite, stats);
                        return;
                    case 0xC8:
                        ((Rec_func_8008ACDC_arg0 *)actor)->unk_96.as_s16 =
                            (s16) (((S_8008ACDC_6 *)command)->unk_00 & 0x7F);
                        begin_parameterized_actor_action(actor, motion, sprite, &D_800DD148, 2);
                        return;
                    case 0xD8:
                        actor_command_handlers[((S_8008ACDC_6 *)command)->unk_00 & 0x7F]();
                        return;
                    }
                }
            } else {
                active_actor_command_code = 0;
                if (input_flags & 4) {
                    if ((*(u8 *)dungeon_button_latch) == 0) {
                        (*(s8 *)dungeon_button_latch) = 1;
                        request_scene_dispatch_state(3);
                        return;
                    }
                    return;
                } else {
                    if ((has_action_input_without_modifier() << 0x10) != 0) {
                        ((Rec_func_8008ACDC_arg0 *)actor)->unk_A4.as_u16 = 0U;
                    }
                    if ((((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0x200) && ((has_pending_actor_or_turn_action(stats) << 0x10) == 0)
                        && !(g_dungeon_status.flags & 4)) {
                        ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 =
                            (u16) (((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0xFDFF);
                        if ((lookup_definition_pair_value(((SpriteFrameState *)sprite)->tile_x, ((SpriteFrameState *)sprite)->tile_y) << 0x10)
                            != 0) {
                            begin_player_menu_action(actor, motion, sprite, &player_menu_action_data);
                            return;
                        }
                    }
                    if (((u32)input->buttons) & 0x80) {
                        begin_player_menu_action(actor, motion, sprite, &submit_enabled_saved_display_value);
                        return;
                    }
                    if ((((u32)input->buttons) & 0x10) || !(((u32)input->buttons) & 3)
                        || (begin_familiar_command_selection(actor, motion, sprite, (((u32) ((u32)input->buttons) >> 1) ^ 1) & 1, 0)
                        == 0)) {
                        input_angle = resolve_player_input_facing(((Rec_func_8008ACDC_arg0 *)actor)->unk_9E, actor + 0xA2, stats
                            + 0x2A);
                        if (input_angle != 0xFFF) {
                            ((S_8008ACDC_4 *)stats)->unk_2A.s = (u16) input_angle;
                            if (!(((u32)input->buttons) & 0x10)) {
                                move_flags = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2;
                                if (!(move_flags & 0x400)) {
                                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = (u16) (move_flags & 0xFFFE);
                                    if (((S_8008ACDC_4 *)stats)->unk_1C & 0x400) {
                                        ((S_8008ACDC_4 *)stats)->unk_2A.s =
                                            (u16) (((S_8008ACDC_4 *)stats)->unk_2A.s + (generate_random_value() & 0xE00));
                                    }
                                    try_move_player(actor, motion, sprite, stats);
                                    if (((Rec_func_8008ACDC_arg0 *)actor)->unk_9A.as_u8 != 0xE) {
                                        return;
                                    }
                                } else {
                                    ((Rec_func_8008ACDC_arg0 *)actor)->unk_96.as_s16 = 0;
                                }
                            } else {
                                ((Rec_func_8008ACDC_arg0 *)actor)->unk_96.as_s16 = 0;
                            }
                        }
                        button_bits = ((u32)input->buttons);
                        if ((button_bits & 0x30) == 0x30) {
                            ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 =
                                (u16) (((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0xFFFE);
                            begin_player_wait_turn(actor, motion, sprite, stats);
                            return;
                        }
                        button_flags = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2;
                        angle_or_flags = button_flags & 0x40;
                        if (angle_or_flags != 0) {
                            angle_or_flags = button_bits & 0x40;
                            if (angle_or_flags == 0) {
                                ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = (u16) (button_flags & 0xFFBF);
                            }
                        } else {
                            angle_or_flags = button_bits & 0x40;
                            if (angle_or_flags != 0) {
                                (*(u16 *)((u8 *)actor + 0xA2)) = (u16) (button_flags & 0xFFFE);
                                if (!(((u32)input->buttons) & 0x20)) {
                                    if ((begin_front_tile_attack(actor, motion, sprite, stats) << 0x10) != 0) {
                                        break;
                                    }
                                    return;
                                }
                                if (try_begin_lift_object(actor, motion, sprite, stats) != 0) {
                                    return;
                                }
                            }
                        }
                        if ((*(u16 *)0x80013714) & 9) {
                            ((Rec_func_8008ACDC_arg0 *)actor)->unk_A4.as_u16 = 0U;
                        }
                        if (((Rec_func_8008ACDC_arg0 *)actor)->unk_9A.as_u8 == 0xE) {
                            idle_ticks = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A4.as_u16 + 1;
                            ((Rec_func_8008ACDC_arg0 *)actor)->unk_A4.as_u16 = idle_ticks;
                            if ((s16) idle_ticks >= 0x3D) {
                                ((Rec_func_8008ACDC_arg0 *)actor)->unk_A4.as_u16 = 0x3CU;
                                enter_directional_state_17(actor, motion, sprite, stats);
                                return;
                            }
                        }
                    } else {
                        return;
                    }
                }
            }
        default:
            turn_flags = ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2;
            if (turn_flags & 1) {
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 = (u16) (turn_flags & 0xFFFE);
                (*(u8 **)((u8 *)sprite + 0x2C)) = player_landing_frame_set;
                set_sprite_animation_frame(sprite, player_landing_frame_set[((s32) (g_game_work.view.camera_rotation.parts.viewAngle
                    + (s16) ((S_8008ACDC_4 *)stats)->unk_2A.s + 0x100) >> 9) & 7], 0, 1);
            }
        }
        if (((SpriteFrameState *)sprite)->flags & 0xE000) {
            (*(u8 **)((u8 *)sprite + 0x2C)) = player_wait_frames;
            set_sprite_animation_frame(sprite, player_wait_frames[((s32) (g_game_work.view.camera_rotation.parts.viewAngle
                + (s16) ((S_8008ACDC_4 *)stats)->unk_2A.s + 0x100) >> 9) & 7], 0, 1);
        }
    }
    return;
}

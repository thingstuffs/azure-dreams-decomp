#include "dungeon/menu/select.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/menu/select.h"

void func_80025014(void *motion_state, void *position, void *draw_state) {
    s16 move_ticks;
    s32 target_y;
    s16 ticks_left;
    void *target_pos;
    void *target_node;
    void *owner;
    s32 current_y;
    s32 node_index;
    s16 *update_counts;
    s16 blink_ticks;
    u16 blink_remaining;

    owner = (*(void **)((u8 *)motion_state + 0));
    node_index = ((S_81809800_0 *)owner)->unk_26;
    update_counts = D_8002715C;
    target_node = ((S_81809800_1 *)(((node_index * 4) + owner)))->unk_0C;
    current_y = ((S_81809800_2 *)position)->unk_00.at02.v;
    target_pos = ((S_81809800_3 *)target_node)->unk_08;
    target_y = ((S_81809800_4 *)target_pos)->unk_00.at02.v;
    update_counts[0] = (s16) ((u16) update_counts[0] + 1);
    if ((target_y != current_y) || (((S_81809800_4 *)target_pos)->unk_04.at02.v
        != ((S_81809800_2 *)position)->unk_04.at02.v)) {
        ((EntityRec *)motion_state)->z.w.i = 2;
    }
    move_ticks = ((EntityRec *)motion_state)->z.w.i;
    if (move_ticks != 0) {
        ((S_81809800_2 *)position)->unk_00.at00.v = (s32) (((S_81809800_2 *)position)->unk_00.at00.v
            + ((s32) (((S_81809800_4 *)target_pos)->unk_00.at00.v
            - ((S_81809800_2 *)position)->unk_00.at00.v) / move_ticks));
        ((S_81809800_2 *)position)->unk_04.at00.v = (s32) (((S_81809800_2 *)position)->unk_04.at00.v
            + ((s32) (((S_81809800_4 *)target_pos)->unk_04.at00.v
            - ((S_81809800_2 *)position)->unk_04.at00.v) / (s16) ((EntityRec *)motion_state)->z.w.i));
        ticks_left = (u16) ((EntityRec *)motion_state)->z.w.i - 1;
        ((EntityRec *)motion_state)->z.w.i = ticks_left;
        if ((ticks_left << 0x10) <= 0) {
            ((S_81809800_2 *)position)->unk_00.at02.v = (s16) (u16) ((S_81809800_4 *)target_pos)->unk_00.at02.v;
            ((S_81809800_2 *)position)->unk_04.at02.v = (s16) (u16) ((S_81809800_4 *)target_pos)->unk_04.at02.v;
            ((EntityRec *)motion_state)->z.w.i = 0;
        }
    }
    func_800478B8(draw_state, target_y, target_pos, position);
    blink_ticks = (*(s16 *)selection_blink_timer);
    blink_remaining = *(u16 *)&(*(s16 *)selection_blink_timer);
    if (blink_ticks != 0) {
        *(u16 *)&(*(s16 *)selection_blink_timer) = (u16) (blink_remaining - 1);
    }
    if ((*(u16 *)&(*(s16 *)selection_blink_timer)) & 1) {
        ((S_81809800_6 *)draw_state)->unk_14 = (u16) (((S_81809800_6 *)draw_state)->unk_14 | 0x80);
    } else {
        ((S_81809800_6 *)draw_state)->unk_14 = (u16) (((S_81809800_6 *)draw_state)->unk_14 & 0xFF7F);
    }
}
#include "dungeon/menu/select.h"

void *allocate_sprite_data_object(s32 user_data) {
    SpriteFrameState *sprite;
    S_80025170_0 *object;

    object = func_8003FC64(0x12);
    if (object != NULL) {
        sprite = object->unk_0C;
        object->unk_10 = (void *)func_80025014;
        func_8003DB94(sprite, &D_80079444, 0);
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->color.word = 0x2C808080;
        sprite->tpage_abr = 0x20;
        sprite->flags = (u16) (sprite->flags | 0xC);
        object->unk_20 = user_data;
    }
    return object;
}
#include "dungeon/menu/select.h"

void update_selection_menu_animation(void *menu_in, void *motion_in, void *appearance_in) {
    s32 *side_ptr;
    u16 target_y;
    u16 entry_counter;
    void *side_data;
    s16 exit_ticks;
    s16 selected_side;
    s16 turn_ticks;
    s16 enter_left;
    s16 turn_left;
    s32 exit_left;
    s32 state;
    s32 step_index;
    s16 wrap_side;
    s32 x_in_bounds;
    u16 *other_dir_dst;
    u16 *other_dir_src;
    u16 *wrapped_dir_src;
    u16 *other_dir;
    u16 *next_dir_dst;
    u16 scale_y;
    u16 scale_z;
    u16 enter_scale;
    u16 exit_scale;
    u32 target_x;
    u32 input_angle;
    u8 exit_shade;
    u8 faded_shade;
    u8 enter_shade;
    u8 lit_shade;
    void **other_slot;
    void **other_slot_data;
    void **first_slot;
    S_8002520C_1 *motion;
    S_8002520C_14 *actor;
    void *side_object;
    s32 side_count;
    void *side_cursor;
    GameWork *state_base;
    S_8002520C_2 *appearance;
    u8 *direction_page;
    s32 *world_page;
    void *menu = menu_in;
    void *motion_data = motion_in;

    entry_counter = D_8002715C[0];
    D_8002715C[0] = entry_counter + 1;
    motion = motion_data;
    appearance = appearance_in;
    state_base = &g_game_work;
    state = ((S_8002520C_0 *)menu)->unk_1C;
    switch ((u32)state) {
    case 0:
        register_node(menu - 0x20, &render_three_by_three_terrain_grid);
        motion->unk_02 = -0x180;
        motion->unk_06 = -0x20;
        appearance->unk_16 = 0x1000U;
        appearance->unk_1E = 0x1000U;
        appearance->unk_1C = 0x1000U;
        ((S_8002520C_0 *)menu)->unk_22 = 8;
        ((S_8002520C_0 *)menu)->unk_1C = (s16) ((u16) ((S_8002520C_0 *)menu)->unk_1C + 1);
                    /* fallthrough */
    case 1:
        side_data = (void *)(((S_8002520C_0 *)menu)->unk_22);
        if (((s16)side_data) != 0) {
            motion->unk_02 = (s16) ((u16) motion->unk_02 + ((s32) (-0x80 - motion->unk_02) / ((s16)side_data)));
            motion->unk_0A.s = (s16) (func_800644B8(((S_8002520C_0 *)menu)->unk_22 << 5) + 0x400);
            enter_scale = appearance->unk_16;
            appearance->unk_16 = (u16) (enter_scale + ((s32) (0xD00
                - enter_scale) / (s16) ((S_8002520C_0 *)menu)->unk_22));
            enter_shade = appearance->unk_0E;
            lit_shade = enter_shade + ((s32) (0x80 - enter_shade) / (s16) ((S_8002520C_0 *)menu)->unk_22);
            appearance->unk_0E = lit_shade;
            appearance->unk_0D = lit_shade;
            appearance->unk_0C = lit_shade;
        }
        enter_left = (u16) ((S_8002520C_0 *)menu)->unk_22 - 1;
        ((S_8002520C_0 *)menu)->unk_22 = enter_left;
        if ((enter_left << 0x10) <= 0) {
            motion->unk_02 = -0x80;
            motion->unk_06 = -0x20;
            motion->unk_0A.s = 0x400;
            appearance->unk_16 = 0xD00U;
            appearance->unk_0E = 0x80U;
            appearance->unk_0D = 0x80U;
            appearance->unk_0C = 0x80U;
            ((S_8002520C_0 *)menu)->unk_22 = 0;
            ((S_8002520C_0 *)menu)->unk_1C = (s16) ((u16) ((S_8002520C_0 *)menu)->unk_1C + 1);
            case 2:
        }
        if (selection_blink_timer[0] == 0) {
            S_8002520C_6 *cell;
            input_angle = resolve_player_input_facing(((u16) appearance->unk_1A >> 9) & 7,
                ((EntityRec *)(((u8 *)(&dungeon_actor_ring_anchor))))->x.v + 0xA2, 0) & 0xFFFF;
            if ((input_angle != 0xFFF) && (((s32)state_base->pressed_buttons) & 0xF000)) {
                s32 step_or_cell;
                s32 side_index;
                u16 *x_step_ptr;
                u32 base_x;
                u16 x_value;
                u32 y_value;
                s32 compare_x;

                {

                    input_angle = input_angle >> 9;
                    side_index = ((S_8002520C_0 *)menu)->unk_26;
                    step_index = input_angle & 7;
                }
                step_or_cell = step_index * 2;
                side_object = ((S_8002520C_22 *)(((side_index * 4) + menu)))->unk_0C;
                side_data = side_object + 0x20;
                cell = ((S_8002520C_5_pre *)side_data)[-1].unk_00;
                {
                    s32 step_value;
                    s32 cell_coord;

                    x_step_ptr = (u16 *) (step_or_cell + ((s32)((s32) ((u16 *)dir_step_x))));
                    step_value = *x_step_ptr;
                    cell_coord = cell->unk_24;
                    base_x = cell_coord + step_value;
                    step_value = (s32) ((u16 *)dir_step_y);
                    step_or_cell += step_value;
                    cell_coord = cell->unk_25;
                    step_value = *(u16 *) step_or_cell;
                    y_value = cell_coord + step_value;
                }
                target_y = (u16) y_value;

                x_value = base_x;
                compare_x = x_value & 0xFFFF;
                if (compare_x == 1) {
                    if ((y_value & 0xFFFF) == compare_x) {
                        s32 next_y;
                        s32 x_step;

                        x_step = *x_step_ptr;
                        next_y = *(u16 *) step_or_cell;
                        x_value = x_step + base_x;
                        target_y = (u16)(y_value + next_y);
                    }
                    first_slot = menu + 0xC;
                } else {
                    first_slot = menu + 0xC;
                }
                step_or_cell = ((S_8002520C_0 *)menu)->unk_26;
                other_slot = first_slot;
                if (step_or_cell == 0) {
                    other_slot = menu + 0x10;
                }
                if (*other_slot != NULL) {
                    other_slot_data = first_slot;
                    if (step_or_cell == 0) {
                        other_slot_data = menu + 0x10;
                    }
                    step_or_cell = (s32) ((S_8002520C_7 *)(*other_slot_data))->unk_0C;
                    state = ((S_8002520C_8 *)((void *) step_or_cell))->unk_24;
                    target_x = x_value & 0xFFFF;
                    if (target_x != state) {
                        x_in_bounds = target_x < 3U;
                    } else {
                        y_value = target_y;
                        if (y_value == ((S_8002520C_8 *)((void *) step_or_cell))->unk_25) {
                            s32 y_step_value;

                            step_or_cell = step_index & 0xFFFF;
                            x_value += ((u16 *)dir_step_x)[step_or_cell];
                            y_step_value = y_value + ((u16 *)dir_step_y)[step_or_cell];
                            target_y = y_step_value;
                        }
                        x_in_bounds = (x_value & 0xFFFF) < 3U;
                    }
                } else {
                    x_in_bounds = (x_value & 0xFFFF) < 3U;
                }
                if ((x_in_bounds != 0) && (target_y < 3U)) {
                    ((S_8002520C_5 *)side_data)->unk_96 = 8;
                    cell->unk_24 = (u8) x_value;
                    cell->unk_25 = (u8) target_y;
                }
            }
            if (((s32)state_base->pressed_buttons) & 0x40) {
                s16 direction;

                play_sound_if_enabled(0x503);
                {
                    s32 side_offset;
                    S_8002520C_10 *world_node;

                    world_page = (s32 *)0x800E0000;
                    side_offset = ((S_8002520C_0 *)menu)->unk_26;
                    side_ptr = (s32 *)(((S_8002520C_9 *)world_page)->unk_3D7C);
                    side_offset *= 4;
                    world_node = (void *) (side_offset + (s32) menu);
                    world_node = world_node->unk_0C;
                    side_offset += (s32)side_ptr;
                    cell = (S_8002520C_6 *)(world_node->unk_0C);
                    actor = ((S_8002520C_11 *)((void *) side_offset))->unk_AC;
                    direction = (get_rounded_facing_and_rounding_flag(1, 1, ((S_8002520C_12 *)cell)->unk_24, ((S_8002520C_12 *)cell)->unk_25,
                        &target_y) >> 9) & 7;
                }
                {
                    s32 turned_dir;
                    u8 *direction_entry;

                    turned_dir = direction - 2;
                    step_index = ((S_8002520C_0 *)menu)->unk_26;
                    direction_page = (u8 *)0x80010000;
                    direction_entry = ((s16)step_index * 2) + direction_page;
                    if ((turned_dir & 7) != ((S_8002520C_13 *)direction_entry)->unk_2094) {
                        direction = (direction - 2) & 7;
                        ((S_8002520C_13 *)direction_entry)->unk_2094 = direction;
                        actor->unk_45 = (s8) direction;
                        append_packed_action_record(((S_8002520C_9 *)world_page)->unk_3D7C, 0x90, ((S_8002520C_0 *)menu)->unk_26,
                            direction);
                        selected_side = ((S_8002520C_0 *)menu)->unk_26;
                        other_dir = (u16 *)0x80012094;
                        if (selected_side == 0) {
                            other_dir = (u16 *)0x80012096;
                        }
                        if (*other_dir == ((S_8002520C_23 *)(((selected_side * 2) + direction_page)))->unk_2094) {
                            next_dir_dst = (u16 *)0x80012094;
                            if (selected_side == 0) {
                                next_dir_dst = (u16 *)0x80012096;
                            }
                            other_dir_src = (u16 *)0x80012094;
                            if (selected_side == 0) {
                                other_dir_src = (u16 *)0x80012096;
                            }
                            *next_dir_dst = *other_dir_src + 1;
                            wrap_side = ((S_8002520C_0 *)menu)->unk_26;
                            other_dir_dst = (u16 *)0x80012094;
                            if (wrap_side == 0) {
                                other_dir_dst = (u16 *)0x80012096;
                            }
                            wrapped_dir_src = (u16 *)0x80012094;
                            if (wrap_side == 0) {
                                wrapped_dir_src = (u16 *)0x80012096;
                            }
                            *other_dir_dst = *wrapped_dir_src & 7;
                        }
                    }
                }
                if (last_frame_ticks[0] != 0) {
                    selection_blink_target[0] = (u16) ((S_8002520C_0 *)menu)->unk_26;
                    selection_blink_timer[0] = (s16) (0x20 / (s32) last_frame_ticks[0]);
                }
                ((S_8002520C_25 *)(((S_8002520C_24 *)(((((S_8002520C_0 *)menu)->unk_26 * 4)
                    + menu)))->unk_0C))->unk_B6 = 1;
            }
            if (((s32)state_base->pressed_buttons) & 8) {
                ((S_8002520C_0 *)menu)->unk_20 = (u16) (((S_8002520C_0 *)menu)->unk_20 - 0x200);
            }
            if (((s32)state_base->pressed_buttons) & 4) {
                ((S_8002520C_0 *)menu)->unk_20 = (u16) (((S_8002520C_0 *)menu)->unk_20 + 0x200);
            }
        }
        if (((S_8002520C_0 *)menu)->unk_1E != (s16) ((S_8002520C_0 *)menu)->unk_20) {
            ((S_8002520C_0 *)menu)->unk_1E = (s16) ((S_8002520C_0 *)menu)->unk_20;
            ((S_8002520C_0 *)menu)->unk_24 = 8;
        }
        turn_ticks = ((S_8002520C_0 *)menu)->unk_24;
        if (turn_ticks != 0) {
            appearance->unk_1A = (u16) (appearance->unk_1A + ((s32) (((S_8002520C_0 *)menu)->unk_1E
                - (s16) appearance->unk_1A) / turn_ticks));
            turn_left = (u16) ((S_8002520C_0 *)menu)->unk_24 - 1;
            ((S_8002520C_0 *)menu)->unk_24 = turn_left;
            if ((turn_left << 0x10) <= 0) {
                appearance->unk_1A = (u16) ((S_8002520C_0 *)menu)->unk_1E;
                ((S_8002520C_0 *)menu)->unk_24 = 0;
                appearance->unk_1A = (u16) (appearance->unk_1A & 0xFFF);
                ((S_8002520C_0 *)menu)->unk_1E = (s16) ((u16) ((S_8002520C_0 *)menu)->unk_1E & 0xFFF);
                ((S_8002520C_0 *)menu)->unk_20 = (u16) (((S_8002520C_0 *)menu)->unk_20 & 0xFFF);
                return;
            }
        }
        break;
    case 3:
        for (side_count = 0, side_cursor = menu; (s32) side_count < 2; side_count++, side_cursor += 4) {
            side_object = ((S_8002520C_15 *)side_cursor)->unk_0C;
            if ((side_object != NULL) && (((S_8002520C_16 *)side_object)->unk_B6 != 0)) {
                return;
            }
        }
        ((S_8002520C_0 *)menu)->unk_22 = 8;
        motion->unk_16 = 8U;
        ((S_8002520C_0 *)menu)->unk_1C = (s16) ((u16) ((S_8002520C_0 *)menu)->unk_1C + 1);
        /* fallthrough */
    case 4:
                exit_ticks = ((S_8002520C_0 *)menu)->unk_22;
                if (exit_ticks != 0) {
                    motion->unk_02 = (s16) ((u16) motion->unk_02 + ((s32) (-0x480 - motion->unk_02) / exit_ticks));
                    motion->unk_0A.u = (u16) (motion->unk_0A.u + func_800644B8(((S_8002520C_0 *)menu)->unk_22 << 5));
                    exit_scale = appearance->unk_16;
                    appearance->unk_16 = (u16) (exit_scale + ((s32) (0x1000
                        - exit_scale) / (s16) ((S_8002520C_0 *)menu)->unk_22));
                    exit_shade = appearance->unk_0E;
                    scale_y = appearance->unk_1C;
                    faded_shade = exit_shade + ((s32) (0 - exit_shade) / (s16) ((S_8002520C_0 *)menu)->unk_22);
                    appearance->unk_0E = faded_shade;
                    appearance->unk_0D = faded_shade;
                    appearance->unk_0C = faded_shade;
                    scale_z = appearance->unk_1E;
                    appearance->unk_1C = (u16) (scale_y + ((s32) (0x200
                        - scale_y) / (s16) ((S_8002520C_0 *)menu)->unk_22));
                    appearance->unk_1E = (u16) (scale_z + ((s32) (0x200
                        - scale_z) / (s16) ((S_8002520C_0 *)menu)->unk_22));
                    motion->unk_16 = (u16) (motion->unk_16 * 2);
                    side_ptr = (s32 *)0x80080000;
                    exit_left = (u16) ((S_8002520C_0 *)menu)->unk_22 - 1;
                    ((S_8002520C_0 *)menu)->unk_22 = exit_left;
                } else {
                    side_ptr = (s32 *)0x80080000;
                    exit_left = (u16) ((S_8002520C_0 *)menu)->unk_22 - 1;
                    ((S_8002520C_0 *)menu)->unk_22 = exit_left;
                }
                if ((exit_left << 0x10) <= 0) {
                    s32 object_or_flags;
                    s32 flags_or_page;
                    s32 object_or_state;

                    ((S_8002520C_0_pre *)menu)[-1].unk_00 = (u16) (((S_8002520C_0_pre *)menu)[-1].unk_00 | 0x8000);
                    flags_or_page = ((S_8002520C_17 *)side_ptr)->unk_14A0;
                    object_or_state = (s32) ((S_8002520C_0 *)menu)->unk_08;
                    object_or_flags = flags_or_page | 0x8000;
                    ((S_8002520C_17 *)side_ptr)->unk_14A0 = object_or_flags;
                    if (object_or_state != 0) {
                        ((S_8002520C_18 *)((void *) object_or_state))->unk_1E =
                            (u16) (((S_8002520C_18 *)((void *) object_or_state))->unk_1E | 0x8000);
                    }
                    side_count = 0;
                    side_data = side_ptr;
                    side_ptr = (s32 *) menu;
                    do {
                        object_or_flags = (s32) ((S_8002520C_17 *)side_ptr)->unk_0C;
                        if (object_or_flags != 0) {
                            s32 flags_or_page;
                            flags_or_page = ((S_8002520C_8 *)((void *) object_or_flags))->unk_1E;
                            object_or_state = ((S_8002520C_19 *)side_data)->unk_14A0;
                            flags_or_page |= 0x8000;
                            object_or_state |= 0x8000;
                            ((S_8002520C_8 *)((void *) object_or_flags))->unk_1E = (u16) flags_or_page;
                            ((S_8002520C_19 *)side_data)->unk_14A0 = object_or_state;
                        }
                        side_count += 1;
                        side_ptr += 1;
                    } while (side_count < 2);
                    side_count = (s32) ((S_8002520C_0 *)menu)->unk_14;
                    if (side_count != 0) {
                        flags_or_page = (s32) 0x80080000;
                        object_or_state = ((S_8002520C_20 *)((void *) side_count))->unk_1E;
                        object_or_flags = ((S_8002520C_21 *)((s32 *) flags_or_page))->unk_14A0;
                        object_or_state |= 0x8000;
                        object_or_flags |= 0x8000;
                        ((S_8002520C_20 *)((void *) side_count))->unk_1E = (u16) object_or_state;
                        ((S_8002520C_21 *)((s32 *) flags_or_page))->unk_14A0 = object_or_flags;
                    }
                }
            break;
    }
}
#include "dungeon/menu/select.h"

void update_directional_object_fade(void *state_arg, void *buffer_arg, void *obj_arg)
{
    void *state;
    u16 update_count;
    s32 fade_ticks;
    void *buffer = buffer_arg;
    u16 render_flags;
    s8 phase;
    u8 fade_in_value;
    u8 fade_in_value_2;
    u8 fade_out_value;
    u8 current_phase;
    s16 unit_scale;
    s16 direction;
    void *owner;

    update_count = (*(u16 *)D_8002715C);
    state = state_arg;
    update_count++;
    (*(u16 *)D_8002715C) = update_count;
    phase = ((S_80025A14_0 *)state)->unk_72.s;
    switch (phase) {
    case 0:
        unit_scale = 0x1000;
        ((S_80025A14_1 *)buffer)->unk_02 = 0;
        ((S_80025A14_1 *)buffer)->unk_06 = 0;
        ((S_80025A14_1 *)buffer)->unk_0A = 0;
        ((S_80025A14_2 *)obj_arg)->unk_1E = unit_scale;
        ((S_80025A14_2 *)obj_arg)->unk_1C = unit_scale;
        ((S_80025A14_2 *)obj_arg)->unk_0E = 0;
        ((S_80025A14_2 *)obj_arg)->unk_0D = 0;
        ((S_80025A14_2 *)obj_arg)->unk_0C = 0;
        ((S_80025A14_2 *)obj_arg)->unk_28 = reference_tile_object.render_attributes;
        ((S_80025A14_2 *)obj_arg)->unk_14 = reference_tile_object.sprite_flags & 0xFFFC;
        ((S_80025A14_2 *)obj_arg)->unk_2C = D_800DD008;
        ((S_80025A14_2 *)obj_arg)->unk_14 |= 0x200;
        ((S_80025A14_0 *)state)->unk_73.s = 8;
        ((S_80025A14_0 *)state)->unk_72.s = ((S_80025A14_0 *)state)->unk_72.u + 1;
                        /* fall through */
    case 1:
        fade_ticks = (s32)((S_80025A14_0 *)state)->unk_73.s;
        if (fade_ticks != 0) {
            fade_in_value = ((S_80025A14_2 *)obj_arg)->unk_0E;
            fade_in_value += (0x40 - fade_in_value) / fade_ticks;
            ((S_80025A14_2 *)obj_arg)->unk_0E = fade_in_value;
            ((S_80025A14_2 *)obj_arg)->unk_0D = fade_in_value;
            ((S_80025A14_2 *)obj_arg)->unk_0C = fade_in_value;
        }
        fade_in_value_2 = ((S_80025A14_0 *)state)->unk_73.u - 1;
        ((S_80025A14_0 *)state)->unk_73.u = fade_in_value_2;
        if ((s8)fade_in_value_2 <= 0) {
            ((S_80025A14_2 *)obj_arg)->unk_0E = 0x40;
            ((S_80025A14_2 *)obj_arg)->unk_0D = 0x40;
            ((S_80025A14_2 *)obj_arg)->unk_0C = 0x40;
            current_phase = ((S_80025A14_0 *)state)->unk_72.u;
            ((S_80025A14_0 *)state)->unk_73.u = 0;
            ((S_80025A14_0 *)state)->unk_72.u = current_phase + 1;
        }
                        /* fall through */
    case 2:
        if (selection_menu_closing != 0) {
            ((S_80025A14_0 *)state)->unk_73.u = 8;
            ((S_80025A14_1 *)buffer)->unk_16 = 8;
            current_phase = ((S_80025A14_0 *)state)->unk_72.u;
            ((S_80025A14_0 *)state)->unk_72.u = current_phase + 1;
        }
        break;
    case 3:
        fade_ticks = (s32)((S_80025A14_0 *)state)->unk_73.s;
        if (fade_ticks != 0) {
            fade_out_value = ((S_80025A14_2 *)obj_arg)->unk_0E;
            fade_out_value += (0 - fade_out_value) / fade_ticks;
            ((S_80025A14_2 *)obj_arg)->unk_0E = fade_out_value;
            ((S_80025A14_2 *)obj_arg)->unk_0D = fade_out_value;
            ((S_80025A14_2 *)obj_arg)->unk_0C = fade_out_value;
        }
        fade_out_value = ((S_80025A14_0 *)state)->unk_73.u - 1;
        ((S_80025A14_0 *)state)->unk_73.u = fade_out_value;
        if ((s8)fade_out_value <= 0) {
            current_phase = ((S_80025A14_0 *)state)->unk_72.u;
            ((S_80025A14_0 *)state)->unk_72.u = current_phase + 1;
        }
        break;
    default:
        return;
    }

    owner = ((S_80025A14_0 *)state)->unk_58;
    owner = ((S_80025A14_4_pre *)owner)[-1].unk_00;
    direction = ((((S_80025A14_4 *)owner)->unk_1A + 0x500) >> 9) & 7;
    if (((S_80025A14_0 *)state)->unk_46 != direction) {
        ((S_80025A14_0 *)state)->unk_46 = direction;
        texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags(obj_arg, ((u8 *)((S_80025A14_2 *)obj_arg)->unk_2C)[direction],
                      ((S_80025A14_2 *)obj_arg)->unk_04, 2);
    }
    step_actor_animation(obj_arg, 2);
    if (dir_sprite_flag[direction] != 0) {
        render_flags = ((S_80025A14_2 *)obj_arg)->unk_14 | 1;
    } else {
        render_flags = ((S_80025A14_2 *)obj_arg)->unk_14 & 0xFFFE;
    }
    ((S_80025A14_2 *)obj_arg)->unk_14 = render_flags;
    return;
}
#include "dungeon/menu/select.h"

void draw_and_restore_fading_object(void *object_arg, void *position_arg, void *sprite_arg) {
    s16 move_ticks;
    s32 start_y;
    s32 move_ticks_left;
    s32 draw_scale;
    s32 direction;
    s8 fade_out_ticks;
    s8 fade_out_left;
    s8 state;
    u16 saved_render_value;
    u16 update_count;
    u8 fade_in_left;
    u8 fade_out_level;
    u8 next_fade_out;
    u8 fade_in_level;
    u8 next_fade_in;
    s32 red;
    s32 green;
    s32 blue;
    u16 *direction_table;
    S_80025C94_1 *motion;
    S_80025C94_0 *object;
    S_80025C94_2 *sprite;
    S_80025C94_3 *position;
    S_80025C94_5 *appearance;
    GameWork *render_context;
    void *object_ptr;
    void *fade_in_ticks;

    update_count = (*(u16 *)D_8002715C);
    object_ptr = object_arg;
    motion = object_ptr;
    position = position_arg;
    sprite = sprite_arg;
    object = motion;
    (*(u16 *)D_8002715C) = update_count + 1;
    render_context = &g_game_work;
    state = object->unk_72.s;
    switch (state) {
    case 0:
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_0E = 0U;
        sprite->unk_0D = 0U;
        sprite->unk_0C = 0U;
        object->unk_73.s = 8;
        object->unk_2A = 0x400;
        direction_table = (u16 *)0x80010000;
        direction = (((S_80025C94_6 *)((s8 *)direction_table + (object->unk_6A * 2)))->unk_2094 + 2) & 7;
        position->unk_00.at02.v = direction_x_offsets[direction];
        start_y = direction_y_offsets[direction];
        position->unk_0A = 0;
        position->unk_04.at02.v = start_y;
        sprite->unk_24 = (u8) (((s8 *)dir_step_x)[direction * 2] + 1);
        sprite->unk_25 = (u8) (((s8 *)dir_step_y)[direction * 2] + 1);
        object->unk_72.s = (s8) ((u8) object->unk_72.s + 1);
    case 1:
        fade_in_ticks = (void *) object->unk_73.s;
        if (fade_in_ticks != NULL) {
            fade_in_level = sprite->unk_0E;
            next_fade_in = fade_in_level + ((s32) (0x80 - fade_in_level) / (s32) fade_in_ticks);
            sprite->unk_0E = next_fade_in;
            sprite->unk_0D = next_fade_in;
            sprite->unk_0C = next_fade_in;
        }
        fade_in_left = object->unk_73.u - 1;
        object->unk_73.u = fade_in_left;
        if ((fade_in_left << 0x18) <= 0) {
            sprite->unk_0E = 0x80U;
            sprite->unk_0D = 0x80U;
            sprite->unk_0C = 0x80U;
            object->unk_73.u = 0U;
            object->unk_72.u = (u8) (object->unk_72.u + 1);
        }
    case 2:
        if (selection_menu_closing != 0) {
            object->unk_73.u = 8U;
            position->unk_16 = 8;
            object->unk_72.u = (u8) (object->unk_72.u + 1);
        }
        break;
    case 3:
        fade_out_ticks = object->unk_73.s;
        if (fade_out_ticks != 0) {
            fade_out_level = sprite->unk_0E;
            next_fade_out = fade_out_level + ((s32) (0 - fade_out_level) / fade_out_ticks);
            sprite->unk_0E = next_fade_out;
            sprite->unk_0D = next_fade_out;
            sprite->unk_0C = next_fade_out;
        }
        fade_out_left = (u8) object->unk_73.s - 1;
        object->unk_73.s = fade_out_left;
        if ((fade_out_left << 0x18) <= 0) {
            object->unk_72.u = (u8) (object->unk_72.u + 1);
        }
        break;
    default:
        motion->unk_96 = 0;
        return;
    }
    move_ticks = motion->unk_96;
    if (move_ticks != 0) {
        position->unk_00.at00.v = (s32) (position->unk_00.at00.v + ((s32) ((((sprite->unk_24 - 1) << 6)
            - (s16) position->unk_00.at02.v) << 0x10) / move_ticks));
        position->unk_04.at00.v = (s32) (position->unk_04.at00.v + ((s32) ((((sprite->unk_25 - 1) << 6)
            - (s16) position->unk_04.at02.v) << 0x10) / (s16) motion->unk_96));
        move_ticks_left = (u16) motion->unk_96 - 1;
        motion->unk_96 = move_ticks_left;
        if ((move_ticks_left << 0x10) <= 0) {
            motion->unk_96 = 0;
        }
    }
    if (object->unk_14 & 0x40000) {
        motion->unk_92 = -0x20;
    } else {
        motion->unk_92 = 0;
    }
    motion->unk_9D = 0;
    appearance = ((S_80025C94_7_pre *)(object->unk_58))[-1].unk_00;
    saved_render_value = ((u16)render_context->view.camera_rotation.parts.viewAngle);
    render_context->view.camera_rotation.parts.viewAngle = (u16) appearance->unk_1A;
    sprite->unk_14 = (u16) (sprite->unk_14 & 0xFFBF);
    position->unk_00.at02.v = (u16) (position->unk_00.at02.v + 0x100);
    position->unk_04.at02.v = (u16) (position->unk_04.at02.v + 0x100);
    if ((*(s16 *)selection_blink_target) == object->unk_6A) {
        draw_scale = ((*(s16 *)selection_blink_timer) << 9) + 0x400;
        object->unk_2A = draw_scale;
    } else {
        object->unk_2A = 0x400;
    }
    object->unk_5C(motion, position, sprite, motion);
    position->unk_00.at02.v = (u16) (position->unk_00.at02.v - 0x100);
    position->unk_04.at02.v = (u16) (position->unk_04.at02.v - 0x100);
    render_context->view.camera_rotation.parts.viewAngle = saved_render_value;
    object->unk_88 = 0;
    red = appearance->unk_0C;
    if (object->unk_6A != ((S_80025C94_7 *)(object->unk_58))->unk_26) {
        red = red >> 1;
    }
    sprite->unk_0C = red;
    green = appearance->unk_0D;
    if (object->unk_6A != ((S_80025C94_7 *)(object->unk_58))->unk_26) {
        green = green >> 1;
    }
    sprite->unk_0D = green;
    blue = appearance->unk_0E;
    if (object->unk_6A != ((S_80025C94_7 *)(object->unk_58))->unk_26) {
        blue = blue >> 1;
    }
    sprite->unk_0E = blue;
    return;
}
#include "dungeon/menu/select.h"

void switch_active_object_index(void *object, s16 new_index) {
    s16 old_index;
    s32 entry_index;
    s32 direction;
    S_800260C8_2 *entry_offsets;
    S_800260C8_3 *linked_state;
    S_800260C8_0 *index_state;
    void *entries;
    ResidentPage *resident_page;

    index_state = object + 0x20;
    old_index = index_state->unk_26;
    if (old_index != new_index) {
        entries = ((S_800260C8_1 *)object)->unk_20;
        if (entries != NULL) {
            ((S_800260C8_6 *)(((S_800260C8_4 *)(((old_index * 4) + entries)))->unk_0C))->unk_B6 = 4;
            resident_page = (ResidentPage *)0x80010000;
            entry_index = index_state->unk_26;
            entry_offsets = ((S_800260C8_7 *)(((S_800260C8_5 *)(((entry_index * 4)
                + ((S_800260C8_1 *)object)->unk_20)))->unk_0C))->unk_0C;
            direction = (resident_page->table[entry_index] + 2) & 7;
            entry_offsets->unk_24 = (s8) (dir_step_x[direction] + 1);
            entry_offsets->unk_25 = (s8) (dir_step_y[direction] + 1);
        }
        index_state->unk_26 = new_index;
        linked_state = ((S_800260C8_1 *)object)->unk_20;
        if (linked_state != NULL) {
            linked_state->unk_26 = new_index;
        }
    }
}
#include "dungeon/menu/select.h"

void initialize_children_or_shutdown(void *owner)
{
    u32 state;
    s32 stop_state;
    s32 source_slot;
    s32 object_or_kind;
    s32 signed_kind;
    s32 shifted_kind;
    s32 parent_value;
    s32 entity_flags;
    s32 flags_mask;
    s32 clear_pairs_left;
    u16 spawn_bits;
    u16 owner_bits;
    u16 child_bits;
    u16 alloc_bits;
    s32 cleanup_flags;
    s32 alloc_flags;
    register void *entity_arg;
    void *child;
    u8 *status_page;
    s32 mode;
    u8 *flag_page;
    u8 *cleanup_page;
    u8 *status;
    void *source;
    SpriteFrameState *parent;
    void *main_child;
    void *aux_child;
    void *child_object;
    void *alloc_container;
    void *setup_container;
    s32 mask_work;
    void *spawn_container;
    void *spawn_child;
    void *spawn_resource;
    void *entity;

    status_page = (u8 *)((s8 *)(&g_game_work));
    state = ((S_80026190_0 *)owner)->unk_1C.s;
    stop_state = 2;
    if (state == stop_state) {
        if ((*(s16 *)D_8002715C) == 0) {
            (*(u16 *)((u8 *)owner + -2)) |= 0x8000;
            object_flag_block.flags |= 0x8000;
        }
        (*(s16 *)D_8002715C) = 0;
        return;
    }

    status = status_page;
    if (((S_80026190_1 *)status)->unk_08 & 0x20) {
        main_child = ((S_80026190_0 *)owner)->unk_00;
        if (main_child != NULL) {
            ((S_80026190_2 *)main_child)->unk_1C = 3;
        }
        aux_child = ((S_80026190_0 *)owner)->unk_04;
        if (aux_child != NULL) {
            ((S_80026190_3 *)aux_child)->unk_0E = 3;
        }
        selection_menu_closing = 1;
        ((S_80026190_0 *)owner)->unk_1C.s = stop_state;
        (*(s16 *)D_8002715C) = 0;
        func_8004E130();
        return;
    }

    if (state != 0) {
        return;
    }

    object_or_kind = (s32)func_8003FC64(0x12);
    if (object_or_kind == 0) {
        return;
    }
    ((S_80026190_4 *)((void *)object_or_kind))->unk_10.s = (void *)update_selection_menu_animation;
    child = (u8 *)object_or_kind + 0x20;
    ((S_80026190_0 *)owner)->unk_00 = child;
    ((S_80026190_5 *)child)->unk_26 = ((S_80026190_0 *)owner)->unk_26;

    child_object = func_8003FC64(0x112);
    ((S_80026190_5 *)child)->unk_08 = child_object;
    if (child_object == NULL) {
        alloc_container = ((S_80026190_0 *)owner)->unk_00;
        alloc_bits = ((S_80026190_6_pre *)alloc_container)[-1].unk_00;
        (*(u16 *)((u8 *)alloc_container + -2)) = alloc_bits | 0x8000;
        alloc_flags = object_flag_block.flags;
        ((S_80026190_0 *)owner)->unk_00 = NULL;
        alloc_flags |= 0x8000;
        object_flag_block.flags = alloc_flags;
        return;
    }

    object_or_kind = (s32)child_object;
    ((S_80026190_4 *)((void *)object_or_kind))->unk_10.s = (void *)update_directional_object_fade;
    ((S_80026190_4 *)((void *)object_or_kind))->unk_78 = ((S_80026190_0 *)owner)->unk_00;
    if ((((S_80026190_5 *)child)->unk_14 = allocate_sprite_data_object((s32)child)) == NULL) {
        setup_container = ((S_80026190_0 *)owner)->unk_00;
        owner_bits = ((S_80026190_7_pre *)setup_container)[-1].unk_00;
        cleanup_page = (u8 *)0x80080000;
        ((S_80026190_7_pre *)setup_container)[-1].unk_00 = owner_bits | 0x8000;
        ((S_80026190_0 *)owner)->unk_00 = NULL;
        mask_work = (s32)(((S_80026190_5 *)child)->unk_08);
        cleanup_flags = ((S_80026190_8 *)cleanup_page)->unk_14A0;
        child_bits = ((S_80026190_9 *)((void *)mask_work))->unk_1E;
        cleanup_flags |= 0x8000;
        ((S_80026190_8 *)cleanup_page)->unk_14A0 = cleanup_flags;
        ((S_80026190_9 *)((void *)mask_work))->unk_1E = child_bits | 0x8000;
        ((S_80026190_5 *)child)->unk_08 = NULL;
        return;
    }

    for (source_slot = 0; source_slot < 2; source_slot++) {
    flag_page = (u8 *)0x80080000;
    source = *(void **)(((u8 *)dungeon_actor_ring_anchor) + (source_slot * 4) + 0xAC);
    if (source != NULL) {
        object_or_kind = 0x1E;
        if (!(((S_80026190_10 *)source)->unk_14 & 0x20000000)) {
            object_or_kind = ((S_80026190_10 *)source)->unk_13;
        }
        if (((S_80026190_10 *)source)->unk_13 == 0x2E) {
            object_or_kind = ((S_80026190_10 *)source)->unk_A8;
            set_code_for_entity_mode(source);
        } else {
            set_code_for_entity_mode(source);
        }

        status_page = (u8 *)0x80010000;
        mode = ((S_80026190_11 *)status_page)->unk_2090;
        if (mode == 1) {
            if ((s16)object_or_kind == 2) {
                object_or_kind = 0x39;
            }
        }
        shifted_kind = object_or_kind << 16;
        signed_kind = shifted_kind >> 16;

        entity = load_monster_resource_data(signed_kind, find_or_retain_sprite_resource_slot(signed_kind, 3), 1);
        drain_cd_command_queue();
        entity = ((SpawnFunc)entity)(1, 0, 0, ((S_80026190_10 *)source)->unk_88);

        status_page = (u8 *)0x80010000;
        mode = ((S_80026190_11 *)status_page)->unk_2090;
        if ((mode == 1) && (signed_kind == 0x39)) {
            object_or_kind = 2;
        }

        if (entity == NULL) {
            spawn_container = ((S_80026190_0 *)owner)->unk_00;
            ((S_80026190_12_pre *)spawn_container)[-1].unk_00 |= 0x8000;
            ((S_80026190_0 *)owner)->unk_00 = NULL;

            spawn_child = ((S_80026190_5 *)child)->unk_08;
            ((S_80026190_13 *)spawn_child)->unk_1E |= 0x8000;
            ((S_80026190_5 *)child)->unk_08 = NULL;

            spawn_resource = ((S_80026190_5 *)child)->unk_14;
            ((S_80026190_14 *)spawn_resource)->unk_1E |= 0x8000;

            parent_value = ((S_80026190_15 *)flag_page)->unk_14A0.s;
            entity_arg = ((S_80026190_5 *)child)->unk_0C;
            ((S_80026190_5 *)child)->unk_14 = NULL;
            flags_mask = parent_value | 0x8000;
            ((S_80026190_15 *)flag_page)->unk_14A0.u = flags_mask;
            if (entity_arg != NULL) {
                spawn_bits = ((S_80026190_16 *)entity_arg)->unk_1E;
                ((S_80026190_15 *)flag_page)->unk_14A0.s = flags_mask;
                ((S_80026190_16 *)entity_arg)->unk_1E = spawn_bits | 0x8000;
                ((S_80026190_5 *)child)->unk_0C = NULL;
            }
            return;
        }

        func_80042640(entity, (s16)object_or_kind);
        ((S_80026190_17 *)entity)->unk_14 = 0;
        ((S_80026190_17 *)entity)->unk_1C = 0;
        copy_entity_record(entity, source);

        ((S_80026190_17 *)entity)->unk_13 = object_or_kind;
        for (clear_pairs_left = 3; clear_pairs_left >= 0; clear_pairs_left--) {
            ((u8 *)entity)[clear_pairs_left * 2 + 0x2C] = 0;
            ((u8 *)entity)[clear_pairs_left * 2 + 0x2D] = 0;
        }

        mask_work = 0xBFFFFFFF;
        entity_arg = entity;
        entity_flags = 0x64;
        ((S_80026190_17 *)entity)->unk_25 = entity_flags;
        ((S_80026190_17 *)entity)->unk_88 = 0;
        ((S_80026190_17 *)entity)->unk_1C &= ~0x1EF8;
        ((S_80026190_17 *)entity)->unk_1C &= mask_work;
        ((S_80026190_17 *)entity)->unk_1C |= 0x40000;
        unlink_entity_node(entity_arg);

        flags_mask = ((S_80026190_10 *)source)->unk_14;
        parent = ((S_80026190_17_pre *)entity)[-1].unk_00;
        flags_mask &= 0x20000000;
        if (flags_mask) {
            parent_value = get_entity_class(source) << 2;
            parent->clut = parent_value;
        } else {
            parent_value = ((S_80026190_19 *)(((S_80026190_10_pre *)source)[-1].unk_00))->unk_12;
            parent->clut = parent_value;
        }

        object_or_kind = (s32)entity - 0x20;
        *(s32 *)((u8 *)child + (source_slot * 4) + 0xC) = object_or_kind;
        ((S_80026190_17 *)entity)->unk_5C = ((S_80026190_4 *)((void *)object_or_kind))->unk_10.u | 0x80000000;
        ((S_80026190_17 *)entity)->unk_58 = ((S_80026190_0 *)owner)->unk_00;
        ((S_80026190_17 *)entity)->unk_6A = source_slot;
        unlink_node((void *)object_or_kind);
        retire_tracked_effect_by_id((void *)object_or_kind);
        update_map_cell_flags_with_item_limit(parent->unk_24, parent->unk_25, 0x300);
        ((S_80026190_17 *)entity)->unk_87 = 0xFF;
        ((S_80026190_4 *)((void *)object_or_kind))->unk_10.s = (void *)draw_and_restore_fading_object;
    }
    }

    object_or_kind = (s32)func_8003FC64(0x212);
    if (object_or_kind != 0) {
        ((S_80026190_4 *)((void *)object_or_kind))->unk_10.s = (void *)initialize_fading_effect;
        ((S_80026190_0 *)owner)->unk_04 = (u8 *)object_or_kind + 0x20;
    }
    ((S_80026190_0 *)owner)->unk_1C.u++;

    return;
}
#include "dungeon/menu/select.h"
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define U8_AT(p, o) (*(u8 *)((u8 *)(p) + (o)))
void initialize_fading_effect(void *effect, void *control)
{
    s16 state;
    s16 dark_frames;
    s16 light_frames;
    s16 dark_frames_left;
    s16 light_frames_left;
    u8 dark_color;
    u8 dark_next_color;
    u8 light_color;
    u8 light_next_color;

    state = S16_AT(effect, 0xE);
    switch (state) {
    case 0:
        register_node((u8 *)effect - 0x20, &queue_four_shaded_quadrants);
        S16_AT(effect, 0) = 0x50;
        S16_AT(effect, 4) = 0xA0;
        S16_AT(effect, 2) = 0x58;
        S16_AT(effect, 6) = 0xB0;
        S16_AT(control, 0xA) = 0x40;
        S16_AT(effect, 0xC) = 8;
        S16_AT(effect, 0xE) = (s16)(U16_AT(effect, 0xE) + 1);
                        /* fall through */
    case 1:
        light_frames = S16_AT(effect, 0xC);
        if (light_frames != 0) {
            light_color = U8_AT(effect, 0xA);
            light_next_color =
                light_color + ((0x60 - light_color) / light_frames);
            U8_AT(effect, 0xA) = light_next_color;
            U8_AT(effect, 9) = light_next_color;
            U8_AT(effect, 8) = light_next_color;
        }
        light_frames_left = U16_AT(effect, 0xC) - 1;
        S16_AT(effect, 0xC) = light_frames_left;
        if ((light_frames_left << 0x10) > 0) {
            return;
        }
        U8_AT(effect, 0xA) = 0x60;
        U8_AT(effect, 9) = 0x60;
        U8_AT(effect, 8) = 0x60;
        S16_AT(effect, 0xE) = (s16)(U16_AT(effect, 0xE) + 1);
        return;
    case 3:
        S16_AT(effect, 0xC) = 8;
        S16_AT(effect, 0xE) = (s16)(U16_AT(effect, 0xE) + 1);
                        /* fall through */
    case 4:
        dark_frames = S16_AT(effect, 0xC);
        if (dark_frames != 0) {
            dark_color = U8_AT(effect, 0xA);
            dark_next_color = dark_color + ((0 - dark_color) / dark_frames);
            U8_AT(effect, 0xA) = dark_next_color;
            U8_AT(effect, 9) = dark_next_color;
            U8_AT(effect, 8) = dark_next_color;
        }
        dark_frames_left = U16_AT(effect, 0xC) - 1;
        S16_AT(effect, 0xC) = dark_frames_left;
        if ((dark_frames_left << 0x10) > 0) {
            return;
        }
        U16_AT(effect, -2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
        break;
    default:
        return;
    }
}
#undef S16_AT
#undef U16_AT
#undef U8_AT
#include "dungeon/menu/select.h"

void *initialize_available_object(s16 initialValue) {
    S_800267F0_0 *object;

    selection_menu_closing = 0;
    object = func_8003FC64(0);
    if (object != NULL) {
        object->unk_10 = (void *)initialize_children_or_shutdown;
        object->unk_46 = initialValue;
        set_message_mode(2);
        runtime_call_selected_mode_handler();
        submit_script_with_registered_context(&D_80027160);
    }
    return object;
}
#include "dungeon/menu/select.h"
#define S16(b, o) (*(s16 *)((u8 *)(b) + (o)))
#define U16(b, o) (*(u16 *)((u8 *)(b) + (o)))
#define S32(b, o) (*(s32 *)((u8 *)(b) + (o)))
s32 render_three_by_three_terrain_grid(Objects *objects, ViewPosition *view_position, RenderParams *render_params)
{
    s16 saved_rotation[4];
    s16 saved_position[4];
    u8 *materials;
    s32 col;
    s32 row;
    s32 cell_index;
    Geometry *geometry;
    Vert *vertices;
    RenderState *render_state;
    Cell *cells;
    Scratch *scratch;
    DrawBuffer *draw_buffer;
    DrawBuffer *active_buffer;
    Prim *prim;
    Face *face;
    SpriteData *sprite_data;
    Object *main_object;
    Object *main_entry;
    Object *extra_entry;
    Object *extra_object;
    Sprite *sprite;
    u32 x1_shifted;
    s32 x1_masked;
    u32 packed2;
    u32 x3;
    u32 x3_shifted;
    u32 x3_masked;
    u32 packed3;
    u32 vert0_ref;
    s16 height0;
    s32 height1;
    s32 height2;
    s32 height3;
    s32 cell_x;
    s32 object_index;
    s32 depth;
    u32 vert3_ref_y;
    u32 vert1_ref_y;
    u32 vert2_y;
    s32 vert0_y;
    u32 y1_high;
    u32 y3_high;
    u32 y2_high;
    u32 height_bias;
    s32 vert3_y;

    geometry = (Geometry *)&scene_geometry[0];
    vertices = geometry->vertices;
    materials = geometry->materials;
    func_800649A0();
    {
        union { s32 value; } cell_y = {0};
        cell_y.value = -0x60;
        scratch = (Scratch *)0x1F800000;
        scratch->view_w = render_params->width;
        scratch->view_h = render_params->height;
        scratch->view_mid = (s32) (render_params->width + render_params->height) >> 1;
        render_state = (RenderState *)&g_game_work;
        cells = &menu_mesh_cells[0];
        scratch->eye[0] = view_position->x;
        scratch->eye[1] = view_position->y;
        scratch->eye[2] = view_position->z;
        func_80064B90(scratch->matrix, &scratch->eye[0]);
        func_80065820(render_params->rotation, scratch->matrix);
        func_80064BC0(scratch->matrix, &scratch->view_w);
        func_80064CF0(scratch->matrix);
        func_80064D80(scratch->matrix);
        draw_buffer = render_state->draw_buffer;
        scratch->ot = (s32) draw_buffer->ot;
        prim = draw_buffer->prim;
        scratch->xy0 = 0;
        scratch->h0 = 0;
        scratch->depth_base = func_80065420(&scratch->xy0, scratch->buf, &scratch->out0, &scratch->out1) - 0x27;
        row = 0;
        cell_index = 0;
        do {
            union { u32 value; } mesh_index = {0};
            union { u32 value; } packed0 = {0};
            union { u32 value; } x1 = {0};
            union { u32 value; } packed1 = {0};
            union { u32 value; } vert0_addr = {0};
            union { u32 value; } vert1_addr = {0};
            union { u32 value; } vert2_addr = {0};
            union { u32 value; } vert2_ref = {0};
            union { u32 value; } vert3_addr = {0};
            union { u32 value; } index1 = {0};
            union { u32 value; } index1_xy = {0};
            union { u32 value; } index2 = {0};
            union { u32 value; } index3 = {0};
            union { u32 value; } y0_high = {0};
            union { s32 value; } facing = {0};
            cell_x = -0x60;
            col = 0;
            do {
                mesh_index.value = menu_mesh_cells[cell_index].idx;
                if (mesh_index.value != 0) {
                    face = geometry->faces[mesh_index.value];
                    for (;;) {
                        vert0_addr.value = face->i0 * 8 + (u32)vertices;
                        packed0.value = ((Vert *)vert0_addr.value)->x;
                        packed0.value = packed0.value + cell_x;
                        packed0.value = packed0.value & 0xFFFF;
                        vert0_y = ((Vert *)vert0_addr.value)->y;
                        y0_high.value = (cell_y.value + vert0_y) << 0x10;
                        packed0.value = packed0.value | y0_high.value;
                        S32(scratch, 0x70) = packed0.value;
                        vert2_ref.value = U16((u8 *)face, 4);
                        vert3_ref_y = U16((u8 *)face, 6);
                        vert0_ref = U16((u8 *)face, 0);
                        index1_xy.value = face->i1;
                        vert1_ref_y = index1_xy.value * 8 + (u32)vertices;
                        x1.value = U16((u8 *)vert1_ref_y, 0);
                        vert1_ref_y = ((Vert *)vert1_ref_y)->y;
                        vert2_ref.value = vert2_ref.value << 3;
                        vert2_ref.value = vert2_ref.value + (u32)vertices;
                        vert3_ref_y = vert3_ref_y << 3;
                        vert3_ref_y = vert3_ref_y + (u32)vertices;
                        vert0_ref = vert0_ref * 8;
                        vert0_ref = vert0_ref + (u32)vertices;
                        x1_shifted = x1.value + cell_x;
                        x1_shifted &= 0xFFFF;
                        x1_masked = (u16)x1_shifted;
                        y1_high = (cell_y.value + vert1_ref_y) << 0x10;
                        packed1.value = x1_masked | y1_high;
                        packed2 = ((Vert *)vert2_ref.value)->x;
                        vert2_y = ((Vert *)vert2_ref.value)->y;
                        x3 = ((Vert *)vert3_ref_y)->x;
                        height0 = ((Vert *)vert0_ref)->w;
                        height_bias = menu_mesh_cells[cell_index].bias;
                        height0 = height0 - height_bias;
                        vert3_ref_y += 2;
                        vert3_y = S16((u8 *)vert3_ref_y, 0);
                        packed2 = packed2 + cell_x;
                        packed2 = packed2 & 0xFFFF;
                        y2_high = (cell_y.value + vert2_y) << 0x10;
                        packed2 = packed2 | y2_high;
                        x3_shifted = x3 + cell_x;
                        x3_masked = x3_shifted & 0xFFFF;
                        scratch->h0 = height0;
                        index1.value = face->i1;
                        vert1_addr.value = index1.value * 8 + (u32)vertices;
                        y3_high = (cell_y.value + vert3_y) << 0x10;
                        height1 = U16((u8 *)vert1_addr.value, 4);
                        S32(scratch, 0x78) = packed1.value;
                        height1 = height1 - menu_mesh_cells[cell_index].bias;
                        scratch->h1 = height1;
                        index2.value = U16((u8 *)face, 4);
                        vert2_addr.value = index2.value * 8 + (u32)vertices;
                        height2 = ((Vert *)vert2_addr.value)->w;
                        S32(scratch, 0x80) = packed2;
                        height2 = height2 - menu_mesh_cells[cell_index].bias;
                        scratch->h2 = height2;
                        index3.value = face->i3;
                        vert3_addr.value = index3.value * 8 + (u32)vertices;
                        packed3 = x3_masked | y3_high;
                        scratch->xy3 = packed3;
                        height3 = ((Vert *)vert3_addr.value)->w;
                        height3 = height3 - menu_mesh_cells[cell_index].bias;
                        scratch->h3 = height3;
                        facing.value = func_800656C0(&scratch->xy0, &scratch->xy1, &scratch->xy2, &scratch->xy3,
                                          &prim->xy0, &prim->xy1, &prim->xy2, &prim->xy3,
                                          &scratch->out0, &scratch->depth, &scratch->out1);
                        scratch->facing = facing.value;
                        if (facing.value > 0) {
                            depth = scratch->depth - scratch->depth_base;
                            scratch->depth = depth;
                            if ((u32) (depth - 1) < 0x1DF) {
                                func_80065034(materials + face->tex * 8, render_state->blend, prim->rgb);
                                prim->a = face->a;
                                prim->b = face->b;
                                prim->u2 = face->u2;
                                prim->u3 = face->u3;
                                if (render_params->color[0] != 0x80) {
                                    prim->rgb[0] = (prim->rgb[0] * render_params->color[0]) >> 7;
                                    prim->rgb[1] = (prim->rgb[1] * render_params->color[1]) >> 7;
                                    prim->rgb[2] = (prim->rgb[2] * render_params->color[2]) >> 7;
                                }
                                prim->code = 9;
                                func_8006658C(scratch->ot + scratch->depth * 4, prim);
                                prim += 1;
                            }
                        }
                        if ((face->flags & 0x80FF) == 0x8001) {
                            break;
                        }
                        face += 1;
                    }
                }
                cells[cell_index].bias = 0;
                cell_x += 0x40;
                col += 1;
                cell_index += 1;
            } while (col < 3);
            cell_y.value += 0x40;
            row += 1;
        } while (row < 3);

        active_buffer = render_state->draw_buffer;
        active_buffer->prim = prim;
        saved_rotation[0] = render_state->rotation[0];
        saved_rotation[1] = render_state->rotation[1];
        saved_rotation[2] = render_state->rotation[2];
        saved_position[0] = render_state->position[0];
        saved_position[1] = render_state->position[1];
        saved_position[2] = render_state->position[2];
        render_state->position[0] = 0;
        render_state->position[1] = 0;
        render_state->position[2] = 0;
        render_state->rotation[0] = render_params->rotation[0];
        render_state->rotation[1] = render_params->rotation[1];
        render_state->rotation[2] = render_params->rotation[2];

        if (objects->main != 0) {
            scratch->clear = 0;
            main_object = objects->main;
            project_sprite_commands(main_object->transform, main_object->lo, main_object->hi, (s16) scratch->depth_base);
            main_entry = objects->main;
            D_8002713A[0] = -2;
            set_negated_coordinate_scratch(main_entry->lo, main_entry->hi, -2, scratch->depth_base);
        }
        object_index = 0;
        do {
            if (objects->extra[object_index] != 0) {
                scratch->clear = 0;
                extra_object = objects->extra[object_index];
                project_sprite_commands(extra_object->transform, extra_object->lo, extra_object->hi, (s16) scratch->depth_base);
                extra_entry = objects->extra[object_index];
                set_negated_coordinate_scratch(extra_entry->lo, extra_entry->hi, 0, scratch->depth_base);
            }
            object_index += 1;
        } while (object_index < 2);

        sprite = objects->sprite;
        if (sprite != 0) {
            sprite_data = sprite->data;
            if (!(sprite_data->flags & 0x80)) {
                draw_sprite_clipped(sprite->transform, sprite->lo, sprite_data, (s16) scratch->depth_base);
            }
        }
        render_state->position[0] = saved_position[0];
        render_state->position[1] = saved_position[1];
        render_state->position[2] = saved_position[2];
        render_state->rotation[0] = saved_rotation[0];
        render_state->rotation[1] = saved_rotation[1];
        render_state->rotation[2] = saved_rotation[2];
        func_80064A40();
        return 0;
    }
}
#undef S16
#undef U16
#undef S32
#include "dungeon/menu/select.h"

void set_negated_coordinate_scratch(s32 call_value, s32 call_option, s16 call_mode, s32 call_extra)
{
    s16 *scratch = (s16 *)0x1F800000;
    GameWork *g = &g_game_work;

    scratch[0x104 / 2] = 0;
    scratch[0x100 / 2] = -((u16)g->view.camera_rotation.parts.camera_rotation_x);
    scratch[0x102 / 2] = -((u16)g->view.camera_rotation.parts.camera_rotation_y);
    render_projected_sprite_with_depth_bias(call_value, call_option, call_mode, call_extra);
}

#include "dungeon/menu/select.h"
#define U8(base, offset) (*(u8 *)((u8 *)(base) + (offset)))
#define S16(base, offset) (*(s16 *)((u8 *)(base) + (offset)))
#define U16(base, offset) (*(u16 *)((u8 *)(base) + (offset)))
#define S32(base, offset) (*(s32 *)((u8 *)(base) + (offset)))
#define PTR(base, offset) (*(u8 **)((u8 *)(base) + (offset)))
s32 queue_four_shaded_quadrants(void *rect_arg, void *owner_arg)
{
    u8 *rect_data;
    u8 *owner;
    u8 **render_state_ptr;
    s32 quadrant;
    u8 *render_state;
    u8 *packet;
    u8 *next_node;
    u16 center_coord;
    s16 edge_coord;
    s32 packet_word;

    rect_data = rect_arg;
    owner = owner_arg;
    render_state_ptr = (u8 **)((s8 *)(&g_game_work));
    for (;;) {
        quadrant = 3;
        do {
            render_state = *render_state_ptr;
            packet = PTR(render_state, 0x8D0);
            PTR(render_state, 0x8D0) = packet + 0x24;

            center_coord = U16(rect_data, 0);
            U16(packet, 0x18) = center_coord;
            U16(packet, 8) = center_coord;

            if (quadrant & 1) {
                edge_coord = U16(rect_data, 0) - U16(rect_data, 4);
            } else {
                edge_coord = U16(rect_data, 0) + U16(rect_data, 4);
            }
            S16(packet, 0x20) = edge_coord;
            S16(packet, 0x10) = edge_coord;

            center_coord = U16(rect_data, 2);
            U16(packet, 0x12) = center_coord;
            U16(packet, 0xA) = center_coord;

            if (quadrant & 2) {
                edge_coord = U16(rect_data, 2) - U16(rect_data, 6);
            } else {
                edge_coord = U16(rect_data, 2) + U16(rect_data, 6);
            }
            S16(packet, 0x22) = edge_coord;
            S16(packet, 0x1A) = edge_coord;

            packet_word = S32(rect_data, 8);
            S32(packet, 0x1C) = 0;
            S32(packet, 0xC) = 0;
            S32(packet, 0x14) = 0;
            S32(packet, 4) = packet_word;
            func_80066708(packet);

            quadrant--;
            U8(packet, 7) |= 2;
            func_8006658C(*render_state_ptr + ((S16(owner, 0xA) * 4) + 0xB0), packet);
        } while (quadrant >= 0);

        render_state = *render_state_ptr;
        packet = PTR(render_state, 0x8D0);
        PTR(render_state, 0x8D0) = packet + 0xC;
        packet_word = func_80066460(0, 2, 0, 0);
        func_80067F20(packet, 0, 0, packet_word & 0xFFFF, 0);
        func_8006658C(*render_state_ptr + ((S16(owner, 0xA) * 4) + 0xB0), packet);

        next_node = PTR(rect_data, -8);
        rect_data = next_node + 0x20;
        if (next_node == 0) {
            break;
        }
        owner = PTR(next_node, 8);
    }
    return 0;
}
#undef U8
#undef S16
#undef U16
#undef S32
#undef PTR

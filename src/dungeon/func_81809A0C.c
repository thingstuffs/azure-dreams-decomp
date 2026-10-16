#include "modules/dungeon_ovl_1829800.h"

void dungeonUpdateSelectionMenuAnimation(void *menu_in, void *motion_in, void *appearance_in) {
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
    state_base = &gameWork;
    state = ((S_8002520C_0 *)menu)->unk_1C;
    switch ((u32)state) {
    case 0:
        func_8004491C(menu - 0x20, &dungeonRenderThreeByThreeTerrainGrid);
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
        if (D_80027156[0] == 0) {
            S_8002520C_6 *cell;
            input_angle = dungeonResolvePlayerInputFacing(((u16) appearance->unk_1A >> 9) & 7,
                ((EntityRec *)(((u8 *)(&D_800E3D7C))))->x.v + 0xA2, 0) & 0xFFFF;
            if ((input_angle != 0xFFF) && (((s32)state_base->unk_010) & 0xF000)) {
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

                    x_step_ptr = (u16 *) (step_or_cell + ((s32)((s32) ((u16 *)dirStepX))));
                    step_value = *x_step_ptr;
                    cell_coord = cell->unk_24;
                    base_x = cell_coord + step_value;
                    step_value = (s32) ((u16 *)dirStepY);
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
                            x_value += ((u16 *)dirStepX)[step_or_cell];
                            y_step_value = y_value + ((u16 *)dirStepY)[step_or_cell];
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
            if (((s32)state_base->unk_010) & 0x40) {
                s16 direction;

                func_800A56E0(0x503);
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
                    direction = (dungeonGetRoundedFacingAndRoundingFlag(1, 1, ((S_8002520C_12 *)cell)->unk_24, ((S_8002520C_12 *)cell)->unk_25,
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
                        dungeonAppendPackedActionRecord(((S_8002520C_9 *)world_page)->unk_3D7C, 0x90, ((S_8002520C_0 *)menu)->unk_26,
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
                if (D_80080A87[0] != 0) {
                    D_80027158[0] = (u16) ((S_8002520C_0 *)menu)->unk_26;
                    D_80027156[0] = (s16) (0x20 / (s32) D_80080A87[0]);
                }
                ((S_8002520C_25 *)(((S_8002520C_24 *)(((((S_8002520C_0 *)menu)->unk_26 * 4)
                    + menu)))->unk_0C))->unk_B6 = 1;
            }
            if (((s32)state_base->unk_010) & 8) {
                ((S_8002520C_0 *)menu)->unk_20 = (u16) (((S_8002520C_0 *)menu)->unk_20 - 0x200);
            }
            if (((s32)state_base->unk_010) & 4) {
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

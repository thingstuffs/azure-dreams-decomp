#include "dungeon/menu/entries.h"


void clear_menu_state_values(ovl_1831cd8_81811CD8_S_80026CD8_0 *state) {
    *state->unk_0C = 0;
    *state->unk_10 = 0;
}

void set_entry_destination_and_value(Rec_func_80026CF0_arg0 *record, s32 value) {
    *record->unk_0C = &D_800789B8;
    *record->unk_10 = value;
}

void position_menu_grid_entries(ovl_1831cd8_81811D0C_S_80026D0C_0 *display, s32 cell_index) {
    s32 row_y;
    s32 x_offset;
    s32 column_x;
    ovl_1831cd8_81811D0C_S_80026D0C_1 *element_node;
    ovl_1831cd8_81811D0C_S_80026D0C_2 *element;

    column_x = ((cell_index % 72) % 9) * 0xB;
    ((ovl_1831cd8_81811D0C_S_80026D0C_7 *)(((ovl_1831cd8_81811D0C_S_80026D0C_3 *)(display->unk_0C))->unk_04))->unk_08 =
        (s16)(column_x - 0x2B);
    row_y = ((cell_index % 72) / 9) * 0x10;
    ((ovl_1831cd8_81811D0C_S_80026D0C_7 *)(((ovl_1831cd8_81811D0C_S_80026D0C_3 *)(display->unk_0C))->unk_04))->unk_0A =
        (s16)(row_y + 0xF);
    element_node = display->unk_10;
    x_offset = ((ovl_1831cd8_81811D0C_S_80026D0C_4 *)(element_node->unk_00))->unk_0A;
    element_node = element_node->unk_04;
    x_offset = (u32)x_offset >> 1;
    x_offset -= 0x29;
    element_node->unk_08 = (s16)(column_x + x_offset);
    element = display->unk_10;
    ((ovl_1831cd8_81811D0C_S_80026D0C_5 *)(element->unk_04))->unk_0A =
        (s16)(row_y + ((((ovl_1831cd8_81811D0C_S_80026D0C_6 *)(element->unk_00))->unk_0B >> 1) + 0xF));
}

s32 configure_menu_resource(s32 setup_value, s32 setup_data) {
    s32 resource;

    resource = create_callback_pair_default(0x91);
    if (resource != 0) {
        resource = func_80025040(resource, setup_value, setup_data, 0x48);
    }
    return resource;
}

s32 count_menu_entry_matches(s32 target_value) {
    s32 index;
    s32 count;
    u8 value;
    u8 *page = (u8 *)0x80010000;

    count = 0;
    for (index = 0; index < 0x40; index++) {
        value = page[0x57D2 + index * 0x13];
        if (value == 0) {
            break;
        }
        if (value == target_value) {
            count++;
        }
    }
    return count;
}

s32 count_menu_entry_pair_matches(s32 target_value, s32 prefix_value) {
    s32 index;
    s32 count;
    u8 value;
    u8 *page = (u8 *)0x80010000;

    count = 0;
    for (index = 0; index < 0x40; index++) {
        value = page[0x57D2 + index * 0x13];
        if (value == 0) {
            break;
        }
        if ((value == target_value) && (page[0x57D1 + index * 0x13] == prefix_value)) {
            count++;
        }
    }
    return count;
}

s32 find_menu_entry_occurrence(s32 target_value, s32 target_occurrence) {
    s32 occurrence;
    s32 index;
    u8 *page = (u8 *)0x80010000;

    occurrence = 0;
    for (index = 0; index < 0x40; index++) {
        if (page[0x57D2 + index * 0x13] == target_value) {
            if (occurrence == target_occurrence) {
                return index;
            }
            occurrence++;
        }
    }
    return -1;
}

s32 find_menu_entry_from_index(s32 target_value, s32 start_index)
{
    s32 index;

    for (index = start_index; index < 0x40; index++) {
        if (((ovl_1831cd8_81811F04_S_func_80026F04_0 *)((u8 *)0x80010000 + index * 19))->unk_57D2 == target_value) {
            return index;
        }
    }
    return -1;
}

s32 find_menu_entry_pair_occurrence(s32 target_value, s32 prefix_value, s32 target_occurrence)
{
    s32 occurrence;
    s32 index;
    s32 offset;

    occurrence = 0;
    index = occurrence;

    do {
        offset = index * 0x13;
        if ((((u8 *)0x800157C0)[offset + 0x12] == target_value) && (((u8 *)0x800157C0)[offset + 0x11] == prefix_value)) {
            if (occurrence == target_occurrence) {
                return index;
            }
            occurrence++;
        }
        index++;
    } while (index < 0x40);
    return -1;
}

s32 find_menu_entry_by_pair_from_index(s32 match_byte_2, s32 match_byte_1, s32 start_index)
{
    s32 i;
    for (i = start_index; i < 0x40; i++) {
        u8 *e = (u8 *)0x80010000 + i * 19;
        if (e[0x57D2] == match_byte_2 && e[0x57D1] == match_byte_1) {
            return i;
        }
    }
    return -1;
}

s32 pack_selected_menu_entries(s32 held_entry_set, s32 position, s32 entry_count) {
    s32 start_entry;
    s32 buffer;
    s32 entry_index;
    s32 copied_count;
    register s32 write_ptr;
    s32 copy_count;
    ovl_1831cd8_81812008_Entry19 *entries;

    entry_index = position;
    entry_index /= 72;
    copy_count = entry_count;
    buffer = create_callback_pair_default(0x91);
    if (buffer != 0) {
        start_entry = entry_index << 3;
        copy_count -= start_entry;
        if (copy_count >= 9) {
            copy_count = 8;
        }
        entry_index = find_menu_entry_occurrence(held_entry_set, start_entry);
        copied_count = 0;
        if (copy_count > 0) {
            entries = (ovl_1831cd8_81812008_Entry19 *)0x800157C0;
            write_ptr = buffer;
            do {
                strncpy(write_ptr,
                        (u8 *)((u32)(entry_index * 0x13) + (u32)entries), 0x12);
                entry_index = find_menu_entry_from_index(held_entry_set, entry_index + 1);
                copied_count += 1;
                write_ptr += 0x12;
            } while (copied_count < copy_count);
        }
    }
    copied_count = buffer;
    return copied_count;
}

/* MECHANISM: The in-place /72 quotient forces the retail 0x30 frame and s0/s3/s6 argument holds.
   Exact callee arity plus guarded a1/s2 runtime roles reproduce the return-slot and loop coloring.
   Integer index-first addition preserves the retail addu a1,a1,s5 operand order. */

void *get_mapped_menu_table_entry(s32 row_id, s32 entry_index)
{
    s32 row;

    row = 2;
    if (row_id != 0x39) {
        row = row_id;
    }
    return D_800287EC + (row * 0x41) + (entry_index * 0xD);
}

s32 build_menu_text_page(s32 context, s32 scroll_y, s32 entry_count, s32 list_type) {
    s32 slot;
    s32 dest;
    s32 entry_type;
    s32 text_table;
    s32 buffer;

    entry_type = list_type;
    scroll_y /= 72;
    buffer = create_callback_pair_default(0x91);
    if (buffer != 0) {
        entry_count -= scroll_y * 8;
        if (entry_count >= 9) {
            entry_count = 8;
        }
        if (scroll_y == 0) {
            slot = 0;
            dest = slot;
            scroll_y = buffer;
            do {
                func_80069E88(scroll_y, get_mapped_menu_table_entry(entry_type, slot | dest), 0x12);
                slot += 1;
                scroll_y += 0x12;
            } while (slot < 5);
            scroll_y = find_menu_entry_pair_occurrence(context, entry_type, 0);
            if (slot < entry_count) {
                text_table = (s32)0x800157C0;
                dest = (slot * 0x12) + buffer;
                do {
                    func_80069E88(dest, (scroll_y * 0x13) + text_table, 0x12);
                    scroll_y = find_menu_entry_by_pair_from_index(context, entry_type, scroll_y + 1);
                    slot += 1;
                    dest += 0x12;
                } while (slot < entry_count);
                return buffer;
            }
        } else {
            scroll_y = find_menu_entry_pair_occurrence(context, entry_type, (scroll_y * 8) - 5);
            slot = 0;
            if (entry_count > 0) {
                text_table = (s32)0x800157C0;
                dest = buffer;
                do {
                    func_80069E88(dest, (scroll_y * 0x13) + text_table, 0x12);
                    scroll_y = find_menu_entry_by_pair_from_index(context, entry_type, scroll_y + 1);
                    slot += 1;
                    dest += 0x12;
                } while (slot < entry_count);
            }
        }
    }
    return buffer;
}

void *refresh_menu_record_resource(Rec_func_80027328_arg0 *record, s32 resource_arg) {
    func_8004B1A4(record->unk_08);
    record->unk_04 = get_half_byte_length(record->unk_00);
    record->unk_08 = configure_menu_resource(record->unk_00, resource_arg);
    return record;
}

void *rebuild_menu_resource(Rec_func_80027328_arg0 *record, s32 resource_arg) {
    s32 resource_value;

    func_8004B1A4(record->unk_08);
    resource_value = count_menu_entry_matches(record->unk_00);
    record->unk_04 = resource_value;
    record->unk_08 = pack_selected_menu_entries(record->unk_00, resource_arg, resource_value);
    return record;
}

void *refresh_menu_derived_value(ovl_1831cd8_818123E4_S_800273E4_0 *state, s32 replacementInput, s32 calculationInput) {
    s32 adjustedValue;

    func_8004B1A4(state->unk_08);
    adjustedValue = count_menu_entry_pair_matches(state->unk_00, calculationInput) + 5;
    state->unk_04 = adjustedValue;
    state->unk_08 = build_menu_text_page(state->unk_00, replacementInput, adjustedValue, calculationInput);
    return state;
}

void dispatch_menu_state_update(s32 *state, s32 mode, s32 value, s32 extra_value)
{
    if (mode == 0) {
        refresh_menu_record_resource(state, value);
        return;
    }
    if (*state != 0x13) {
        rebuild_menu_resource(state, value);
        return;
    }
    refresh_menu_derived_value(state, value, extra_value);
}

void reset_menu_object_state_2(void *record) {
    ((ovl_1831cd8_818124A8_S_800274A8_0 *)((u8 *)record - 0x10))->unk_00 = (void *)tick_menu_countdown;
    ((ovl_1831cd8_818124A8_S_800274A8_0 *)((u8 *)record - 0x10))->unk_10 = (s32) ((ovl_1831cd8_818124A8_S_800274A8_0 *)((u8 *)record - 0x10))->unk_14;
    reset_object_to_default_data(((ovl_1831cd8_818124A8_S_800274A8_0 *)((u8 *)record - 0x10))->unk_54);
    clear_menu_embedded_state(record - 0x20);
}

void handle_menu_grid_input(ovl_1831cd8_818124F0_S_800274F0_Arg *menu) {
    GameWork *input;
    s32 held_buttons;
    s32 pressed_buttons;
    s32 index_step = 0;
    s32 repeat_ticks;
    s32 next_index;
    s32 selected_index;
    s32 item_count;
    s32 remaining_items;
    s32 repeat_buttons;

    input = &g_game_work;
    held_buttons = input->buttons;
    if (held_buttons == 0)
        return;
    pressed_buttons = ((s32)input->pressed_buttons);
    if (pressed_buttons & 0x20) {
        SD_Call(0x515, input);
        reset_menu_object_state_2(menu);
        return;
    }
    if (pressed_buttons & 0x10) {
        SD_Call(0x503, input);
        reset_menu_object_state_2(menu);
        forward_stored_object_value(menu->unk44);
        return;
    }
    if (pressed_buttons & 0x40) {
        SD_Call(0x503, input);
        dispatch_menu_state_update(&menu->unk38, menu->unk14,
                      (menu->unk8 / 72) * 72, menu->unk28);
        write_text_and_advance_selection(func_8002553C(menu->unk44),
                      menu->unk40 + ((menu->unk8 % 72) * 2));
        if (menu->unk14 == 1 ||
            has_available_object(menu->unk48->unk28) != 0) {
            reset_menu_object_state_2(menu);
            forward_stored_object_value(menu->unk44);
        }
        return;
    }

    if (held_buttons & 0xF000) {
        if (pressed_buttons & 0xF000) {
            menu->unkC = 0;
            pressed_buttons = ((s32)input->pressed_buttons);
            if (pressed_buttons & 0x8000) {
                index_step = -1;
            } else if (pressed_buttons & 0x2000) {
                index_step = 1;
            } else if (pressed_buttons & 0x1000) {
                index_step = -9;
            } else if (pressed_buttons & 0x4000) {
                index_step = 9;
            }
        } else {
            repeat_ticks = menu->unkC;
            if (repeat_ticks >= 9) {
                menu->unkC = repeat_ticks - 1;
                repeat_buttons = input->buttons;
                if (repeat_buttons & 0x8000) {
                    index_step = -1;
                } else if (repeat_buttons & 0x2000) {
                    index_step = 1;
                } else if (repeat_buttons & 0x1000) {
                    index_step = -9;
                } else if (repeat_buttons & 0x4000) {
                    index_step = 9;
                }
            } else {
                menu->unkC = repeat_ticks + 1;
            }
        }
    }

    if (index_step == 0)
        return;
    SD_Call(0x502, input);
    selected_index = menu->unk8;
    item_count = menu->unk3C;
    next_index = selected_index + index_step;
    remaining_items = item_count - next_index;
    if (!(remaining_items > 0 && item_count >= remaining_items))
        return;
    menu->unk8 = next_index;
    if ((next_index - index_step) / 72 == next_index / 72) {
        position_menu_grid_entries(menu->unk88, next_index);
        return;
    }
    clear_menu_state_values(menu->unk88);
    *(void **)((u8 *)menu - 0x10) = (void *)run_menu_countdown_callback;
    menu->unk0 = menu->unk4;

    return;
}

void handle_menu_button_input(void *menu) {
    GameWork *input = &g_game_work;
    s32 held_buttons;
    s32 buttons;
    s32 cursor_step = 0;
    s32 repeat_count;
    s32 new_offset;
    s32 old_offset;
    s32 row_count;
    s32 rows_left;

    held_buttons = input->buttons;
    if (held_buttons == 0) {
        return;
    }

    buttons = ((s32)input->pressed_buttons);
    if (buttons & 0x20) {
        SD_Call(0x515);
        ((ovl_1831cd8_818127A8_S_800277A8_1_pre *)menu)[-1].unk_00 = (void *)tick_menu_countdown;
        ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_00 = ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_04;
        clear_menu_embedded_state((u8 *)menu - 0x20);
        reset_object_to_default_data(((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_44);
        return;
    }

    if (buttons & 0x10) {
        SD_Call(0x503);
        reset_menu_object_state_2(menu);
        forward_stored_object_value(((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_44);
        return;
    }

    if (buttons & 0x40) {
        SD_Call(0x503);
        dispatch_menu_state_update((u8 *)menu + 0x38, ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_14,
                      (((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_08 / 72) * 72,
                      ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_28);
        copy_string_to_object_buffer(func_8002553C(((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_44),
                      ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_40 +
                      (((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_08 % 72) * 2);
        return;
    }

    if (held_buttons & 0x5000) {
        if (buttons & 0x5000) {
            ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_0C = 0;
            buttons = ((s32)input->pressed_buttons);
            if (buttons & 0x1000) {
                cursor_step = -9;
            } else if (buttons & 0x4000) {
                cursor_step = 9;
            }
        } else {
            repeat_count = ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_0C;
            if (repeat_count >= 9) {
                ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_0C = repeat_count - 1;
                buttons = input->buttons;
                if (buttons & 0x1000) {
                    cursor_step = -9;
                } else if (buttons & 0x4000) {
                    cursor_step = 9;
                }
            } else {
                ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_0C = repeat_count + 1;
            }
        }
    }

    if (cursor_step == 0) {
        return;
    }

    SD_Call(0x502);
    new_offset = ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_08 + cursor_step;
    row_count = ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_3C;
    rows_left = row_count - new_offset / 9;
    if (rows_left <= 0 || row_count < rows_left) {
        return;
    }

    old_offset = new_offset - cursor_step;
    ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_08 = new_offset;
    if (new_offset / 72 != old_offset / 72) {
        clear_menu_state_values(((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_88);
        ((ovl_1831cd8_818127A8_S_800277A8_1_pre *)menu)[-1].unk_00 = (void *)run_menu_countdown_callback;
        ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_00 = ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_04;
        return;
    }

    position_menu_grid_entries(((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_88, new_offset);
}

void invoke_enabled_menu_callback(s32 *record) {
    if (record[8] != 0) {
        D_80029514[record[5]](record);
    }
}

void func_80027A68(s32 *record) { invoke_enabled_menu_callback(record); }

void handle_menu_record_check(void *record) {
    if (advance_timed_tagged_stream(record + 0x2C) != 0) {
        ((ovl_1831cd8_81812A88_S_80027A88_0 *)((u8 *)record - 0x10))->unk_00 = (void *)func_80027A68;
        ((ovl_1831cd8_81812A88_S_80027A88_0 *)((u8 *)record - 0x10))->unk_10 = 0;
    }
    invoke_enabled_menu_callback(record);
}

void draw_menu_progress_bar(void *context, s32 currentValue, s32 maxValue) {
    ovl_1831cd8_81812AD0_RECT rect;

    rect = D_80025034[0];
    rect.h = ((s32) (currentValue * 0x90) / maxValue) + 4;
    build_tinted_gradient_rect(*(s32 *)((s8 *)context + 0x4C) + 0x18, &rect, D_80080B54);
}

void store_scaled_menu_ratio(ovl_1831cd8_81812B44_S_80027B44_0 *object, s32 numerator, s32 denominator) {
    ((ovl_1831cd8_81812B44_S_80027B44_2 *)(((ovl_1831cd8_81812B44_S_80027B44_1 *)(object->unk_04))->unk_04))->unk_0A =
        (s16) ((s32) (numerator * 0x90) / denominator);
}

void set_menu_object_scale_fields(s32 object_table, s32 scale_numerator, s32 scale_denominator) {
    s32 scaled_value;
    s32 entry_index;
    s32 scaled_numerator;
    s32 entry_offset;
    void **object_entry;
    void *object;

    entry_index = 6;
    scaled_numerator = scale_numerator * 0x90;
    entry_offset = -0x90;
    object_entry = (void **)(object_table + 0x18);
    do {
        scaled_value = scaled_numerator / scale_denominator;
        object = *object_entry++;
        entry_index++;
        *(s16 *)((u8 *)*(void **)((u8 *)object + 4) + 0xA) =
            scaled_value + entry_offset + 0x90;
        entry_offset += 0x10;
    } while (entry_index < 0xE);
}

void refresh_menu_entry_resources(void *entry_table, void *resource_names)
{
    ovl_1831cd8_81812BBC_Work name_buffer;
    s32 name_offset;
    s32 entry_index;
    ovl_1831cd8_81812BBC_Entry **entry_slot;

    entry_index = 6;
    entry_slot = (ovl_1831cd8_81812BBC_Entry **)((u8 *)entry_table + 0x18);
    name_offset = 0;
    for (;;) {
        ovl_1831cd8_81812BBC_Entry *entry = *entry_slot;
        ovl_1831cd8_81812BBC_Inner *inner = entry->unk4;
        s32 inner_value = inner->unkA;
        name_buffer.unk0 = D_8002503C;

        if (inner_value >= 0x79) {
            if (entry->unk0 == 0) {
                strncat(&name_buffer, (u8 *)resource_names + name_offset, 0x12);
                (*entry_slot)->unk0 = (s32 *)func_8004DC14(&name_buffer, 1);
            }
        } else if (entry->unk0 != 0) {
            func_8004E99C(entry->unk0);
            (*entry_slot)->unk0 = 0;
        }
        entry_slot += 1;
        entry_index += 1;
        name_offset += 0x12;
        if (entry_index >= 0xE) {
            break;
        }
    }
}

void update_menu_object_data(void *object) {
    store_scaled_menu_ratio(((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_88, ((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_00, ((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_04);
    draw_menu_progress_bar(object, ((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_00, ((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_04);
    set_menu_object_scale_fields(((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_88, ((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_00, ((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_04);
    refresh_menu_entry_resources(((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_88, ((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_40);
    advance_timed_tagged_stream(object + 0x2C);
}

void update_menu_progress_bar(ovl_1831cd8_81812D08_ProgressState *state) {
    store_scaled_menu_ratio(state->entries, state->current, state->maximum);
    draw_menu_progress_bar(state, state->current, state->maximum);
    set_menu_object_scale_fields(state->entries, state->current, state->maximum);
    refresh_menu_entry_resources(state->entries, state->resource_names);
    advance_timed_tagged_stream(state->cursor);
}

void dispatch_menu_update_callback(s32 *state) {
    D_8002951C[state[5]](state);
    state[0]++;
    if (state[1] < state[0]) {
        set_entry_destination_and_value(state[34], state[19]);
        position_menu_grid_entries(state[34], state[2]);
        state[-4] = (u32)(void *)handle_menu_record_check;
    }
    invoke_enabled_menu_callback(state);
}

void tick_menu_countdown(s32 *countdownState) {
    D_80029524[countdownState[5]](countdownState);
    countdownState[0]--;
    if (countdownState[0] < 0) {
        countdownState[0] = 0;
        countdownState[-4] = (s32)(void *)handle_menu_record_check;
    }
    invoke_enabled_menu_callback(countdownState);
}

void run_menu_countdown_callback(s32 *state) {
    D_8002952C[state[5]](state);
    state[0]--;
    if (state[0] < 0) {
        state[0] = 0;
        dispatch_menu_state_update((u8 *)state + 0x38, state[5], (state[2] / 72) * 72, state[10]);
        state[-4] = (u32)(void *)dispatch_menu_update_callback;
    }
    invoke_enabled_menu_callback(state);
}

void advance_menu_value_fade(void *state) {
    s32 nextStep;

    ((ovl_1831cd8_81812F34_S_80027F34_2 *)(((ovl_1831cd8_81812F34_S_80027F34_1 *)state)->unk_80))->unk_02 =
        (s16) (0x400 - ((s32) (((ovl_1831cd8_81812F34_S_80027F34_0 *)((u8 *)state - 0x10))->unk_10
        << 0xA) / (s32) ((ovl_1831cd8_81812F34_S_80027F34_0 *)((u8 *)state - 0x10))->unk_14));
    nextStep = ((ovl_1831cd8_81812F34_S_80027F34_0 *)((u8 *)state - 0x10))->unk_10 + 1;
    ((ovl_1831cd8_81812F34_S_80027F34_0 *)((u8 *)state - 0x10))->unk_10 = nextStep;
    if (((ovl_1831cd8_81812F34_S_80027F34_0 *)((u8 *)state - 0x10))->unk_14 < nextStep) {
        ((ovl_1831cd8_81812F34_S_80027F34_0 *)((u8 *)state - 0x10))->unk_10 = 0;
        ((ovl_1831cd8_81812F34_S_80027F34_0 *)((u8 *)state - 0x10))->unk_00 = (void *)func_80027A68;
    }
    invoke_enabled_menu_callback(state);
}

S_800491F4 *link_menu_record_nodes(S_800491F4 **nodes) {
    return build_reverse_indexed_chain(nodes, &D_80029534, 15);
}

S_800491F4 *build_menu_entry_chain(S_800491F4 **nodes) { return build_reverse_indexed_chain(nodes, D_80029544, 15); }

void *initialize_menu_mode_one_fields(ovl_1831cd8_81812FF4_S_80027FF4_0 *object, s32 mode) {
    copy_menu_record_template(object);
    if (mode == 1) {
        object->unk_02 = -0x31;
        object->unk_0E = -0x31;
        object->unk_0A = 0x63;
        object->unk_16 = 0x63;
    }
    return object;
}

void initialize_menu_header_records(void *unused, ovl_1831cd8_81813050_Header *header, ovl_1831cd8_81813050_Template0 *record_a, ovl_1831cd8_81813050_Record1 *record_b) {
    ovl_1831cd8_81813050_Template0 *defaults_a = &D_8002E5D8;
    ovl_1831cd8_81813050_Template1 *defaults_b = &D_8002E5E8;
    s32 *first_word;

    record_a->unk0 = defaults_a->unk0;
    first_word = &defaults_b->unk0;
    record_a->unk4 = defaults_a->unk4;
    record_a->unk8 = defaults_a->unk8;
    record_a->unkC = defaults_a->unkC;

    ((ovl_1831cd8_81813050_Template1 *)record_b)->unk0 = *first_word;
    ((ovl_1831cd8_81813050_Template1 *)record_b)->unk4 = defaults_b->unk4;
    ((ovl_1831cd8_81813050_Template1 *)record_b)->unk8 = defaults_b->unk8;

    header->unk4 = (ovl_1831cd8_81813050_Record0 *)record_a;
    header->unk8 = record_b;
    header->unk0 = 0;

    header->unk4->unk8 = -0x58;
    header->unk4->unkA = -0x40;
    header->unk4->unkC = 0x200;
    header->unk8->unk2 = 0x400;
    header->unk8->unk6 = -0x50;
    header->unk4->unkF = 4;
}

void initialize_menu_panel_rows(void *panel, void *widgets) {
    s16 row_y;
    s16 row_x;
    s32 slot_index;
    void **widget_slot;
    ovl_1831cd8_818130FC_S_800280FC_3 *widget_data;

    *((ovl_1831cd8_818130FC_S_800280FC_0 *)widgets)->unk_00 = &D_80078AB4;
    *((ovl_1831cd8_818130FC_S_800280FC_0 *)widgets)->unk_04 = &D_80078AD8;
    func_8004CBFC(panel + 0x2C, &D_80079324, ((ovl_1831cd8_818130FC_S_800280FC_0 *)widgets)->unk_08);
    *((ovl_1831cd8_818130FC_S_800280FC_0 *)widgets)->unk_0C = 0;
    ((ovl_1831cd8_818130FC_S_800280FC_6 *)(((ovl_1831cd8_818130FC_S_800280FC_4 *)widgets)->unk_10))->unk_00 = 0;
    ((ovl_1831cd8_818130FC_S_800280FC_9 *)(((ovl_1831cd8_818130FC_S_800280FC_6 *)(((ovl_1831cd8_818130FC_S_800280FC_4 *)widgets)->unk_10))->unk_04))->unk_08 = 0x58;
    *((ovl_1831cd8_818130FC_S_800280FC_0 *)widgets)->unk_14 = ((ovl_1831cd8_818130FC_S_800280FC_1 *)panel)->unk_4C + 0x18;
    draw_menu_progress_bar(panel, 0, 1);
    slot_index = 6;
    row_x = 0x58;
    row_y = 0x90;
    widget_slot = widgets + 0x18;
    do {
        ((ovl_1831cd8_818130FC_S_800280FC_2 *)(*widget_slot))->unk_00 = 0;
        ((ovl_1831cd8_818130FC_S_800280FC_7 *)(((ovl_1831cd8_818130FC_S_800280FC_5 *)(*widget_slot))->unk_04))->unk_08 = row_x;
        slot_index += 1;
        widget_data = ((ovl_1831cd8_818130FC_S_800280FC_2 *)(*widget_slot))->unk_04;
        widget_slot = (void **)((s8 *)((void **)((s8 *)widget_slot + 4)));
        widget_data->unk_0A = row_y;
        row_y += 0x10;
    } while (slot_index < 0xE);
    ((ovl_1831cd8_818130FC_S_800280FC_10 *)(((ovl_1831cd8_818130FC_S_800280FC_8 *)(((ovl_1831cd8_818130FC_S_800280FC_4 *)widgets)->unk_38))->unk_04))->unk_08 = 0x4C;
    ((ovl_1831cd8_818130FC_S_800280FC_8 *)(((ovl_1831cd8_818130FC_S_800280FC_4 *)widgets)->unk_38))->unk_00 = 0;
}

void initialize_menu_record_range(void *record, s32 range_start, s32 value) {
    *(s32 *)((u8 *)record + 0x44) = range_start;
    range_start += 0x20;
    *(s32 *)((u8 *)record + 0x04) = 4;
    *(s32 *)((u8 *)record + 0x48) = range_start;
    *(s32 *)((u8 *)record + 0x18) = value;
    *(s32 *)record = 0;
    *(u8 **)((u8 *)record - 0x10) = (void *)advance_menu_value_fade;
}

void initialize_menu_object_from_data(void *object, s32 init_value, s32 init_value_2) {
    initialize_menu_record_range(object, init_value, init_value_2);
    initialize_menu_header_records(object, object + 0x78, object + 0x50, object + 0x60);
    initialize_menu_panel_rows(object, ((Rec_func_80027AD0_arg0 *)object)->unk_88);
}

s32 allocate_menu_object_buffers(ovl_1831cd8_81813284_Unk818110CC *object, s32 buffer_param)
{
    s32 success = 0;
    s32 *buffers = object->unk8C;
    s32 allocated_buffer;

    allocated_buffer = func_80049004(buffers, buffer_param, 8);
    object->unk88 = allocated_buffer;
    if (allocated_buffer != 0) {
        allocated_buffer = func_80048FBC(buffers, 8);
        object->unk4C = allocated_buffer;
        if (allocated_buffer != 0) {
            object->unk6C[0] = D_8002E5E8.unk0;
            object->unk6C[1] = D_8002E5E8.unk4;
            object->unk6C[2] = D_8002E5E8.unk8;
            texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(object->unk88, object->unk6C, 15);
            success = 1;
        }
    }
    return success;
}

void initialize_menu_object_state(s32 object_addr, s32 initial_value) {
    void *state;

    state = object_addr + 0x20;
    ((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_24 = 0;
    ((ovl_1831cd8_81813320_S_80028320_2 *)(((ovl_1831cd8_81813320_S_80028320_1 *)state)->unk_80))->unk_02 = 0;
    ((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_48 = initial_value;
    ((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_18 = 0;
    dispatch_menu_state_update(object_addr + 0x58, ((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_24, 0,
        ((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_38);
    initialize_menu_mode_one_fields(((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_5C, ((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_24);
    ((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_94 = (s32)link_menu_record_nodes(((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_98);
    format_menu_referenced_values(((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_98);
    func_80028648(object_addr);
    ((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_00 = (void *)dispatch_menu_update_callback;
}

void install_menu_object_handler(s32 object_addr) {
    void *object_state;

    object_state = object_addr + 0x20;
    ((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_14 = 1;
    ((ovl_1831cd8_818133B4_S_800283B4_1 *)(((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_80))->unk_02 = 0;
    ((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_08 = 0;
    ((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_28 = ((ovl_1831cd8_818133B4_S_800283B4_2 *)(((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_48))->unk_1C;
    ((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_38 = ((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_18;
    dispatch_menu_state_update(object_addr + 0x58, ((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_14, 0,
        ((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_28);
    initialize_menu_mode_one_fields(((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_4C, ((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_14);
    ((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_84 = (s32)link_menu_record_nodes(((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_88);
    format_menu_referenced_values(((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_88);
    func_80028648(object_addr);
    ((ovl_1831cd8_818133B4_S_800283B4_0_pre *)object_state)[-1].unk_00 = (void *)dispatch_menu_update_callback;
}

void *create_menu_child_object(s32 parent_obj, s32 descriptor_value)
{
    ovl_1831cd8_8181345C_Obj8181345C *obj;
    ovl_1831cd8_8181345C_Sub8181345C *sub;

    obj = func_8003FC64(0);
    sub = &obj->sub;
    if (obj != 0) {
        if (allocate_menu_object_buffers(sub, 15) != 0) {
            obj->field0C = (u8 *)obj + 0x98;
            sub->field84 = build_menu_entry_chain(sub->field88);
            initialize_menu_object_from_data(sub, parent_obj, descriptor_value);
            register_node(obj, (void *)draw_tinted_node_sprites_scratch);
            clear_menu_embedded_state(obj);
        } else {
            release_null_terminated_entries((u8 *)obj + 0xAC);
            obj->flags |= 0x8000;
            obj = 0;
            object_flag_block.flags |= 0x8000;
        }
    }
    return obj;
}

void format_menu_referenced_values(void *state) {
    s32 **value_slot;
    s32 slot_index;

    slot_index = 6;
    value_slot = state + 0x18;
    do {
        slot_index += 1;
        func_8004E99C(**value_slot);
        **value_slot = 0;
        value_slot += 1;
    } while (slot_index < 0xE);
    func_8004E99C(**(s32 **)((u8 *)state + 0x38));
}

void retire_menu_object(void *object)
{
    u8 *objectData;
    u16 objectFlags;
    s32 globalFlags;

    if (object != 0) {
        objectData = (u8 *)object + 0x20;
        format_menu_referenced_values(*(void **)(objectData + 0x88));
        func_8004B1A4(*(void **)(objectData + 0x40));
        release_null_terminated_entries((u8 *)object + 0xAC);
        objectFlags = *(u16 *)((u8 *)object + 0x1E);
        globalFlags = object_flag_block.flags;
        *(u16 *)((u8 *)object + 0x1E) = objectFlags | 0x8000;
        object_flag_block.flags = globalFlags | 0x8000;
    }
}

void clear_menu_embedded_state(s32 object_addr) {
    ovl_1831cd8_81813620_S_80028620_0 *state;

    state = object_addr + 0x20;
    state->unk_20 = 0;
    clear_menu_state_values(state->unk_88);
}

void func_80028648(ovl_1831cd8_81813648_ReadyState *state) { state->ready = 1; }

void *build_menu_draw_packets(void *packet, void *coords) {
    u32 packet_type;
    u8 *coord_bytes = (u8 *)coords;

    *(u32 *)((u8 *)packet + 4) = D_8002954C;
    *((u8 *)packet + 1) = 0x48;
    *((u8 *)packet + 2) = coord_bytes[0];
    *((u8 *)packet + 3) = coord_bytes[2];
    *((u8 *)packet + 0xA) = coord_bytes[4];
    *((u8 *)packet + 0xB) = coord_bytes[6];

    packet = (u8 *)packet + 0xC;

    *(u32 *)((u8 *)packet + 4) = D_8002954C;
    *((u8 *)packet + 1) = 0x48;
    *((u8 *)packet + 2) = coord_bytes[0];
    *((u8 *)packet + 3) = coord_bytes[2];
    *((u8 *)packet + 0xA) = coord_bytes[4] + 1;
    *((u8 *)packet + 0xB) = coord_bytes[6] + 1;

    packet = (u8 *)packet + 0xC;

    *(u32 *)((u8 *)packet + 4) = D_80029548;
    *((u8 *)packet + 1) = 0x48;
    *((u8 *)packet + 2) = coord_bytes[0];
    *((u8 *)packet + 3) = coord_bytes[2];
    *((u8 *)packet + 0xA) = coord_bytes[4];
    *((u8 *)packet + 0xB) = coord_bytes[6];
    packet_type = 3;
    *((u8 *)packet + 0) = packet_type;

    packet = (u8 *)packet + 0xC;

    *(u32 *)((u8 *)packet + 4) = D_80029548;
    *((u8 *)packet + 1) = 0x48;
    *((u8 *)packet + 2) = coord_bytes[0];
    *((u8 *)packet + 3) = coord_bytes[2];
    *((u8 *)packet + 0xA) = coord_bytes[4] + 1;
    *((u8 *)packet + 0xB) = coord_bytes[6] + 1;
    *((u8 *)packet + 0) = packet_type;
    return packet;
}

ovl_1831cd8_81813774_UnalignedBlock12 *copy_menu_record_template(ovl_1831cd8_81813774_UnalignedBlock12 *dest) {
    dest[0] = D_80029550.chunks[0];
    dest[1] = D_80029550.chunks[1];
    return dest;
}

/* MECHANISM: Frameless leaf split into two packed 12-byte aggregate copies.
   Returning the destination makes the $v0 return value the store base, which
   yields retail's leading move $v0,$a0 and the $a0/$a1/$a2 copy registers. */

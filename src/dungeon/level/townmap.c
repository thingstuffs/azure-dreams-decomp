#include "dungeon/level/townmap.h"


void process_pending_resource_load(void)
{
    s32 entry_result;
    s32 *entry_table;

    if (D_800CF874[0] != 0) {
        func_80067014(0);
        entry_table = &D_800CF838[15];
        entry_result = load_cd_resource(entry_table[D_800CF874[0]]);
        D_80081458[0] = entry_result;
        if (D_800CF874[0] == 1) {
            D_800CF874[0] = 0;
            return;
        }
        D_800CF874[0] = 1;
    }
}

void write_resource_command(s32 value, s32 command) {
    D_800CFC24[3] = (s8)(value >> 8);
    D_800CFC24[2] = value;
    D_800CFC24[4] = (s8)(value >> 0x10);
    D_800CFC24[5] = (s8)(value >> 0x18);
    D_800CFC24[6] = command;
    call_script(&D_800CFC24);
}

void send_resource_command_23(s32 entry_index) {
    write_resource_command(D_800CFBA0[entry_index], 0x23);
}

s32 town_map_set(s32 value_7c, s32 value_78) {
    register s32 count;
    void *objects[11];
    void *resources[11];
    void **object_cursor;
    void **resource_cursor;
    void *object;
    void *resource;
    count = 0;
    object_cursor = objects;
    resource_cursor = resources;
    while (1) {
        object = func_8003FC64(0x11);
        if (object == 0) {
            break;
        }
        resource = runtime_find_unused_pool_slot();
        if (resource == 0) {
            break;
        }
        runtime_initialize_state_value(resource, 0);
        *object_cursor++ = object;
        *resource_cursor++ = resource;
        count++;
        if (count >= 11) {
            break;
        }
    }

    if (count < 11) {
        if (object_cursor != objects) {
            do {
                --object_cursor;
                unlink_active_node(*object_cursor);
                push_node_onto_free_list(*object_cursor);
            } while (object_cursor != objects);
            ++object_cursor;
        }
        if (resource_cursor != resources) {
            do {
                --resource_cursor;
                runtime_clear_value(*resource_cursor);
            } while (resource_cursor != resources);
        }
        return 0;
    }

    object_cursor = objects;
    resource_cursor = resources;
    count = 0;
    {
        s8 *link_slots = &D_800CFC2C;
        while (1) {
            s8 linked_slot = *(s8 *)(count + (s32)link_slots);
            void *linked_data;
            if (linked_slot == count) {
                linked_data = 0;
            } else {
                linked_data = (u8 *)objects[linked_slot] + 0x20;
            }
            {
                struct object_data {
                    u8 pad[0x74];
                    s32 field_74;
                    s32 field_78;
                    s32 field_7c;
                } *payload = (struct object_data *)((u8 *)*object_cursor + 0x20);
                payload->field_74 = 0;
                payload->field_78 = value_78;
                payload->field_7c = value_7c;
                initialize_town_map_object_state(count++, linked_data, *object_cursor++, *resource_cursor++);
            }
            if (count >= 11) {
                D_800FC418 = 0;
                return 1;
            }
        }
    }
}

s32 town_map_del(void) {
    D_800FC418 = 0xFF;
    return 1;
}

s32 clear_town_map_status(void) {
    D_800FC418 = 0;
    return 1;
}

void initialize_town_map_object_state(s32 mode, s32 *list, u8 *init_context, u8 *target_object) {
    u8 *context = init_context;
    u8 *object = target_object;
    u8 *record;
    u8 *transform;
    u8 *display;
    s32 list_value;
    u32 *mode_table;
    u32 mode_entry;


    *(Callback *)(context + 0x10) = func_8008B9D8;
    register_node(context, &D_80033D54);
    transform = *(u8 **)(context + 8);
    display = *(u8 **)(context + 0xC);

    record = context + 0x20;
    list_value = 0;
    if (list != 0) {
        list_value = *list;
    }
    runtime_initialize_state_value(object, list_value);
    mode_table = D_800CFB74;
    *(u8 **)(context + 0x20) = object;
    *(u32 *)(object + 0x60) = 2;
    *(u32 *)(record + 4) = 0;
    *(u16 *)(record + 0x66) = (u16)mode;
    mode_entry = mode_table[mode];
    if (mode_entry != 0) {
        *(u8 **)(record + 8) = &D_80037714;
        copy_window_params(record, mode_entry);
    } else {
        *(u8 **)(record + 8) = 0;
    }
    *(u16 *)(record + 0x60) = 0;
    *(u32 *)(display + 0xC) = 0x00808080;
    if ((u32)(mode - 9) < 2U) {
        func_8003DB94(display, &D_800794AC, 0);
    } else {
        *(u32 *)(display + 8) = 0;
    }
    if (mode == 0) {
        *(s16 *)(transform + 2) = 0x20;
        *(s16 *)(transform + 6) = -0x20;
        *(s16 *)(transform + 0xA) = 0x200;
    }
    if (mode == 10) {
        *(u32 *)(record + 0x74) = 0;
        D_80082ABC = *(u8 *)(*(u8 **)(record + 0x7C));
    }
    *(Callback *)(record + 0x68) = advance_town_map_countdown_callback;
    *(s16 *)(record + 0x64) = (s16)(s8)D_800CFC38[mode];
    *(u32 *)(record + 0x6C) = D_800CFC44[mode];
    if (mode == 9) {
        unlink_node_if_registered(record);
    }
}

void func_8008B9D8(town_map_7FFEE278_S_8008B9D8_0 *object) {
    object->unk_68((struct Struct_7FFEE2A0 *)object);
}

void advance_town_map_countdown_callback(town_map_7FFEE2A0_Struct_7FFEE2A0 *state) {
    state->unk64--;
    if (state->unk64 < 0) {
        void (*next_callback)(void) = state->unk6C;
        state->unk68 = next_callback;
        next_callback();
    }
}

void decrease_town_map_object_field_0a_and_transition(town_map_7FFEE2E4_S_8008BA44_0 *state) {
    town_map_7FFEE2E4_S_8008BA44_1 *object;
    town_map_7FFEE2E4_S_8008BA44_2 *checked_object;
    s32 next_value;

    object = state->unk_00;
    object->unk_0A = (u16) (object->unk_0A - 0x100);
    checked_object = state->unk_00;
    if ((s16) checked_object->unk_0A < 0) {
        checked_object->unk_0A = 0U;
        state->unk_68 = (s32 *)handle_town_map_input;
        state->town_map_7FFEE2E4_unk_64.s = (s16) (s8) D_800CFC70[state->unk_66];
        next_value = D_800CFC7C[state->unk_66];
        state->town_map_7FFEE2E4_unk_64.u = 0x16;
        state->unk_6C = next_value;
    }
}

void decrease_inner_value_and_load_indexed_state(town_map_7FFEE36C_MainStruct *state) {
    state->sub->unkA -= 0x200;
    if ((s16)state->sub->unkA < 0) {
        state->sub->unkA = 0;
        state->unk68 = (void *)handle_town_map_input;
        state->unk64 = (s8)D_800CFC70[state->unk66];
        state->unk6C = D_800CFC7C[state->unk66];
    }
}

void advance_inner_value_and_load_indexed_state(town_map_7FFEE3F0_Actor *actor) {
    town_map_7FFEE3F0_SubStruct *sub = actor->sub;

    sub->unk8 += 0x200;
    if ((s16)actor->sub->unk8 > 0) {
        actor->sub->unk8 = 0;
        actor->unk68 = (void *)handle_town_map_input;
        actor->unk64 = D_800CFC70[actor->unk66];
        actor->unk6C = D_800CFC7C[actor->unk66];
    }
}

void decrease_substructure_value_and_reset(town_map_7FFEE474_MainStruct *object) {
    object->sub->unk8 -= 0x200;
    if ((s16)object->sub->unk8 < 0) {
        object->sub->unk8 = 0;
        object->unk68 = (void *)handle_town_map_input;
        object->unk64 = (s8)D_800CFC70[object->unk66];
        object->unk6c = D_800CFC7C[object->unk66];
    }
}

void handle_town_map_input(u8 *object, town_map_7FFEE4F8_S_8008BC58_2 *view_params, void *update_context)
{
    GameWork *input = &g_game_work;
    u8 *selection_ids = ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_7C;
    u8 *display_record;
    s16 state;

    if (D_800FC418 != 0) {
        ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_68 = (void *)restore_town_map_input_state;
        return;
    }

    state = ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_66;
    if (state == 0) {
        u16 input_delay;
        s32 buttons;

        input_delay = ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_64 - 1;
        ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_64 = input_delay;
        if ((input_delay << 16) <= 0) {
            ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_64 = 0;
            if (((s32)input->pressed_buttons) & 0x10000000) {
                view_params->unk_0A += 0x10;
            }
            if (((s32)input->pressed_buttons) & 0x40000000) {
                view_params->unk_0A -= 0x10;
            }
            buttons = ((s32)input->pressed_buttons);
            if (buttons & 0x40) {
                D_800FC418 = 1;
                call_script(D_80072214);
                return;
            }
            if (buttons & 0x20) {
                D_800FC418 = 1;
                call_script(D_80072210);
                return;
            }
        } else {
            return;
        }
    } else if (state == 9) {
        s32 x;
        s32 y;

        func_800478B8(update_context);
        display_record = *(u8 **)object;
        x = D_80083780.x.w.i / 64 - 0x18;
        ((town_map_7FFEE4F8_S_8008BC58_3 *)display_record)->unk_30 = x;
        display_record = *(u8 **)object;
        y = D_80083780.y.w.i / 64 - 0x40;
        ((town_map_7FFEE4F8_S_8008BC58_3 *)display_record)->unk_34 = y;
        return;
    } else if (state == 10) {
        s32 selection_index;
        s32 selection_index_2;
        s32 selection_index_3;
        s32 selection_index_4;
        s32 selection_index_5;
        s32 selection_index_6;
        u8 selection_id;
        u8 *selection_positions;
        s32 buttons;

        func_800478B8(update_context);
        buttons = ((s32)input->pressed_buttons);
        if (buttons & 0x6000) {
            selection_index = ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_74 + 1;
            ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_74 = selection_index;
            if (selection_index >= ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_78) {
                ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_74 = 0;
            }
            send_resource_command_23(selection_ids[((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_74]);
        } else if (buttons & 0x9000) {
            selection_index_2 = ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_74 - 1;
            ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_74 = selection_index_2;
            if (selection_index_2 < 0) {
                selection_index_3 = ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_78 - 1;
                ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_74 = selection_index_3;
            }
            send_resource_command_23(selection_ids[((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_74]);
        }

        selection_index_4 = ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_74;
        selection_positions = D_800D2EA4;
        selection_id = selection_ids[selection_index_4];
        ((town_map_7FFEE4F8_S_8008BC58_3 *)(*(u8 **)object))->unk_30 = selection_positions[selection_id * 8] - 0x18;

        selection_index_5 = ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_74;
        selection_id = selection_ids[selection_index_5];
        display_record = *(u8 **)object;
        ((town_map_7FFEE4F8_S_8008BC58_3 *)display_record)->unk_34 = selection_positions[selection_id * 8 + 1] - 0x40;

        selection_index_6 = ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_74;
        selection_id = selection_ids[selection_index_6];
        D_80082ABC = selection_id;
    }

    return;
}

void restore_town_map_input_state(town_map_7FFEE778_S_8008BED8_0 *state) {
    s32 *handler;
    u32 status = D_800FC418;

    if (status == 0xFF) {
        handler = (s32 *)advance_town_map_countdown_callback;
    } else if (status == 0) {
        handler = (s32 *)handle_town_map_input;
    } else {
        return;
    }
    state->unk_68 = handler;
}

void release_town_map_record(void *record) {
    int global_flags;
    runtime_clear_value(*(void **)record);
    ((u16 *)record)[-1] |= 0x8000;
    global_flags = object_flag_block.flags;
    ((s32 *)record)[-4] = 0;
    object_flag_block.flags = global_flags | 0x8000;
}

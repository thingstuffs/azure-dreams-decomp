#include "dungeon/menu/selection.h"


void set_indexed_object_field(ovl_1831370_81811370_S_80026370_0 *object, s32 index) {
    ((ovl_1831370_81811370_S_80026370_2 *)(((ovl_1831370_81811370_S_80026370_1 *)(object->unk_04))->unk_04))->unk_08 = (s16) ((index * 8) - 0x18);
}

s32 adjust_selection_by_item_count(s32 input_value, s32 target, s32 lookup_index)
{
    return advance_index_with_single_wrap(target, input_value, D_800294F8[lookup_index]);
}

void inventory_set_object_entry_address(ovl_1831370_818113C0_S_800263C0_0 *object, s32 source) {
    release_object_handle(object);
    *object->unk_0C = func_8004DC14(source, 0);
}

void update_menu_selection_from_input(ovl_1831370_8181140C_MenuState *menu) {
    s32 direction = 0;
    s32 buttons;
    s32 repeat_ticks;
    s32 selection;

    if (g_game_work.buttons != 0) {
        if (((s32)g_game_work.pressed_buttons) & 0xC) {
            menu->field4 = 0;
            buttons = ((s32)g_game_work.pressed_buttons);
            if (buttons & 4) {
                direction = -1;
            } else if (buttons & 8) {
                direction = 1;
            }
        } else if (g_game_work.buttons & 0xC) {
            repeat_ticks = menu->field4;
            if (repeat_ticks >= 9) {
                menu->field4 = repeat_ticks - 1;
                buttons = g_game_work.buttons;
                if (buttons & 4) {
                    direction = -1;
                } else if (buttons & 8) {
                    direction = 1;
                }
            } else {
                menu->field4 = repeat_ticks + 1;
            }
        }

        if (direction != 0) {
            SD_Call(0x502);
            selection = adjust_selection_by_item_count(direction, menu->field8, menu->field10);
            menu->field8 = selection;
            set_indexed_object_field(menu->field70, selection);
        }
    }
}

void update_embedded_state_from_table(s32 object_addr) {
    s32 updated_value;
    ovl_1831370_81811508_S_80026508_0 *state;

    state = object_addr + 0x20;
    updated_value = adjust_selection_by_item_count(-1, state->unk_08, state->unk_10);
    state->unk_08 = updated_value;
    set_indexed_object_field(state->unk_70, updated_value);
}

void clear_object_buffer_and_state(s32 objectAddress)
{
    ovl_1831370_8181154C_S_8002654C_0 *objectState;

    objectState = (void *)(objectAddress + 0x20);
    memset(objectState->unk_14, 0,
           (D_800294F8[objectState->unk_10] * 2) | 1);
    inventory_set_object_entry_address(objectState->unk_70, objectState->unk_14);
    objectState->unk_08 = 0;
    set_indexed_object_field(objectState->unk_70, 0);
}

void write_text_and_advance_selection(s32 objectAddress, s32 updateValue) {
    s32 updatedValue;
    s32 *object;

    object = (s32 *)(objectAddress + 0x20);
    write_char_pair(object[5], updateValue, object[2]);
    inventory_set_object_entry_address(object[28], object[5]);
    updatedValue = adjust_selection_by_item_count(1, object[2], object[4]);
    object[2] = updatedValue;
    set_indexed_object_field(object[28], updatedValue);
}

void copy_string_to_object_buffer(s8 *object, s32 sourceString) {
    ovl_1831370_8181161C_Func8181161CData *textData = (ovl_1831370_8181161C_Func8181161CData *)(object + 0x20);

    memset(textData->field_14, 0, (D_800294F8[textData->index] << 1) | 1);
    strcpy(textData->field_14, sourceString);
    inventory_set_object_entry_address(textData->field_70, textData->field_14);
}

/* Forward the complete menu object to its update routine. */
void forward_menu_object_to_selection_updater(ovl_1831370_8181140C_MenuState *menu) { update_menu_selection_from_input(menu); }

void apply_step_and_reset_after_five(s32 *step) {
    s32 step_value = *step << 10;

    *(s16 *) (*(s32 *) ((u8 *) step + 0x64) + 6) = step_value;
    *step += 1;
    if (*step >= 5) {
        *step = 0;
        *(void **) ((u8 *) step - 0x10) = (void *)forward_menu_object_to_selection_updater;
    }
    update_menu_selection_from_input((ovl_1831370_8181140C_MenuState *)step);
}

void *initialize_variant_packet(ovl_1831370_81811708_Packet *packet, s32 variant) {
    s32 payload;

    packet->unk1 = 0x28;
    payload = D_800294FC;
    packet->unk2 = -0x21;
    packet->unk3 = 5;
    packet->unk4 = payload;
    packet->unkA = (variant == 1) ? 0x42 : 0x5A;
    packet->unkB = 0x16;
    packet->unk0 = 0x80;
    return packet;
}

void set_descriptor_fields_and_flag(void *descriptor)
{
    s32 saved_settings;
    s32 settings;

    saved_settings = 0x8040F0;
    *(s8 *)((u8 *)descriptor + 1) = 0x28;
    settings = *(s32 *)&saved_settings;
    *(s8 *)((u8 *)descriptor + 3) = 0x18;
    *(s8 *)((u8 *)descriptor + 0xA) = 7;
    *(s8 *)((u8 *)descriptor + 2) = 0;
    *(s8 *)((u8 *)descriptor + 0xB) = 2;
    *(s32 *)((u8 *)descriptor + 4) = settings;
    *(u8 *)descriptor |= 0x80;
}

S_800491F4 *forward_value_to_shared_helper(S_800491F4 **value) {
    return build_reverse_indexed_chain(value, D_80029500, 4);
}

void initialize_owner_defaults(void *unused, ovl_1831370_818117D8_Owner *owner, ovl_1831370_818117D8_S_8002E5D8 *patch_data,
                   ovl_1831370_818117D8_S_8002E5E8 *aux_data) {
    ovl_1831370_818117D8_S_8002E5D8 *patch_defaults = &D_8002E5D8;
    ovl_1831370_818117D8_S_8002E5E8 *aux_defaults = &D_8002E5E8;
    s32 *aux_first_word;

    patch_data->unk0 = patch_defaults->unk0;
    aux_first_word = &aux_defaults->unk0;
    patch_data->unk4 = patch_defaults->unk4;
    patch_data->unk8 = patch_defaults->unk8;
    patch_data->unkC = patch_defaults->unkC;

    aux_data->unk0 = *aux_first_word;
    aux_data->unk4 = aux_defaults->unk4;
    aux_data->unk8 = aux_defaults->unk8;

    owner->unk4 = (ovl_1831370_818117D8_PatchRecord *)patch_data;
    owner->unk8 = aux_data;
    owner->unk0 = 0;

    owner->unk4->unk8 = -96;
    owner->unk4->unkA = -112;
    owner->unk4->unkC = 0x200;
    owner->unk4->unk6 = 0;
    owner->unk4->unkF = 4;
}

void initialize_object_destination_fields(ovl_1831370_81811878_Source *src, ovl_1831370_81811878_Destinations *dst)
{
    *dst->dst0 = D_80029508[src->word10];
    *dst->dst4 = &src->word2C;
    set_indexed_object_field(dst, 0);
    *dst->dst8 = &src->word20;
    dst->dstC->unk0 = func_8004DC14(src->word14, 0);
    dst->dstC->unk4->unk8 = 0x68;
    dst->dstC->unk4->unkA = 0x88;
}

void initialize_object_phase_data(void *recordFields, s32 recordValue2C, s32 typeCode, s32 recordValue24) {
    s32 isType13;

    ((ovl_1831370_8181192C_S_8002692C_0 *)((u8 *)recordFields - 0x10))->unk_1C = typeCode;
    isType13 = typeCode == 0x13;
    ((ovl_1831370_8181192C_S_8002692C_0 *)((u8 *)recordFields - 0x10))->unk_20 = isType13;
    initialize_variant_packet(recordFields + 0x20, isType13);
    set_descriptor_fields_and_flag(recordFields + 0x2C);
    ((ovl_1831370_8181192C_S_8002692C_0 *)((u8 *)recordFields - 0x10))->unk_24 = recordValue24;
    ((ovl_1831370_8181192C_S_8002692C_0 *)((u8 *)recordFields - 0x10))->unk_2C = recordValue2C;
    ((ovl_1831370_8181192C_S_8002692C_0 *)((u8 *)recordFields - 0x10))->unk_00 = (void *)apply_step_and_reset_after_five;
}

void initialize_embedded_object_state(void *state, s32 parent, s32 type, s32 config) {
    initialize_object_phase_data(state, parent, type, config);
    initialize_owner_defaults(state, state + 0x60, state + 0x38, state + 0x48);
    initialize_object_destination_fields(state, ((ovl_1831370_818119A0_S_800269A0_0 *)state)->unk_70);
}

s32 get_and_position_object_handle(void *object)
{
    ovl_1831370_818119E8_Vec3 *initial_pos;
    s32 success = 0;

    if ((*(s32 *)((s8 *)object + 0x70) = func_80048EE4((s8 *)object + 0x74, 4)) != 0) {
        initial_pos = &D_8002E5E8;
        *(s32 *)((s8 *)object + 0x54) = initial_pos->x;
        *(s32 *)((s8 *)object + 0x58) = initial_pos->y;
        *(s32 *)((s8 *)object + 0x5C) = initial_pos->z;
        texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(*(s32 *)((s8 *)object + 0x70), (s8 *)object + 0x54, 4);
        success = 1;
    }
    return success;
}

void *allocate_initialized_child_object(s32 parent_object, s32 type_code, s32 config_value) {
    u8 *object;
    u8 *state;

    object = func_8003FC64(0);
    state = object + 0x20;
    if (object != 0) {
        if (get_and_position_object_handle(state) != 0) {
            *(void **)(object + 0xC) = object + 0x80;
            *(s32 *)(state + 0x6C) = (s32)forward_value_to_shared_helper(*(S_800491F4 ***)(state + 0x70));
            initialize_embedded_object_state(state, parent_object, type_code, config_value);
            register_node(object, draw_tinted_node_sprites_scratch);
        } else {
            func_8004B1A4(*(s32 *)(state + 0x74));
            *(u16 *)(object + 0x1E) |= 0x8000;
            object = 0;
            object_flag_block.flags |= 0x8000;
        }
    }
    return object;
}

void release_object_handle(ovl_1831370_81811B44_S_80026B44_0 *owner) {
    s32 handle;

    handle = *owner->unk_0C;
    if (handle != 0) {
        func_8004E99C(handle);
        *owner->unk_0C = 0;
    }
}

void cleanup_object_resources(ovl_1831370_81811B94_CleanupObject *object)
{
    ovl_1831370_81811B94_CleanupData *cleanup;

    if (object != 0) {
        cleanup = &object->cleanup;
        release_object_handle(cleanup->field_70);
        func_8004B1A4(cleanup->field_74);
        object->flags |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

u32 has_available_object(void *object) {
    if (object != 0) {
        if (*(s32 *)((s8 *)object + 0x28) == 0) {
            return 1;
        }
    }
    return 0;
}

s32 check_object_byte_pairs_content(s32 object_addr) {
    s32 byte_count;
    s32 loop_bound;
    u8 compare_space;
    s32 pair_count;
    s32 byte_offset;
    s32 has_content;
    u8 first_byte;
    u8 default_first;
    ovl_1831370_81811C20_S_80026C20_0 *pair_info;
    void *pair_data;
    ovl_1831370_81811C20_S_80026C20_1 *pair;
    u8 *default_pair;

    has_content = 0;
    if (object_addr != 0) {
        pair_info = object_addr + 0x20;
        pair_count = 9;
        if (pair_info->unk_0C == 0x13) {
            pair_count = 6;
        }
        byte_count = pair_count * 2;
        byte_offset = 0;
        if (has_content < byte_count) {
            default_pair = D_80029510;
            compare_space = 0x20;
            loop_bound = byte_count;
            pair_data = pair_info->unk_14;
            default_first = D_80029510[0];
next_pair:
            pair = pair_data + byte_offset;
            first_byte = pair->unk_00;
            if (first_byte != 0) {
                if (((first_byte != default_first) ||
                     (pair->ovl_1831370_81811C20_unk_01.s !=
                      default_pair[1])) &&
                    ((first_byte != compare_space) ||
                     (pair->ovl_1831370_81811C20_unk_01.u != first_byte))) {
                    has_content = 1;
                }
                byte_offset += 2;
                if (byte_offset < loop_bound) {
                    goto next_pair;
                }
            }
        }
    }
    return has_content;
}

/* MECHANISM: Frameless leaf with held t0/t1/t2/t3/t4 roles and a volatile second byte read.
   Distinct a1 -> v1 -> t2 bound lifetimes plus the t0-relative test force retail's slt/beqz
   and move handoff, restoring the two missing words and every cascaded branch displacement. */

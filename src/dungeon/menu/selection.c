/* Selection menu input, widget descriptors, child allocation, and text-content checks. */
#include "shared/audio_commands.h"
#include "shared/object_node.h"
#include "dungeon/menu.h"
#include "dungeon/menu/selection.h"
#include "shared/object_flags.h"
#include "engine/graphics.h"
#include "engine/resource.h"
#include "engine/text.h"


/* Sets the linked entry halfword at offset 8 to index times eight minus 0x18. */
void set_indexed_object_field(ovl_1831370_81811370_S_80026370_0 *object, s32 index) {
    ((ovl_1831370_81811370_S_80026370_2 *)(((ovl_1831370_81811370_S_80026370_1 *)(object->unk_04))->unk_04))->unk_08 = (s16) ((index * 8) - 0x18);
}

/*
 * Calls advance_index_with_single_wrap with target, input_value,
 * text_editor_pair_limits[lookup_index] and returns its result.
 */
s32 adjust_selection_by_item_count(s32 input_value, s32 target, s32 lookup_index)
{
    return advance_index_with_single_wrap(target, input_value, text_editor_pair_limits[lookup_index]);
}

/*
 * Releases the previous object handle, creates a replacement through func_8004DC14 with mode zero,
 * and stores the returned handle.
 */
void inventory_set_object_entry_address(ovl_1831370_818113C0_S_800263C0_0 *object, s32 source) {
    release_object_handle(object);
    *object->unk_0C = func_8004DC14(source, 0);
}

/* Moves menu selection with left or right buttons and held-button repeat, then updates the cursor object. */
void update_menu_selection_from_input(ovl_1831370_8181140C_MenuState *menu) {
    s32 direction = 0;
    s32 buttons;
    s32 repeat_ticks;
    s32 selection;

    if (g_game_work.buttons != 0) {
        if ((g_game_work.pressed_buttons) & 0xC) {
            menu->field4 = 0;
            buttons = (g_game_work.pressed_buttons);
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
            SD_Call(AUDIO_CURSOR_MOVE);
            selection = adjust_selection_by_item_count(direction, menu->field8, menu->field10);
            menu->field8 = selection;
            set_indexed_object_field(menu->field70, selection);
        }
    }
}

/*
 * Moves the selection backward through the item count and applies the resulting index to the
 * linked entry offset.
 */
void update_embedded_state_from_table(s32 object_addr) {
    s32 updated_value;
    ovl_1831370_81811508_S_80026508_0 *state;

    state = object_addr + 0x20;
    updated_value = adjust_selection_by_item_count(-1, state->unk_08, state->unk_10);
    state->unk_08 = updated_value;
    set_indexed_object_field(state->unk_70, updated_value);
}

/*
 * Clears the text buffer using the indexed pair limit, rebinds the entry address, and resets both
 * selection and linked entry offset to zero.
 */
void clear_object_buffer_and_state(s32 objectAddress)
{
    ovl_1831370_8181154C_S_8002654C_0 *objectState;

    objectState = (void *)(objectAddress + 0x20);
    memset(objectState->unk_14, 0,
           (text_editor_pair_limits[objectState->unk_10] * 2) | 1);
    inventory_set_object_entry_address(objectState->unk_70, objectState->unk_14);
    objectState->unk_08 = 0;
    set_indexed_object_field(objectState->unk_70, 0);
}

/*
 * Writes a character pair at the current selection, rebinds the entry address, and advances the
 * selection and linked entry offset.
 */
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

/*
 * Clears the text buffer using the indexed pair limit, copies the supplied string, and rebinds the
 * current entry address.
 */
void copy_string_to_object_buffer(s8 *object, s32 sourceString) {
    ovl_1831370_8181161C_Func8181161CData *textData = (ovl_1831370_8181161C_Func8181161CData *)(object + 0x20);

    memset(textData->field_14, 0, (text_editor_pair_limits[textData->index] << 1) | 1);
    strcpy(textData->field_14, sourceString);
    inventory_set_object_entry_address(textData->field_70, textData->field_14);
}

/* Forward the complete menu object to its update routine. */
void forward_menu_object_to_selection_updater(ovl_1831370_8181140C_MenuState *menu) { update_menu_selection_from_input(menu); }

/*
 * Writes the current step scaled by 0x400 to the linked halfword, then advances it and switches to
 * selection updates after step four. Processes menu input each update.
 */
void apply_step_and_reset_after_five(ovl_1831370_8181140C_MenuState *step) {
    s32 step_value = step->unk0 << 10;

    *(s16 *) (*(s32 *) ((u8 *) step + 0x64) + 6) = step_value;
    step->unk0 += 1;
    if (step->unk0 >= 5) {
        step->unk0 = 0;
        *(void **) ((u8 *) step - 0x10) = (void *)forward_menu_object_to_selection_updater;
    }
    update_menu_selection_from_input(step);
}

/* Initializes a selection sprite descriptor, choosing its width from the variant and setting its end bit. */
void *initialize_variant_packet(ovl_1831370_81811708_Packet *packet, s32 variant) {
    s32 payload;

    packet->unk1 = 0x28;
    payload = text_editor_packet_payload;
    packet->unk2 = -0x21;
    packet->unk3 = 5;
    packet->unk4 = payload;
    packet->unkA = (variant == 1) ? 0x42 : 0x5A;
    packet->unkB = 0x16;
    packet->unk0 = 0x80;
    return packet;
}

/* Sets the selection marker descriptor's geometry and payload 0x8040F0, preserving flags and setting
   its end bit. */
void set_descriptor_fields_and_flag(void *descriptor)
{
    s32 saved_settings;
    s32 settings;

    saved_settings = 0x8040F0;
    *(s8 *)((u8 *)descriptor + 1) = 0x28;
    settings = *&saved_settings;
    *(s8 *)((u8 *)descriptor + 3) = 0x18;
    *(s8 *)((u8 *)descriptor + 0xA) = 7;
    *(s8 *)((u8 *)descriptor + 2) = 0;
    *(s8 *)((u8 *)descriptor + 0xB) = 2;
    *(s32 *)((u8 *)descriptor + 4) = settings;
    *(u8 *)descriptor |= 0x80;
}

/*
 * Calls build_reverse_indexed_chain with value, menu_selection_chain_indices, 4 and returns its
 * result.
 */
S_800491F4 *forward_value_to_shared_helper(S_800491F4 **value) {
    return build_reverse_indexed_chain(value, menu_selection_chain_indices, 4);
}

/* Copies default display records into a selection widget and sets its position, depth, and flags. */
void initialize_owner_defaults(void *unused, ovl_1831370_818117D8_Owner *owner, ovl_1831370_818117D8_S_8002E5D8 *patch_data,
                   ovl_1831370_818117D8_S_8002E5E8 *aux_data) {
    ovl_1831370_818117D8_S_8002E5D8 *patch_defaults = &display_block_defaults;
    ovl_1831370_818117D8_S_8002E5E8 *aux_defaults = &display_vector_defaults;
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

/*
 * Binds the indexed data and embedded text destinations, resets the entry offset, and initializes
 * the text object with dimensions 0x68 by 0x88.
 */
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

/* Stores the selected type and values, initializes both descriptors, and starts the opening animation. */
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

/*
 * Initializes object phase data, binds its three embedded owner blocks, and fills the linked
 * destination fields.
 */
void initialize_embedded_object_state(void *state, s32 parent, s32 type, s32 config) {
    initialize_object_phase_data(state, parent, type, config);
    initialize_owner_defaults(state, state + 0x60, state + 0x38, state + 0x48);
    initialize_object_destination_fields(state, ((ovl_1831370_818119A0_S_800269A0_0 *)state)->unk_70);
}

/* Allocates four widget entries and links each to the object's copied default display vector. */
s32 get_and_position_object_handle(void *object)
{
    ovl_1831370_818119E8_Vec3 *initial_pos;
    s32 success = 0;

    if ((*(s32 *)((s8 *)object + 0x70) = func_80048EE4((s8 *)object + 0x74, 4)) != 0) {
        initial_pos = &display_vector_defaults;
        *(s32 *)((s8 *)object + 0x54) = initial_pos->x;
        *(s32 *)((s8 *)object + 0x58) = initial_pos->y;
        *(s32 *)((s8 *)object + 0x5C) = initial_pos->z;
        texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(*(s32 *)((s8 *)object + 0x70), (s8 *)object + 0x54, 4);
        success = 1;
    }
    return success;
}

/* Creates a selection menu child with widget data and drawing, marking failed allocations for removal. */
void *allocate_initialized_child_object(s32 parent_object, s32 type_code, s32 config_value) {
    ObjectNodeHeader *object;
    u8 *state;

    object = allocate_flagged_object_node(0);
    state = ((u8 *)object )+ 0x20;
    if (object != 0) {
        if (get_and_position_object_handle(state) != 0) {
            object->sprite =((u8*)object )  + 0x80;
            *(s32 *)(state + 0x6C) = (s32)forward_value_to_shared_helper(*(S_800491F4 ***)(state + 0x70));
            initialize_embedded_object_state(state, parent_object, type_code, config_value);
            register_node(object, draw_tinted_node_sprites_scratch);
        } else {
            flag_object_for_removal(*(unsigned short **)(state + 0x74));
            object ->flags |= 0x8000;
            object = 0;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
    return object;
}

/* Flags a nonzero referenced handle for removal and clears the handle word. */
void release_object_handle(ovl_1831370_81811B44_S_80026B44_0 *owner) {
    void *handle;

    handle = *owner->unk_0C;
    if (handle != 0) {
        flag_optional_object_for_removal(handle);
        *owner->unk_0C = 0;
    }
}

/*
 * For a nonnull object, releases the referenced handle and display resource, then sets local and
 * global removal flags.
 */
void cleanup_object_resources(ovl_1831370_81811B94_CleanupObject *object)
{
    ovl_1831370_81811B94_CleanupData *cleanup;

    if (object != 0) {
        cleanup = &object->cleanup;
        release_object_handle(cleanup->field_70);
        flag_object_for_removal(cleanup->field_74);
        object->flags |= 0x8000;
        D_800814A0 |= OBJECT_REMOVE_PENDING;
    }
}

/* Returns one only for a nonnull object whose word at offset 0x28 is zero. */
u32 has_available_object(void *object) {
    if (object != 0) {
        if (*(s32 *)((s8 *)object + 0x28) == 0) {
            return 1;
        }
    }
    return 0;
}

/* Checks whether six or nine byte pairs contain text other than the default pair or two spaces. */
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
            default_pair = text_editor_empty_pair;
            compare_space = 0x20;
            loop_bound = byte_count;
            pair_data = pair_info->unk_14;
            default_first = text_editor_empty_pair[0];
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

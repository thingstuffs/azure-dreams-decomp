/* Inventory action menu input, item text editing, and widget allocation and layout. */
#include "shared/object_node.h"
#include "dungeon/item.h"
#include "dungeon/item/itemwin.h"
#include "shared/item_ids.h"
#include "shared/object_flags.h"


void inventory_dispatch_indexed_handler(void *context, s32 handler_index) {
    DispatchFunc *table;
    DispatchFunc *handler_entry;

    table = inventory_menu_handlers;
    handler_entry = table + handler_index;
    (*handler_entry)(context, (void *)handler_entry);
}

void inventory_set_paired_index_offset(ovl_1830850_81810888_S_80025888_0 *pair, s32 index) {
    s16 offset;

    offset = (index * 0x10) - 0x38;
    ((ovl_1830850_81810888_S_80025888_3 *)(((ovl_1830850_81810888_S_80025888_1 *)(pair->unk_04))->unk_04))->unk_0A = offset;
    ((ovl_1830850_81810888_S_80025888_4 *)(((ovl_1830850_81810888_S_80025888_2 *)(pair->unk_08))->unk_04))->unk_0A = offset;
}

s32 inventory_menu_returns_zero(void *menu) { return 0; }

/* Restores the saved item category record when present, otherwise copies the original text back. */
void restore_item_text_before_edit(void *item_object)
{
    s32 category;
    s32 subobject_base;
    void *object = item_object;
    ovl_1830850_818108B8_S_800258B8_1 *subobject;

    subobject_base = ((ovl_1830850_818108B8_S_800258B8_0 *)object)->unk_14;
    category = ((ovl_1830850_818108B8_S_800258B8_0 *)object)->unk_0C;
    subobject = (void *)(subobject_base + 0x20);
    if (category != ITEM_KIND_FAMILIAR) {
        if (subobject->unk_08 != 0) {
            free_item_data_slot(category, subobject->unk_1C);
            item_category_groups[((ovl_1830850_818108B8_S_800258B8_0 *)object)->unk_0C]
            .records[subobject->unk_1C].value =
                subobject->unk_08;
            return;
        }
    }
    strcpy(((ovl_1830850_818108B8_S_800258B8_0 *)object)->unk_88, (u8 *)object + 0x78);
}

void inventory_select_null_or_default_data(void *object)
{
    if (check_object_byte_pairs_content(*(s32 *)((u8 *)*(void **)((u8 *)object + 0x18) + 0x28))) {
        **(void ***)((u8 *)*(void **)((u8 *)object + 0x54) + 0x30) = 0;
        return;
    }

    **(void ***)((u8 *)*(void **)((u8 *)object + 0x54) + 0x30) = inventory_default_entry_data;
}

s32 inventory_check_type_four_linked_object(Rec_func_80025850_arg0 *context) {
    s32 check_passed;

    check_passed = 0;
    if (context->unk_08 == 4) {
        check_passed = check_object_byte_pairs_content(((ovl_1830850_818109CC_S_800259CC_2 *)(((Rec_func_80025850_arg0 *)context)->unk_18))->unk_28) == 0;
    }
    return check_passed;
}

/* Handles inventory cancel and activation buttons and moves among five actions with held-button repeat. */
void inventory_handle_menu_actions_and_repeat(ovl_1830850_81810A0C_DungeonArg *menu) {
    ovl_1830850_81810A0C_DungeonState *input = g_game_work;
    s32 selection_step;

    if (input->unk8 != 0 && menu->unk10 != 0) {
        if (input->unk10 & 0x20) {
            SD_Call(0x515);
            set_object_data_pointer(menu->unk14);
            restore_item_text_before_edit(menu);
        } else if (input->unk10 & 0x40) {
            if (inventory_menu_returns_zero(menu) != 0 || inventory_check_type_four_linked_object(menu) != 0) {
                SD_Call(0x506);
            } else {
                if (menu->unk8 == 4) {
                    SD_Call(0x503);
                } else {
                    SD_Call(0x514);
                }
                inventory_dispatch_indexed_handler(menu, menu->unk8);
            }
        } else if (input->unk10 & 0x10) {
            menu->unk8 = 4;
            inventory_set_paired_index_offset(menu->unk54, menu->unk8);
        } else if (input->unk8 & 0x5000) {
            selection_step = 0;
            if (input->unk10 & 0x5000) {
                menu->unk4 = 0;
                if (input->unk10 & 0x1000) {
                    selection_step = -1;
                } else if (input->unk10 & 0x4000) {
                    selection_step = 1;
                }
            } else {
                if (menu->unk4 >= 9) {
                    menu->unk4 = menu->unk4 - 1;
                    if (input->unk8 & 0x1000) {
                        selection_step = -1;
                    } else if (input->unk8 & 0x4000) {
                        selection_step = 1;
                    }
                } else {
                    menu->unk4 = menu->unk4 + 1;
                }
            }
            if (selection_step != 0) {
                SD_Call(0x502);
                menu->unk8 = advance_index_with_single_wrap(selection_step, menu->unk8, 5);
                inventory_set_paired_index_offset(menu->unk54, menu->unk8);
            }
        }
    }

    inventory_select_null_or_default_data(menu);
}

void update_inventory_menu(void *menu) { inventory_handle_menu_actions_and_repeat(menu); }

/* Steps the inventory opening transform for five updates, then installs its regular menu callback. */
void inventory_apply_step_and_reset_after_five(ovl_1830850_81810BF4_Entity *entity) {
    s32 next_state;
    s32 t;

    t = entity->state;
    *(s16 *)((u8 *)entity->object + 6) = t << 10;
    next_state = entity->state + 1;
    entity->state = next_state;
    if (next_state >= 5) {
        entity->state = 0;
        *(void **)((u8 *)entity - 0x10) = (void *)update_inventory_menu;
    }
    inventory_handle_menu_actions_and_repeat((ovl_1830850_81810A0C_DungeonArg *)entity);
}

void inventory_clear_entry_value(ovl_1830850_81810C4C_S_80025C4C_0 *entry) {
    *entry->unk_04 = 0;
}

void set_destination_byte_pointer(ovl_1830850_81810C58_S_80025C58_0 *dest) {
    *dest->unk_04 = D_800789B8;
}

/* Initializes five 12-byte sprite entries at 16-pixel intervals and marks the last entry as the
   terminator. */
void *inventory_initialize_five_shared_entries(void *entryBuffer) {
    s32 entryIndex;
    s32 sharedEntryValue;
    ovl_1830850_81810C6C_Entry *entries;

    entryIndex = 0;
    entries = entryBuffer;
    do {
        entries[entryIndex].f1 = 40;
        sharedEntryValue = inventory_shared_entry_value;
        entries[entryIndex].f3 = (entryIndex * 16) - 62;
        entries[entryIndex].f2 = 2;
        entries[entryIndex].f10 = 12;
        entries[entryIndex].f11 = 12;
        entries[entryIndex].f4 = sharedEntryValue;
        entryIndex += 1;
    } while (entryIndex < 5);
    ((ovl_1830850_81810C6C_Entry *)((entryIndex * 12) + entryBuffer))[-1].f0 = 128;
    return entryBuffer;
}

/* Initializes the large inventory sprite descriptor with a zero payload and sets its end bit. */
void inventory_initialize_packet_and_set_flag(ovl_1830850_81810CD8_S_80025CD8_0 *packet) {
    s32 zero;
    s32 payload;

    zero = 0;
    packet->unk_01 = 0x28;
    payload = *(s32 *)&zero;
    packet->unk_02 = -0x18;
    packet->unk_03 = 4;
    packet->unk_0A = 0x30;
    packet->unk_0B = 0x58;
    packet->unk_04 = payload;
    packet->unk_00 |= 0x80;
}

/* Initializes the small inventory sprite descriptor with payload 0xB8C8 and sets its end bit. */
void initialize_inventory_packet(Rec_func_80025D28_arg0 *packet) {
    s32 initial_payload;
    s32 payload;
    u8 flags;

    initial_payload = 0xB8C8;
    packet->unk_01 = 0x28;
    payload = *(s32 *)&initial_payload;
    flags = packet->unk_00;
    packet->unk_02 = 2;
    packet->unk_03 = 2;
    packet->unk_0A = 0xC;
    packet->unk_0B = 0xC;
    packet->unk_04 = payload;
    packet->unk_00 = (u8)(flags | 0x80);
}

S_800491F4 *inventory_create_context_entry_13(S_800491F4 **context) {
    return build_reverse_indexed_chain(context, item_window_chain_indices, 13);
}

/* Copies default display records into the inventory widget and sets its position, depth, and flags. */
void inventory_initialize_owner_patch_and_state(void *unused, ovl_1830850_81810D9C_Owner *owner, ovl_1830850_81810D9C_S_8002E5D8 *patch,
                   ovl_1830850_81810D9C_S_8002E5E8 *state) {
    ovl_1830850_81810D9C_S_8002E5D8 *patch_defaults = &display_block_defaults;
    ovl_1830850_81810D9C_S_8002E5E8 *state_defaults = &display_vector_defaults;
    s32 *state_first_word;

    patch->unk0 = patch_defaults->unk0;
    state_first_word = &state_defaults->unk0;
    patch->unk4 = patch_defaults->unk4;
    patch->unk8 = patch_defaults->unk8;
    patch->unkC = patch_defaults->unkC;

    state->unk0 = *state_first_word;
    state->unk4 = state_defaults->unk4;
    state->unk8 = state_defaults->unk8;

    owner->unk4 = (ovl_1830850_81810D9C_PatchRecord *)patch;
    owner->unk8 = state;
    owner->unk0 = 0;

    owner->unk4->unk8 = 0x2C;
    owner->unk4->unkA = -8;
    owner->unk4->unkC = 0x200;
    owner->unk4->unk6 = 0;
    owner->unk4->unkF = 4;
}

/* Assigns inventory widget resources, text buffers, action rows, and their display offsets. */
void inventory_initialize_owner_pointers_and_offsets(ovl_1830850_81810E3C_Source *source, ovl_1830850_81810E3C_Owner **owners)
{
    s32 owner_idx;

    owners[0]->unk0 = D_80078C10;
    owners[0]->unk4->unkA = 0;

    owners[1]->unk0 = D_800789B8;
    owners[1]->unk4->unk8 = -20;

    owners[2]->unk0 = source->unk74 + 12;
    owners[2]->unk4->unk8 = -20;
    inventory_set_paired_index_offset(owners, 0);

    owners[3]->unk0 = source->unk74;
    owners[3]->unk4->unkA = -64;
    inventory_initialize_five_shared_entries(source->unk74 + 24);

    owners[4]->unk0 = source->unk74 + 24;
    owners[4]->unk4->unk8 = -20;
    owners[4]->unk4->unkA = 8;

    owners[5]->unk0 = func_8004DC14(D_80029474, 0);
    owners[5]->unk4->unk8 = 124;
    owners[5]->unk4->unkA = 72;

    for (owner_idx = 6; owner_idx < 11; owner_idx++) {
        owners[owner_idx]->unk0 = D_8007795C;
        owners[owner_idx]->unk4->unk8 = -12;
        owners[owner_idx]->unk4->unkA = (owner_idx * 16) - 137;
    }

    inventory_select_null_or_default_data(source);
    owners[12]->unk4->unk8 = -12;
    owners[12]->unk4->unkA = 23;
}

/* Initializes editor sprite descriptors, stores the edit range, backs up the text, and starts its
   opening update. */
void initialize_text_editor_context(void *object, s32 range_start, s32 initial_value, s32 text_addr)
{
    u8 *data = object;

    inventory_initialize_packet_and_set_flag(*(s32 *)(data + 0x74));
    initialize_inventory_packet(*(s32 *)(data + 0x74) + 0xC);
    *(s32 *)(data + 0x0C) = initial_value;
    *(s32 *)(data + 0x14) = range_start;
    *(s32 *)(data + 0x18) = range_start + 0x20;
    *(s32 *)(data + 0x88) = text_addr;
    strcpy(data + 0x78, text_addr);
    *(s32 **)(data - 0x10) = (void *)inventory_apply_step_and_reset_after_five;
}

void inventory_initialize_object_from_embedded_data(void *object, s32 init_value, s32 init_value_2, s32 init_value_3) {
    initialize_text_editor_context(object, init_value, init_value_2, init_value_3);
    inventory_initialize_owner_patch_and_state(object, object + 0x44, object + 0x1C, object + 0x2C);
    inventory_initialize_owner_pointers_and_offsets(object, ((Rec_func_80025850_arg0 *)object)->unk_54);
}

/* Allocates inventory widget buffers, copies the default vector, and shares it among 13 entries. */
s32 inventory_copy_state_vector_after_buffers(ovl_1830850_818110CC_Unk818110CC *state, s32 input)
{
    s32 success = 0;
    s32 *buffer = state->unk58;
    s32 call_result;

    call_result = func_80049004(buffer, input, 6);
    state->unk54 = call_result;
    if (call_result != 0) {
        call_result = allocate_and_append_callback_payload(buffer, 6);
        state->unk74 = call_result;
        if (call_result != 0) {
            state->unk38[0] = display_vector_defaults.unk0;
            state->unk38[1] = display_vector_defaults.unk4;
            state->unk38[2] = display_vector_defaults.unk8;
            texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(state->unk54, state->unk38, 13);
            success = 1;
        }
    }
    return success;
}

/* Creates an inventory editor child with buffers and drawing, retiring the object if buffer setup fails. */
ovl_1830850_81811168_DungeonObj81811168 *inventory_allocate_and_initialize_child(s32 parent_obj, s32 initial_value, s32 text_addr)
{
    ovl_1830850_81811168_DungeonObj81811168 *obj;
    ovl_1830850_81811168_DungeonSub81811168 *state;

    obj = (ovl_1830850_81811168_DungeonObj81811168 *)allocate_flagged_object_node(0);
    state = &obj->sub20;
    if (obj != 0) {
        if (inventory_copy_state_vector_after_buffers(state, 13) != 0) {
            obj->field0C = (u8 *)obj + 0x64;
            state->value50 = (s32)inventory_create_context_entry_13(state->value54);
            inventory_initialize_object_from_embedded_data(state, parent_obj, initial_value, text_addr);
            register_node(obj, (void *)draw_tinted_node_sprites_scratch);
            inventory_set_embedded_state_one(obj);
        } else {
            release_null_terminated_entries((u8 *)obj + 0x78);
            obj->flags1E |= 0x8000;
            obj = 0;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
    return obj;
}

void inventory_clear_referenced_handle(ovl_1830850_81811250_S_80026250_0 *context) {
    flag_optional_object_for_removal(*context->unk_14);
    *context->unk_14 = 0;
}

void inventory_process_resources_and_set_flags(void *object)
{
    u16 object_flags;
    s32 global_flags;

    if (object != 0) {
        inventory_clear_referenced_handle(*(void **)((u8 *)object + 0x74));
        release_null_terminated_entries((u16 **)((u8 *)object + 0x78));
        object_flags = *(u16 *)((u8 *)object + 0x1E);
        global_flags = object_flag_block.flags;
        *(u16 *)((u8 *)object + 0x1E) = object_flags | 0x8000;
        object_flag_block.flags = global_flags | 0x8000;
    }
}

void inventory_clear_object_field_and_entry(s32 object_addr) {
    ovl_1830850_818112EC_S_800262EC_0 *object_data;

    object_data = object_addr + 0x20;
    object_data->unk_10 = 0;
    inventory_clear_entry_value(object_data->unk_54);
}

void inventory_set_embedded_state_one(s32 object_addr) {
    ovl_1830850_81811314_S_80026314_0 *state;

    state = object_addr + 0x20;
    state->unk_10 = 1;
    set_destination_byte_pointer(state->unk_54);
}

void inventory_set_embedded_state_four(s32 object_addr) {
    ovl_1830850_81811340_S_80026340_0 *state;

    state = object_addr + 0x20;
    state->unk_08 = 4;
    inventory_set_paired_index_offset(state->unk_54, 4);
}

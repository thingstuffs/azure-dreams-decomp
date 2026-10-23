/* Message dialog lifecycle; G00381; inferred-strong; CL/PD joins as listed below, no proven or weak cut crossed */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:main/func_8000F934, CL:main/func_8000FAE8, CL:main/func_8000FB20, CL:main/func_8000FB48, CL:main/func_8000FBE8, CL:main/func_8000FC48, CL:main/func_8000FC90. */
#include "frontend/libcard/message_dialog_lifecycle_g00381.h"
#include "shared/object_node.h"
#include "frontend/libcard.h"

/* Record the maximum string length and last nonempty slot across five strings. */
void card_boot_measure_five_line_message(u8 *text_block)
{
    u8 **strings;
    u8 *text;
    u8 *next_text;
    s32 longest;
    s32 last_nonempty;
    s32 length;
    s32 string_index;
    u8 character;

    longest = 0;
    last_nonempty = longest;
    string_index = longest;
    strings = (u8 **)text_block;
    do {
        length = 0;
        text = *strings;
        goto check;
        do {
            length++;
            text = next_text;
            last_nonempty = string_index;
            if (longest < length) {
                longest = length;
            }
check:
            character = *text;
            next_text = text + 1;
        } while (character != 0);
        string_index++;
        strings++;
    } while (string_index < 5);
    text_block[0x16] = longest;
    text_block[0x17] = last_nonempty + 1;
}

/* Sets record fields and processes the selected table entry. */
void card_boot_bind_message_dialog_record(Rec_func_8002290C_arg0 *record, s32 value_14, s32 entry_index, s32 value_0c, s32 value_20) {
    record->unk_14 = value_14;
    record->unk_20 = value_20;
    record->unk_08 = entry_index;
    record->unk_0C = value_0c;
    card_boot_measure_five_line_message((entry_index * 0x18) + &((u8 *)card_menu_entry_values)[0]);
}

/* Sets record fields, processes its embedded data, and updates the record. */
void card_boot_initialize_message_dialog_layout(s32 record, s32 value_14, s32 entry_index, s32 value_0c, s32 value_20) {
    card_boot_bind_message_dialog_record((Rec_func_8002290C_arg0 *)record, value_14, entry_index, value_0c, value_20);
    card_boot_initialize_message_render_templates(record + 0x8BC, record + 0x894, record + 0x8A4);
    card_boot_initialize_dialog_packets_and_display(record);
}

/* Initialize the object from its table entry and select its callback. */
void card_boot_activate_message_dialog(void *object)
{
    void *callback;
    s32 entry_index;

    card_boot_build_message_window_packets((u8 *)object + 0x24, object);
    card_boot_layout_five_entry_list(object);
    entry_index = ((S_80022CD8_0 *)object)->unk_08;
    ((S_80022CD8_0 *)object)->unk_00 = card_menu_entry_values[entry_index].unk_15;
    card_boot_update_message_choice_highlight(object);
    if (((S_80022CD8_0 *)object)->unk_0C == 2) {
        callback = D_800226A8;
    } else {
        callback = D_80022524;
    }
    ((S_80022CD8_0_pre *)object)[-1].unk_00 = callback;
}

static __inline__ void set_handler(ObjectNodeHeader *base) {
    base->update_callback = D_80022CD8;
}

/* Creates or resets the entity, initializes its nodes and record, and installs its handler. */
u8 *card_boot_create_or_reset_message_dialog(s32 value_14, void *entry_index, void *value_0c, s32 value_20) {
    ObjectNodeHeader *base;
    u8 *context;

    base = D_800287E8;
    context = ((u8 *)base) + 0x20;
    if (find_active_list_node(base) == 0) {
        base = initialize_scene_object_in_buffer(0, base, 0x27A);
        register_node(base, menu_backdrop_tag);
    } else {
        card_boot_close_message_dialog(((S_80022D60_0 *)context)->unk_0C != 2);
        base->flags &= 0x7FFF;
        bzero(context, 0x9C8);
    }
    card_boot_initialize_dialog_draw_nodes(context, 7);
    {
        u8 *body = context;

        base->sprite = body + 0x8BC;
        ((S_80022D60_2 *)body)->unk_8C8 = card_boot_link_message_display_entries(body + 0x8CC);
        card_boot_initialize_message_dialog_layout((s32)body, value_14, (s32)entry_index, (s32)value_0c, value_20);
    }
    set_handler(base);
    return base;
}

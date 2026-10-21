/* Dialog selection highlight; G00379; inferred-strong; CL/PD joins as listed below, no proven or weak cut crossed */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:main/func_8000F25C, CL:main/func_8000F300, CL:main/func_8000F33C, CL:main/func_8000F3B4. */
#include "frontend/libcard/dialog_selection_highlight_g00379.h"

/* Initializes a packet for the selected slot and returns the next packet. */
void *card_boot_build_slot_marker_packet(s32 unused, Struct_8000F300 *packet, s32 slot_index) {
    s32 command = 0xA04010;
    u8 flags = packet->unk0;
    void *next_packet;

    packet->unk1 = 0x28;
    packet->unkA = (s8)(slot_index * 8 + 4);
    packet->unkB = 0x13;
    next_packet = packet + 1;
    packet->unk4 = command;
    flags |= 0x80;
    packet->unk0 = flags;
    return next_packet;
}

/* Processes consecutive 12-byte entries starting at the requested index. */
void card_boot_highlight_dialog_text_range(s32 entry_base, s32 start_index, s32 entry_count) {
    s32 entry_index;
    s32 entry_addr;

    set_style_for_tagged_glyph_entries(entry_base, 1);
    entry_addr = entry_base + (start_index * 0xC);
    entry_index = 0;
    if (entry_count > 0) {
        do {
            set_glyph_style_index(entry_addr, 0);
            entry_index += 1;
            entry_addr += 0xC;
        } while (entry_index < entry_count);
    }
}

static __inline__ u32 calculate_x(
    void *context,
    s32 column
    )
{
    u32 x;

    x = (u32)column * 4U;
    x -= (u32)(*(s32 *)((u8 *)context + 0x18) / 2);
    return x + 0xA2;
}

/* Positions the current record and updates the specified row. */
void card_boot_position_dialog_selection_marker(void *context, s32 column, s32 mode, s32 row, s32 row_value)
{
    void *state = context;
    s32 *record;
    void *position;
    u32 x;
    s32 saved_row_value;

    x = calculate_x(state, column);
    position = (u8 *)state + 0xE4;
    record = *(s32 **)((u8 *)state + 0x8E4);
    *(s16 *)((u8 *)*(void **)((u8 *)record + 4) + 8) = (s16)x;
    *(s16 *)((u8 *)*(void **)((u8 *)record + 4) + 0xA) =
        (s16)((row * 0x11) - (*(s32 *)((u8 *)state + 0x1C) / 2) + 0x7A);
    saved_row_value = *(s32 *)&row_value;
    card_boot_build_slot_marker_packet((s32)state, (Struct_8000F300 *)position, mode);
    record[0] = (s32)(unsigned long)position;
    card_boot_highlight_dialog_text_range(
        *(s32 *)*(s32 **)((u8 *)state + row * 4 + 0x8CC),
        saved_row_value,
        mode);
}

/* Processes the last word of an enabled table entry for the supplied object. */
void card_boot_update_message_choice_highlight(void *object) {
    s32 result_first;
    s32 result_second;
    s32 result_third;
    EntryT *entry;
    s32 last_index;
    s32 table_index;
    s32 table_base;

    table_base = (s32)D_800280B4;
    table_index = *(s32 *)((u8 *)object + 8);
    entry = (EntryT *)(table_index * 0x18 + table_base);
    last_index = entry->count17 - 1;
    if (entry->flag14 != 0) {
        card_boot_measure_dialog_choice_word((u8 *)(entry->words[last_index]), *(s32 *)object, &result_first, &result_second, &result_third);
        card_boot_position_dialog_selection_marker(object, result_first, result_second, last_index, result_third);
    }
}

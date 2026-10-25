#include "sdk/libc.h"
/* Initialize display entries and draw entity statistics panels.
 * Evidence: proven (string literals).
 * town/engine#g1058 J1[800892C0,800892C8,800892CC,800892F0,800892FC,80089304,80089324,8008933C,80089340]
 * B2@0x8008929c; B2@0x80089ae8; partial span, complete TU edges unknown.
 */
#include "town/shop/stat_panel.h"
#include "shared/monster_ids.h"

/* Transfer pending texture and palette data, then clear the transfer state. */
void complete_display_transfer(void *texture_state) {
    s32 table_index;
    struct { s16 x; s16 y; s16 w; s16 h; } rect;
    void *state = texture_state;
    void *texture;
    s16 *slot_table;

    if (((DisplayTransferState *)state)->transfer_pending != 0) {
        DrawSync(0);
        slot_table = display_resource_cache_keys;
        table_index = ((DisplayTransferState *)state)->slot_index;
        texture = ((DisplayTransferState *)state)->texture;
        ((DisplayTransferState *)state)->transfer_phase = 0;
        ((DisplayTransferState *)state)->transfer_pending = 0;
        slot_table[table_index * 2] = ((DisplayTransferState *)state)->texture_slot;
        slot_table[(((DisplayTransferState *)state)->slot_index * 2) + 1] = ((DisplayTransferState *)state)->palette.palette_slot;

        rect.x = ((u8) ((S_800B5B20_0 *)texture)->unk_08 >> 2) + ((((S_800B5B20_0 *)texture)->unk_04 << 6) & 0x3C0);
        rect.y = ((S_800B5B20_0 *)texture)->unk_09 + ((((S_800B5B20_0 *)texture)->unk_04 * 0x10) & 0x100);
        rect.w = (s16) ((u8) ((S_800B5B20_0 *)texture)->unk_0A >> 2);
        rect.h = (s16) ((S_800B5B20_0 *)texture)->unk_0B;
        LoadImage(&rect, ((DisplayTransferState *)state)->data);
        if (((DisplayTransferState *)state)->slot_index != 0) {
            u16 palette_y;
            s32 palette_offset;
            s32 data_base;

            rect.x = (((S_800B5B20_0 *)texture)->unk_06 & 0x3F) * 0x10;
            palette_y = ((S_800B5B20_0 *)texture)->unk_06;
            rect.w = 0x10;
            rect.h = 1;
            palette_y >>= 6;
            rect.y = (s16) palette_y;

            palette_offset = ((DisplayTransferState *)state)->palette.palette_offset;
            data_base = ((DisplayTransferState *)state)->data;
            palette_offset <<= 5;
            palette_offset += 0x200;

            LoadImage(&rect, data_base + palette_offset);
        }
        DrawSync(0);
    }
    ((DisplayTransferState *)state)->data = 0;
}

/* Initializes three entries with offsets and fixed, supplied, and computed values. */
void initialize_three_display_entries(s32 source_value, Func800B8500Entry **entries, s32 entry_value) {
    s32 entry_offset = 8;

    entries[0]->inner->field_8 = -0x38;
    entries[0]->inner->field_A = entry_offset;
    entries[0]->value = &D_80077FBC[0];

    entries[1]->inner->field_8 = -0x38;
    entries[1]->inner->field_A = entry_offset;
    entries[1]->value = entry_value;

    entries[2]->inner->field_8 = -0x10;
    entries[2]->inner->field_A = 0x16;
    entries[2]->value = lookup_patterned_display_icon(get_enabled_record_flag_priority(source_value));
}

/* Returns the global in mode 1, otherwise calls the default handler. */
s32 get_mode_specific_value(void *entry) {
    if (runtime_dispatch_state.mode != 1) {
        return select_object_state_value();
    }
    return D_800D1790[0];
}

/* Builds and displays an entry's formatted text. */
void draw_formatted_monster_status_text(void *entry, void *display) {
    u8 text[64];

    memcpy(text, D_800892C0, 5);
    strcat(text, (u8 *)entry + 0x34);
    strcat(text, D_8008933C);
    strcat(text, (u8 *)get_mode_specific_value(entry));
    set_display_entry_text_and_position(*(s32 *)((u8 *)display + 0x10), text, 0, 0x47, 0x88);
}

/* Maps value 0x39 to 2 and returns other values unchanged. */
s32 normalize_monster_status_species_code(s32 value) {
    s32 mapped_value;

    mapped_value = MONSTER_KEWNE;
    if (value != 0x39) {
        mapped_value = value;
    }
    return mapped_value;
}

/* Formats and draws entity stats and detail text in the panel. */
void draw_entity_stats_panel(void *entity, void *panel) {
    u8 number_text[0x40];
    u8 text[0x40];
    s32 display_value;
    s32 text_style;

    memcpy(text, D_80089308, 5);
    func_8004E5A0(*((u8 *)entity + 0x11), 2, &number_text);
    remap_flagged_string_bytes(&number_text);
    strcat(&text, &number_text);
    strcat(&text, D_80089310);
    strcat(&text, D_80089318);

    func_8004E5A0(*((u8 *)entity + 0x28), 3, &number_text);
    strcat(&text, &number_text);
    strcat(&text, D_8008931C);

    func_8004E5A0(*((u8 *)entity + 0x29), 3, &number_text);
    strcat(&text, &number_text);
    strcat(&text, D_80089340);

    func_8004E5A0(*((u8 *)entity + 0x25), 3, &number_text);
    strcat(&text, &number_text);
    strcat(&text, D_8008931C);

    func_8004E5A0(*((u8 *)entity + 0x66), 3, &number_text);
    strcat(&text, &number_text);

    set_storage_entry_text(*(s32 *)((u8 *)panel + 0x14), &text, 0, 0x6C, 0x98);
    display_value = monster_get_species_name_text(normalize_monster_status_species_code(*((u8 *)entity + 0x13)));
    text_style = 0;
    if (*((u8 *)entity + 0x43) >= 0x41) {
        text_style = 3;
    }
    set_display_entry_text_and_position(*(s32 *)((u8 *)panel + 0x18), display_value, text_style, 0x68, 0x98);
    set_storage_entry_text(*(s32 *)((u8 *)panel + 0x4C), D_80089324, 0, 0x48, 0xB8);
    set_storage_entry_text(*(s32 *)((u8 *)panel + 0x1C), format_object_value_marker(&text, entity), 0, 0x48, 0xC8);
    set_storage_entry_text(*(s32 *)((u8 *)panel + 0x48), format_compared_stat_pairs(&text, entity), 0, 0x48, 0xB8);
}

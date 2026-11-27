#include "sdk/libc.h"
/* Initialize display entries and draw entity statistics panels.
 * Evidence: proven (string literals).
 * town/engine#g1058 J1[800892C0,800892C8,800892CC,800892F0,800892FC,80089304,80089324,8008933C,80089340]
 * B2@0x8008929c; B2@0x80089ae8; partial span, complete TU edges unknown.
 */
#include "town/shop/stat_panel.h"
#include "shared/monster_ids.h"
#include "engine/text.h"
#include "dungeon/system.h"
#include "slus.h"

/* Transfer pending texture and palette data, then clear the transfer state. */
void complete_display_transfer(ShopFirstCallbackObject *state) {
    s32 table_index;
    struct { s16 x; s16 y; s16 w; s16 h; } rect;
    SpritePartCommand *texture;
    s16 *slot_table;

    if (state->completion_handle != 0) {
        DrawSync(0);
        slot_table = display_resource_cache_keys;
        table_index = state->slot_index;
        texture = state->texture;
        state->read_handle = 0;
        state->completion_handle = 0;
        slot_table[table_index * 2] = state->species_code;
        slot_table[(state->slot_index * 2) + 1] = state->palette_index;

        rect.x = (texture->data.texture.u0 >> 2) + ((texture->tpage << 6) & 0x3C0);
        rect.y = texture->data.texture.v0 + ((texture->tpage * 0x10) & 0x100);
        rect.w = (s16) (texture->data.texture.width >> 2);
        rect.h = (s16) texture->data.texture.height;
        LoadImage(&rect, state->transfer_data);
        if (state->slot_index != 0) {
            u16 palette_y;
            s32 palette_offset;
            s32 data_base;

            rect.x = (texture->clut & 0x3F) * 0x10;
            palette_y = texture->clut;
            rect.w = 0x10;
            rect.h = 1;
            palette_y >>= 6;
            rect.y = (s16) palette_y;

            palette_offset = state->palette_index;
            data_base = state->transfer_data;
            palette_offset <<= 5;
            palette_offset += 0x200;

            LoadImage(&rect, data_base + palette_offset);
        }
        DrawSync(0);
    }
    state->transfer_data = 0;
}

/* Initializes three entries with offsets and fixed, supplied, and computed values. */
void initialize_three_display_entries(ActorRecord *actor, ItemMenuPart **entries, SpritePartCommand *entry_value) {
    s32 entry_offset = 8;

    entries[0]->position->x = -0x38;
    entries[0]->position->y = entry_offset;
    entries[0]->handler = &D_80077FBC[0];

    entries[1]->position->x = -0x38;
    entries[1]->position->y = entry_offset;
    entries[1]->handler = entry_value;

    entries[2]->position->x = -0x10;
    entries[2]->position->y = 0x16;
    entries[2]->handler = lookup_patterned_display_icon(get_enabled_record_flag_priority(actor));
}

/* Returns the global in mode 1, otherwise calls the default handler. */
s32 get_monster_status_label(void *entry) {
    if (runtime_dispatch_state.mode != 1) {
        return select_status_text(entry);
    }
    return D_800D1790[0];
}

/* Builds and displays an entry's formatted text. */
void draw_formatted_monster_status_text(void *entry, ItemMenuPart **display) {
    u8 text[64];

    memcpy(text, D_800892C0, 5);
    strcat(text, (u8 *)entry + 0x34);
    strcat(text, D_8008933C);
    strcat(text, (u8 *)get_monster_status_label(entry));
    set_display_entry_text_and_position(display[4], text, 0, 0x47, 0x88);
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
void draw_entity_stats_panel(void *entity, ItemMenuPart **panel) {
    u8 number_text[0x40];
    u8 text[0x40];
    s32 display_value;
    s32 text_style;

    memcpy(text, level_line_indent, 5);
    func_8004E5A0(*((u8 *)entity + 0x11), 2, &number_text);
    remap_flagged_string_bytes(&number_text);
    strcat(&text, &number_text);
    strcat(&text, level_line_break_text);
    strcat(&text, hp_label_text);

    func_8004E5A0(*((u8 *)entity + 0x28), 3, &number_text);
    strcat(&text, &number_text);
    strcat(&text, stat_pair_separator);

    func_8004E5A0(*((u8 *)entity + 0x29), 3, &number_text);
    strcat(&text, &number_text);
    strcat(&text, D_80089340);

    func_8004E5A0(*((u8 *)entity + 0x25), 3, &number_text);
    strcat(&text, &number_text);
    strcat(&text, stat_pair_separator);

    func_8004E5A0(*((u8 *)entity + 0x66), 3, &number_text);
    strcat(&text, &number_text);

    set_storage_entry_text(panel[5], text, 0, 0x6C, 0x98);
    display_value = monster_get_species_name_text(normalize_monster_status_species_code(*((u8 *)entity + 0x13)));
    text_style = 0;
    if (*((u8 *)entity + 0x43) >= 0x41) {
        text_style = 3;
    }
    set_display_entry_text_and_position(panel[6], display_value, text_style, 0x68, 0x98);
    set_storage_entry_text(panel[19], attack_defense_labels, 0, 0x48, 0xB8);
    set_storage_entry_text(panel[7], format_gauge_text(&text, entity), 0, 0x48, 0xC8);
    set_storage_entry_text(panel[18], format_compared_stat_pairs(&text, entity), 0, 0x48, 0xB8);
}

/* Advance monster status opening and display spacing (G00633). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B8E20, CL:town/func_800B8E78. */
#include "town/shop/monster_status_opening_g00633.h"

/* Updates two display entries for the mode and adjusts their spacing. */
void update_mode_display_spacing(S_800B65D8_3 *base, s32 display_mode) {
    s32 mode;
    s32 total_width;
    s32 entry_index;
    u8 *lookup;
    void *entry_slot;
    s32 x_offset;
    s32 spacing;
    s32 entry_id;
    S_800B65D8_1 *entry;
    SignedWidgetYView *position;

    entry_index = (total_width = 0);
    lookup = D_80089344;
    entry_slot = base;
    do {
        mode = display_mode;
        entry = ((S_800B65D8_0 *)entry_slot)->unk_50;
        entry_id = select_display_spacing_table_entry(mode, *(u8 *)((s32)entry_index + (long)lookup));
        if ((entry_index == 0) && (mode == 4)) {
            entry_id -= 1;
        }
        entry->unk_00 = read_display_spacing_word(entry_id);
        spacing = read_display_spacing_byte(entry_id);
        if (spacing == 0x10) {
            ((SignedWidgetYView *)(((S_800B65D8_4 *)entry)->unk_04))->unk_0A = 0;
        } else {
            x_offset = total_width - (entry_index * 8);
            position = entry->unk_04;
            total_width += spacing;
            position->unk_0A = x_offset;
        }
        entry_index += 1;
        entry_slot += 4;
    } while (entry_index < 2);
    spacing = 0;
    if (total_width != 0) {
        spacing = total_width - 0x14;
    }
    set_monster_status_panel_height(*base->unk_5C, spacing);
}

/* Advance the object's five-step sequence, then reset it and set its next handler. */
void advance_monster_status_opening(void *object) {
    s16 step;

    step = *(s16 *)((u8 *)object + 0xE);
    if (step < 5) {
        update_mode_display_spacing((S_800B65D8_3 *)*(s32 *)((u8 *)object + 0x98), step);
        *(u16 *)((u8 *)object + 0xE) = *(u16 *)((u8 *)object + 0xE) + 1;
        return;
    }
    process_object_data_by_mode(object);
    *(void **)object = &D_800B6578[0];
}

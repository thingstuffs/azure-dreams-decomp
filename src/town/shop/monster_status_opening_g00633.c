/* Advance monster status opening and display spacing. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B8E20, CL:town/func_800B8E78. */
#include "town/shop/monster_status_opening_g00633.h"
#include "town/shop.h"
#include "town/shop/object.h"
#include "town/shop/monster_status_idle.h"

/* Updates two display entries for the mode and adjusts their spacing. */
void layout_monster_status_entries(ItemMenuPart **parts, s32 display_mode) {
    s32 mode;
    s32 total_width;
    s32 entry_index;
    u8 *lookup;
    ItemMenuPart **entry_slot;
    s32 x_offset;
    s32 spacing;
    s32 entry_id;
    ItemMenuPart *entry;
    ItemMenuPartPosition *position;

    entry_index = (total_width = 0);
    lookup = D_80089344;
    entry_slot = parts;
    do {
        mode = display_mode;
        entry = entry_slot[20];
        entry_id = select_display_spacing_table_entry(mode, *(u8 *)(entry_index + (long)lookup));
        if ((entry_index == 0) && (mode == 4)) {
            entry_id -= 1;
        }
        entry->handler = (void *)(long)read_display_spacing_word(entry_id);
        spacing = read_display_spacing_byte(entry_id);
        if (spacing == 0x10) {
            entry->position->y = 0;
        } else {
            x_offset = total_width - (entry_index * 8);
            position = entry->position;
            total_width += spacing;
            position->y = x_offset;
        }
        entry_index += 1;
        entry_slot++;
    } while (entry_index < 2);
    spacing = 0;
    if (total_width != 0) {
        spacing = total_width - 0x14;
    }
    set_monster_status_panel_height(parts[23]->handler, spacing);
}

/* Advance the object's five-step sequence, then reset it and set its next handler. */
void advance_monster_status_opening(ShopFirstCallbackObject *object) {
    s16 step;

    step = object->opening_step;
    if (step < 5) {
        layout_monster_status_entries(object->parts, step);
        object->opening_step = object->opening_step + 1;
        return;
    }
    build_monster_status_display(object);
    object->first_callback = noop_monster_status_idle;
}

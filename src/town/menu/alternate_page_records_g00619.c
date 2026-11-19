/* Updates page boundary indicators and refreshes the linked menu display records. */
/* inferred-strong alternate_page_records_g00619; joins CL:town/func_80035C0C,CL:town/func_800B5978,CL:town/func_800B5B74; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80035C0C, CL:town/func_800B5978, CL:town/func_800B5B74. */
#include "town/menu/alternate_page_records_g00619.h"
#include "town/menu.h"

/* Shows or hides the two page indicators according to the current page and its limit. */
void update_alternate_menu_page_bounds(AlternateStorageOwner *obj)
{
    AlternateStorageSource *state;
    s32 flag_bits;

    if (obj->source->page.current > 0) {
        u32 flags;

        obj->parts[38]->handler = item_menu_primary_page_data;
        flags = obj->flags;
        flags &= ~2;
        obj->flags = flags;
    } else {
        obj->parts[38]->handler = 0;
        obj->flags |= 2;
    }
    state = obj->source;
    if (state->page.current < state->page.last) {
        flag_bits = -2;
        obj->flags &= flag_bits;
        obj->parts[39]->handler = card_selection_display_data;
        return;
    }

    obj->parts[39]->handler = 0;
    obj->flags |= 1;
}

/* Update the linked record components and finalize the data at offset 0x68. */
void update_paged_menu_record(AlternateStorageOwner *record) {
    fill_paged_menu_slots(record);
    update_alternate_menu_page_bounds(record);
    populate_record_page_entries(record);
    forward_paged_record_data(&record->parts[26], record);
}

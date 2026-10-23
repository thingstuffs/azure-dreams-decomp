/* Updates page boundary indicators and refreshes the linked menu display records. */
/* inferred-strong G00619: alternate_page_records_g00619; joins CL:town/func_80035C0C,CL:town/func_800B5978,CL:town/func_800B5B74; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80035C0C, CL:town/func_800B5978, CL:town/func_800B5B74. */
#include "town/menu/alternate_page_records_g00619.h"

/* Shows or hides the two page indicators according to the current page and its limit. */
void update_alternate_menu_page_bounds(Object *obj)
{
    State *state;
    s32 flag_bits;

    if (obj->state->current > 0) {
        u32 flags;

        *obj->outputs->primary = item_menu_primary_page_data;
        flags = obj->flags;
        flags &= ~2;
        obj->flags = flags;
    } else {
        *obj->outputs->primary = 0;
        obj->flags |= 2;
    }
    state = obj->state;
    if (state->current < state->limit) {
        flag_bits = -2;
        obj->flags &= flag_bits;
        *obj->outputs->secondary = card_selection_display_data;
        return;
    }

    *obj->outputs->secondary = 0;
    obj->flags |= 1;
}

/* Update the linked record components and finalize the data at offset 0x68. */
void update_and_finalize_record(Rec_func_800B2DA0_arg1 *record) {
    update_linked_record_data(record);
    update_alternate_menu_page_bounds((Object *)record);
    prepare_linked_record_data(record);
    forward_paged_record_data(record->unk_A8 + 0x68, (void * *)(record));
}

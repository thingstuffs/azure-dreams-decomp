#include "common.h"
#include "shared/object_node.h"
#include "town/shop/item_menu_cursor_transition_g00601.h"
#include "slus.h"
#include "town/shop/item.h"

/* Update the selection and install its delay callback when the row changes. */
void change_item_menu_selection(ObjectNodeHeader *object, s32 value_arg, s32 reset_value) {
    s32 new_value;
    ItemMenuTransition *state;

    state = (ItemMenuTransition *)(object + 1);
    new_value = advance_index_with_single_wrap(state->end_row, value_arg, state->entry_count);
    if (new_value != state->end_row) {
        state->end_row = new_value;
        state->duration = reset_value;
        state->progress = 0;
        state->callback = D_800AE5B8;
        state->start_row = state->end_row;
    }
}

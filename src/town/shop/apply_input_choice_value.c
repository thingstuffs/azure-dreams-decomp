#include "common.h"
#include "m2c_compat.h"
#include "town/shop.h"

void write_choice_template_value();                    /* extern */

/* Processes the entry when its lookup returns a valid index. */
void apply_input_choice_value(s32 entry_id) {
    s32 entry_index;

    entry_index = select_choice_from_input_flags(entry_id);
    if (entry_index != -1) {
        write_choice_template_value(entry_id, entry_index);
    }
}

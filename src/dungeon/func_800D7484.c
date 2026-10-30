#include "common.h"
#include "m2c_compat.h"
#include "dungeon/menu.h"

s32 link_indexed_entry_chain();                    /* extern */
void set_attached_object_position(s32 *, s32);                            /* extern */
void initialize_nine_entry_links();              /* extern */

/* Run both setup calls, compute the result from the pointed value, and finalize. */
s32 run_object_setup_and_finalize(s32 *value_ptr, s32 context) {
    s32 result;

    set_attached_object_position(value_ptr, context);
    initialize_nine_entry_links(value_ptr, context);
    result = link_indexed_entry_chain(*value_ptr, context);
    copy_menu_vram_block();
    return result;
}

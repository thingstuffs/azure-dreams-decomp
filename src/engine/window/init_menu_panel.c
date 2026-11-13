#include "common.h"
#include "m2c_compat.h"
#include "engine/menu.h"
#include "engine/menu/animated_panel.h"
#include "engine/window.h"
#include "engine/util.h"

s16 read_terminal_tagged_entry_value();                             /* extern */
void init_menu_record_from_template();       /* extern */

/* Initializes resource state, resolves its size, and sets its position. */
void init_menu_panel(AnimatedMenuPanelBody *state, s32 config_id, s32 resource_id, s16 x, s16 y, s32 size) {
    s32 resource_handle;
    u16 resolved_size;
    s32 requested_size;

    sound_initialize_ordered_elements(state);
    state->tag_values = lookup_first_mask_value(config_id);
    resource_handle = func_8004DC14(resource_id, 1);
    requested_size = size;
    resolved_size = requested_size;
    state->resource_handle = resource_handle;
    requested_size = (s16)requested_size;
    if (requested_size == -1) {
        resolved_size = read_terminal_tagged_entry_value(resource_handle) + 0x20;
    }
    init_menu_record_from_template(state, state->template_buffer, resolved_size & 0xFFFF, state->flags & 1);
    state->template_word = (s32)(unsigned long)state->template_buffer;
    init_menu_panel_blocks(state, x, y, (s16) resolved_size);
}

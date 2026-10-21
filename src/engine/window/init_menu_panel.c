#include "common.h"
#include "m2c_compat.h"
#include "engine/menu.h"
#include "engine/window.h"

typedef struct S_8004A24C_0 {
    u16 unk_00;
    u8 pad_02[0x6];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
} S_8004A24C_0;   /* arg0 in init_menu_panel */

void menu_initialize_four_sub_blocks_position_offsets_fixed_header_derived_values();       /* extern */
s32 read_terminal_tagged_entry_value();                             /* extern */
void menu_copy_the_default_template_fills_five_byte_pairs_negated_half();       /* extern */
s32 func_8004DC14();                /* extern */

/* Initializes resource state, resolves its size, and sets its position. */
void init_menu_panel(S_8004A24C_0 *state, s32 config_id, s32 resource_id, s16 x, s16 y, s32 size) {
    s32 resource_handle;
    u16 resolved_size;
    s32 requested_size;

    sound_initialize_ordered_elements(state);
    state->unk_1C = lookup_first_mask_value(config_id);
    resource_handle = func_8004DC14(resource_id, 1);
    requested_size = size;
    resolved_size = requested_size;
    state->unk_18 = resource_handle;
    requested_size = (s16)requested_size;
    if (requested_size == -1) {
        resolved_size = read_terminal_tagged_entry_value(resource_handle) + 0x20;
    }
    menu_copy_the_default_template_fills_five_byte_pairs_negated_half(state, state->unk_08, resolved_size & 0xFFFF, state->unk_00 & 1);
    state->unk_14 = (s32) state->unk_08;
    menu_initialize_four_sub_blocks_position_offsets_fixed_header_derived_values(state, x, y, (s16) resolved_size);
}

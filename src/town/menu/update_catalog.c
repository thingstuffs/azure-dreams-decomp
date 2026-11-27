#include "common.h"
#include "m2c_compat.h"
#include "town/menu.h"
#include "town/menu/catalog.h"




/* Runs the initial handler, packs and bounds the state code, then runs the final handler. */
void update_catalog(CatalogDisplay *state) {
    s8 middle_bits;
    u8 packed_code;
    u8 code_bits;
    u16 below_limit;

    {
        u32 handler_index;
        void (*initial_handler)(CatalogDisplay *);

        handler_index = state->phase;
        initial_handler = D_80126B34[handler_index];
        initial_handler(state);
    }
    code_bits = state->page_index;
    middle_bits = state->column_index;
    packed_code = state->row_index;
    code_bits <<= 4;
    middle_bits <<= 3;
    code_bits += middle_bits;
    packed_code += code_bits;
    code_bits = packed_code & 0xFF;
    state->selected_entry = packed_code;
    below_limit = code_bits < 0x38U;
    if (below_limit == 0) {
        state->selected_entry = 0x31;
    } else {
        below_limit = code_bits < 0x31U;
        if (below_limit == 0) {
            state->selected_entry = 0x30;
        }
    }
    catalog_callbacks[state->phase](state);
}

/* MECHANISM: The true-space body uses a 24-byte frame and a local join at 0x8012677C, not a phantom
   call. Pointer-table declarations restore 4-byte indexing. */

#include "common.h"
#include "m2c_compat.h"
#include "engine/texture.h"
#include "frontend/libcard.h"
#include "main/data.h"
typedef struct S_800491F4 S_800491F4;

/* Forwards the input with fixed data D_80027F68 and parameter 0x12. */
void card_boot_link_three_row_panel_entries(S_800491F4 **input) {
    build_reverse_indexed_chain(input, &card_panel_chain_indices, 0x12);
}

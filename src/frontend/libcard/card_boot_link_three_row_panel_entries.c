#include "common.h"
#include "m2c_compat.h"
typedef struct S_800491F4 S_800491F4;

S_800491F4 *build_reverse_indexed_chain(S_800491F4 **, u8 *, s32);  /* extern */
extern u8 D_80027F68;

/* Forwards the input with fixed data D_80027F68 and parameter 0x12. */
void card_boot_link_three_row_panel_entries(S_800491F4 **input) {
    build_reverse_indexed_chain(input, &D_80027F68, 0x12);
}

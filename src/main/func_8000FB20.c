#include "common.h"
#include "m2c_compat.h"
typedef struct S_800491F4 S_800491F4;

S_800491F4 *build_reverse_indexed_chain(S_800491F4 **, u8 *, s32);  /* extern */
extern u8 D_80027F60;

/* Forwards the input to build_reverse_indexed_chain with &D_80027F60 and 7. */
void card_boot_link_message_display_entries(S_800491F4 **input) {
    build_reverse_indexed_chain(input, &D_80027F60, 7);
}

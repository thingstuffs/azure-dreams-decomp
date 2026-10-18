#include "common.h"
#include "m2c_compat.h"
typedef struct S_800491F4 S_800491F4;

S_800491F4 *build_reverse_indexed_chain(S_800491F4 **, u8 *, s32);  /* extern */
extern u8 D_80027FC4;

/* Forwards the value to build_reverse_indexed_chain with D_80027FC4 and 10. */
void card_boot_link_slot_window_entries(S_800491F4 **value) {
    build_reverse_indexed_chain(value, &D_80027FC4, 0xa);
}

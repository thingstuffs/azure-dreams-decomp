#include "common.h"
#include "m2c_compat.h"
typedef struct S_800491F4 S_800491F4;

S_800491F4 *build_reverse_indexed_chain(S_800491F4 **, u8 *, s32);  /* extern */
extern u8 D_8002808C;

/* Links nodes in the order specified by D_8002808C, stopping at an index of 4 or greater. */
void card_boot_link_paired_choice_display_entries(S_800491F4 **nodes) {
    build_reverse_indexed_chain(nodes, &D_8002808C, 4);
}

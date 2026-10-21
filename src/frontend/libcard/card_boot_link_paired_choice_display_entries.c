#include "common.h"
#include "m2c_compat.h"
#include "engine/texture.h"
#include "frontend/libcard.h"
#include "main/data.h"
typedef struct S_800491F4 S_800491F4;

/* Links nodes in the order specified by D_8002808C, stopping at an index of 4 or greater. */
void card_boot_link_paired_choice_display_entries(S_800491F4 **nodes) {
    build_reverse_indexed_chain(nodes, &card_choice_chain_indices, 4);
}

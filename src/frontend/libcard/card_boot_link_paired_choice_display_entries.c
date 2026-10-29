#include "common.h"
#include "m2c_compat.h"
#include "engine/texture.h"
#include "frontend/libcard.h"
#include "main/data.h"
typedef struct S_800491F4 S_800491F4;

/* Builds and returns a reverse chain of paired choice nodes using card_choice_chain_indices and limit 4. */
S_800491F4 *card_boot_link_paired_choice_display_entries(S_800491F4 **nodes) {
    return build_reverse_indexed_chain(nodes, card_choice_chain_indices, 4);
}

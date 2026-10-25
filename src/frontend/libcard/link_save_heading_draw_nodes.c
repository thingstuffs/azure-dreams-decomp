#include "common.h"
#include "m2c_compat.h"
#include "engine/texture.h"
#include "frontend/libcard.h"
#include "main/data.h"

typedef struct S_800491F4 S_800491F4;

/* Builds a reverse chain of save-heading nodes using save_heading_chain_indices and limit 4. */
struct S_800491F4 *link_save_heading_draw_nodes(void *input) {
    return build_reverse_indexed_chain(input, save_heading_chain_indices, 4);
}

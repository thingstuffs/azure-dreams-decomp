#include "common.h"
#include "m2c_compat.h"
#include "engine/texture.h"
#include "frontend/libcard.h"
#include "main/data.h"

typedef struct S_800491F4 S_800491F4;

/* Forwards input to build_reverse_indexed_chain with D_80028094 and the fixed argument 4. */
void link_save_heading_draw_nodes(void * input) {
    build_reverse_indexed_chain(input, &save_heading_chain_indices, 4);
}

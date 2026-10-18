#include "common.h"
#include "m2c_compat.h"

typedef struct S_800491F4 S_800491F4;
S_800491F4 *build_reverse_indexed_chain();          /* extern */
extern M2C_UNK D_80028094;

/* Forwards input to build_reverse_indexed_chain with D_80028094 and the fixed argument 4. */
void link_save_heading_draw_nodes(void * input) {
    build_reverse_indexed_chain(input, &D_80028094, 4);
}

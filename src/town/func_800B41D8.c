#include "common.h"

extern u8 D_800D1624[];
extern void build_reverse_indexed_chain(void *a0, void *a1, int a2);

/* Forwards the context and D_800D1624 to build_reverse_indexed_chain with selector 4. */
void process_context_with_selector_4(void *context) {
    build_reverse_indexed_chain(context, D_800D1624, 4);
}

#include "common.h"

extern u8 D_800D1624[];
extern void buildReverseIndexedChain(void *a0, void *a1, int a2);

/* Forwards the context and D_800D1624 to buildReverseIndexedChain with selector 4. */
void townProcessContextWithSelector4(void *context) {
    buildReverseIndexedChain(context, D_800D1624, 4);
}

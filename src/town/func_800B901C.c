#include "common.h"

extern void buildReverseIndexedChain(void *a0, void *a1, int a2);
extern u8 D_800D17C4[];

/* Passes the target and D_800D17C4 to buildReverseIndexedChain with argument 24. */
void townLinkMonsterStatusDisplayEntries(void *target) {
    buildReverseIndexedChain(target, D_800D17C4, 24);
}

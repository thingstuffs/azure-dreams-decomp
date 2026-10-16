#include "common.h"

extern u8 D_800D1760[];
extern void buildReverseIndexedChain(void *a0, void *a1, s32 a2);

/* Processes the target with D_800D1760 and parameter 41. */
void townProcessTargetWithCode41(void *target) {
    buildReverseIndexedChain(target, D_800D1760, 41);
}

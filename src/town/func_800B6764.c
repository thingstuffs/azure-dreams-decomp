#include "common.h"

extern unsigned char D_800D16BC[16];
extern void buildReverseIndexedChain(void *a0, void *a1, int a2);

/* Pass the target and D_800D16BC to buildReverseIndexedChain with code 33. */
void townProcessTargetWithCode33(void *target)
{
    buildReverseIndexedChain(target, D_800D16BC, 33);
}

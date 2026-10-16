#include "common.h"

extern void buildReverseIndexedChain(s32, void *, s32);
extern u8 D_800D1594[];

/* Link entries in D_800D1594 order until an index reaches 26. */
void townLinkItemMenuDisplayEntries(s32 entries) {
    buildReverseIndexedChain(entries, D_800D1594, 26);
}

#include "common.h"
#include "m2c_compat.h"
typedef struct S_800491F4 S_800491F4;

S_800491F4 *buildReverseIndexedChain(S_800491F4 **, u8 *, s32);  /* extern */
extern u8 D_80027F60;

/* Forwards the input to buildReverseIndexedChain with &D_80027F60 and 7. */
void cardBootLinkMessageDisplayEntries(S_800491F4 **input) {
    buildReverseIndexedChain(input, &D_80027F60, 7);
}

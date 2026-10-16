#include "common.h"
#include "m2c_compat.h"
typedef struct S_800491F4 S_800491F4;

S_800491F4 *buildReverseIndexedChain(S_800491F4 **, u8 *, s32);  /* extern */
extern u8 D_80027FF8;

/* Calls buildReverseIndexedChain for the target with fixed data and a value of 0x15. */
void func_80024C48(S_800491F4 **target) {
    buildReverseIndexedChain(target, &D_80027FF8, 0x15);
}

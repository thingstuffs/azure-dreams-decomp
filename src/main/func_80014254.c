#include "common.h"
#include "m2c_compat.h"

typedef struct S_800491F4 S_800491F4;
S_800491F4 *buildReverseIndexedChain();          /* extern */
extern M2C_UNK D_80028094;

/* Forwards input to buildReverseIndexedChain with D_80028094 and the fixed argument 4. */
void mainLinkSaveHeadingDrawNodes(void * input) {
    buildReverseIndexedChain(input, &D_80028094, 4);
}

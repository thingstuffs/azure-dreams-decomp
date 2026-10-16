#include "common.h"
#include "shared/town_handler.h"




typedef struct S_80094A60_0 {
    u8 pad_00[0x16];
    s16 unk_16;
} S_80094A60_0;   /* arg1 in townCallTheSelectedNonzeroTableCallee80094A38 */

/* Passes the selected nonzero table value to townStoreTheInForwardsField10Callee800949C4. */
void townCallTheSelectedNonzeroTableCallee80094A38(s32 *values, S_80094A60_0 *selector, void *ptr2) {
    s32 value = values[selector->unk_16];
    if (value != 0) {
        townStoreTheInForwardsField10Callee800949C4(value, (Rec_D_80082D58 *) selector, ptr2);
    }
}

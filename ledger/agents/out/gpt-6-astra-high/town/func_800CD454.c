#include "common.h"
#include "m2c_compat.h"

s32 func_8004A658();                /* extern */
M2C_UNK func_8008F104();     /* extern */
M2C_UNK func_8009B218(); /* extern */
extern M2C_UNK D_800D0678;

typedef struct S_800CABB4_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800CABB4_0;   /* arg2 in func_800CABB4 */

/* Initializes the state value and sets up the context using D_800D0678. */
void func_800CABB4(s32 contextId, M2C_UNK contextData, S_800CABB4_0 *state) {
    state->unk_08 = func_8004A658(4, 1);
    func_8008F104(contextId, contextData, &D_800D0678);
    func_8009B218(contextId, contextData, state, 0);
}

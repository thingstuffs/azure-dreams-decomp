#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

s32 func_8004A658();                /* extern */
M2C_UNK func_8008F104();     /* extern */
M2C_UNK func_8009B218(); /* extern */
extern M2C_UNK D_800D0678;


/* Initializes the state value and sets up the context using D_800D0678. */
void func_800CABB4(s32 contextId, M2C_UNK contextData, Rec_D_80082E80 *state) {
    state->unk_08 = func_8004A658(4, 1);
    func_8008F104(contextId, contextData, &D_800D0678);
    func_8009B218(contextId, contextData, state, 0);
}

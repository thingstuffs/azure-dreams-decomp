#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

s32 func_8004A658();                /* extern */
void func_8008F104();     /* extern */
void func_8009B218(); /* extern */
extern s32 D_800D0678[];


/* Initializes the state value and sets up the context using D_800D0678. */
void func_800CABB4(s32 contextId, s32 contextData, Rec_D_80082E80 *state) {
    state->unk_08 = func_8004A658(4, 1);
    func_8008F104(contextId, contextData, &D_800D0678);
    func_8009B218(contextId, contextData, state, 0);
}

#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

M2C_UNK func_80095388();                      /* extern */
M2C_UNK func_8009A1A4();        /* extern */


/* Advances and refreshes the state, then processes it when its increment is nonnegative. */
void func_80099B00(s32 context, EntityRec *state, M2C_UNK updateData) {
    state->z.v = (s32) (state->z.v + state->flags14);
    func_80095388(state);
    if (state->flags14 >= 0) {
        func_8009A1A4(context, state, updateData);
    }
}

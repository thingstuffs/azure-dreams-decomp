#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_80095388();                      /* extern */
M2C_UNK func_8009A1A4();        /* extern */


/* Advances and refreshes the state, then processes it when its increment is nonnegative. */
void func_80099B00(s32 context, Rec_D_800E3D7C *state, M2C_UNK updateData) {
    state->unk_08.at00_s32.v = (s32) (state->unk_08.at00_s32.v + state->unk_14.as_s32);
    func_80095388(state);
    if (state->unk_14.as_s32 >= 0) {
        func_8009A1A4(context, state, updateData);
    }
}

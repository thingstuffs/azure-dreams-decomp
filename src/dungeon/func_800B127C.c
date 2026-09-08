#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_80082E80.h"

M2C_UNK func_8008CAA0(); /* extern */
M2C_UNK func_8008CBA0(); /* extern */
M2C_UNK func_80090200(); /* extern */

/* Dispatch state handlers according to the signed state value and actor flags. */
void func_800B69DC(Rec_func_8008ACDC_arg0 *actor, M2C_UNK context, Rec_D_80082E80 *object, Rec_D_800E3D7C *state) {
    s16 state_value;

    state_value = state->unk_64.as_s16;
    if ((state_value < 0) || (actor->unk_10C & 1)) {
        object->unk_14.at00_u16.v = (u16) (object->unk_14.at00_u16.v & 0xF7FF);
        func_8008CAA0(actor, context, object, state);
        return;
    }
    if (state_value > 0) {
        func_8008CBA0(actor, context, object, state);
    }
    if ((actor->unk_9A.as_u8 != 0xD) && (state->unk_1C.as_s32 & 0x200)) {
        object->unk_14.at00_u16.v = (u16) (object->unk_14.at00_u16.v & 0xF7FF);
        func_80090200(actor, context, object, state);
    }
}

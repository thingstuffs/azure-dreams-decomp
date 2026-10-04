#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_80082E80.h"

void func_8008CAA0(); /* extern */
void func_8008CBA0(); /* extern */
void func_80090200(); /* extern */

/* Dispatch state handlers according to the signed state value and actor flags. */
void func_800B69DC(Rec_func_8008ACDC_arg0 *actor, s32 context, Rec_D_80082E80 *object, EntityRec *state) {
    s16 state_value;

    state_value = state->unk_64;
    if ((state_value < 0) || (actor->unk_10C & 1)) {
        object->unk_14.at00_u16.v = (u16) (object->unk_14.at00_u16.v & 0xF7FF);
        func_8008CAA0(actor, context, object, state);
        return;
    }
    if (state_value > 0) {
        func_8008CBA0(actor, context, object, state);
    }
    if ((actor->unk_9A.as_u8 != 0xD) && (state->flags1C & 0x200)) {
        object->unk_14.at00_u16.v = (u16) (object->unk_14.at00_u16.v & 0xF7FF);
        func_80090200(actor, context, object, state);
    }
}

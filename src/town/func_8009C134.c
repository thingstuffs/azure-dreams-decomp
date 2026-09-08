#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80098928();     /* extern */
s16 func_800C2AE8();                          


/* extern */

/* Update the object and its countdown, dispatching expiry handling when it runs out. */
void func_80099894(Rec_func_80094268_arg0 *state, Rec_D_800E3D7C *object, M2C_UNK context) {
    u16 ticks_left;

    object->unk_08.at02_s16.v = func_800C2AE8(object);
    ticks_left = state->unk_0A.as_u16 - 1;
    state->unk_0A.as_u16 = ticks_left;
    if ((s16) ticks_left < 0) {
        func_80098928(state, object, context);
        return;
    }
    object->unk_04.at00_s32.v = (s32) (object->unk_04.at00_s32.v + 0xFFFE0000);
}

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"
#include "records/Rec_D_800E3D7C.h"
/* Set the state flag, initialize the object's fixed-point value, and clear its paired field. */
void func_8008F27C(Rec_D_800CFCB4 *state, Rec_D_800E3D7C *object, s32 initial_value) {
    state->unk_35 = 1;
    object->unk_08.at00_s32.v = (s32) (initial_value << 0x10);
    object->unk_14.as_s32 = 0;
}

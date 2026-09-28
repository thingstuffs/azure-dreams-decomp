#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"
#include "shared/entity.h"
/* Set the state flag, initialize the object's fixed-point value, and clear its paired field. */
void func_8008F27C(Rec_D_800CFCB4 *state, EntityRec *object, s32 initial_value) {
    state->unk_35 = 1;
    object->z.v = (s32) (initial_value << 0x10);
    object->flags14 = 0;
}

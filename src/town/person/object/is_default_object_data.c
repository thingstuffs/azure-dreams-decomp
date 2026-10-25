#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "m2c_compat.h"

extern M2C_UNK D_800D68E8;


/* Checks whether the object's referenced value is the address of D_800D68E8. */
s32 is_default_object_data(Rec_func_80094268_arg0 *object) {
    return *object->unk_7C.as_ppm == &D_800D68E8;
}

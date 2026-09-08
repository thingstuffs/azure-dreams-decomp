#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_8009B6B4;
/* Set the state flag and assign the object's data pointer. */
void func_8009C0C0(Rec_func_80094268_arg0 *object, Rec_D_800CFCB4 *state) {
    state->unk_15 = 1;
    object->unk_50.as_pm = &D_8009B6B4;
}

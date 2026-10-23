#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"
#include "records/Rec_func_80094268_arg0.h"

extern M2C_UNK actor_surface_callback_address;
/* Set the state flag and assign the object's data pointer to D_8009B454. */
void set_actor_motion_state(Rec_func_80094268_arg0 *object, Rec_D_800CFCB4 *state) {
    state->unk_15 = 1;
    object->unk_50.as_pm = &actor_surface_callback_address;
}

#include "common.h"
#include "records/Rec_D_800CFCB4.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"
void update_motion_and_handle_terrain_contact(void *object, Rec_D_800CFCB4 *collision, EntityRec *motion, s32 callback_arg);
/* Set the state flag and assign the object's data pointer. */
void set_actor_drop_state(Rec_func_80094268_arg0 *object, Rec_D_800CFCB4 *state) {
    state->unk_15 = 1;
    object->unk_50.as_pm = &update_motion_and_handle_terrain_contact;
}

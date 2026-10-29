#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"


#include "town/person/object/initialize_object_entries_api.h"
#include "town/person/object.h"
extern M2C_UNK D_800C8788;
extern s32 D_800D627C[];


/* Initialize the object callback and set its state value to negative ten in fixed point. */
void initialize_object_callback(Rec_func_80094268_arg0 *object, ObjectPosition *state, void *init_data) {
    initialize_object_entries((Struct800C5724 *)(object), init_data, D_800D627C);
    object->unk_54 = &D_800C8788;
    state->velocity_z = 0xFFF60000;
}

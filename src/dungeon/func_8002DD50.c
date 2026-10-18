#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

extern M2C_UNK initialize_object_entries();
extern M2C_UNK D_800CB474;
extern M2C_UNK D_800D6938;


/* Decrement the object's counter and switch state with a ten-tick counter when it expires. */
void advance_object_counter_and_reset_state(Rec_func_80094268_arg0 *object, M2C_UNK unused, M2C_UNK context) {
    u16 remaining_ticks;

    remaining_ticks = object->unk_6C.as_u16 - 1;
    object->unk_6C.as_u16 = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        initialize_object_entries(object, context, &D_800D6938);
        object->unk_54 = &D_800CB474;
        object->unk_6C.as_u16 = 0xAU;
    }
}

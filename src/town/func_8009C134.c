#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"

void initialize_record_with_handler_table();     /* extern */
s16 query_lowered_transform_position();


/* extern */

/* Update the object and its countdown, dispatching expiry handling when it runs out. */
void update_object_and_countdown(Rec_func_80094268_arg0 *state, EntityRec *object, M2C_UNK context) {
    u16 ticks_left;

    object->z.w.i = query_lowered_transform_position(object);
    ticks_left = state->unk_0A.as_u16 - 1;
    state->unk_0A.as_u16 = ticks_left;
    if ((s16) ticks_left < 0) {
        initialize_record_with_handler_table(state, object, context);
        return;
    }
    object->y.v = (s32) (object->y.v + 0xFFFE0000);
}

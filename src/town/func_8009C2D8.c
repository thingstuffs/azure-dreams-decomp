/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"

void func_80098928();     
s16 func_800C2AE8();

void func_80099A38(Rec_func_80094268_arg0 *state, EntityRec *object, s32 context) {
    u16 ticks_left;

    object->z.w.i = func_800C2AE8(object);
    ticks_left = state->unk_0A.as_u16 - 1;
    state->unk_0A.as_u16 = ticks_left;
    if ((s16) ticks_left < 0) {
        func_80098928(state, object, context);
        return;
    }
    object->x.v = (s32) (object->x.v + 0x20000);
}

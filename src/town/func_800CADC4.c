#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_800C2E84();  /* extern */
M2C_UNK func_800C8A68();                     /* extern */
extern M2C_UNK D_800C84B8;
extern M2C_UNK D_800D62AC;


/* Decrement the object's countdown and advance its state when it expires. */
void func_800C8524(Rec_func_80094268_arg0 *object, M2C_UNK update_context, M2C_UNK state_context) {
    u16 ticks_left;

    ticks_left = object->unk_6C.as_u16 - 1;
    object->unk_6C.as_u16 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        func_800C8A68(update_context);
        func_800C2E84(object, state_context, &D_800D62AC);
        object->unk_54 = &D_800C84B8;
        object->unk_6C.as_u16 = 0x15U;
    }
}

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_800C2E84();          /* extern */
extern M2C_UNK D_800C8FF0;
extern M2C_UNK D_800D6268;


/* Decrement the object's countdown and advance its state when the countdown expires. */
void func_800C8F80(Rec_func_80094268_arg0 *object, M2C_UNK unused, M2C_UNK updateContext) {
    u16 remainingTicks;

    remainingTicks = object->unk_6C.as_u16 - 1;
    object->unk_6C.as_u16 = remainingTicks;
    if ((remainingTicks << 0x10) <= 0) {
        func_800C2E84(object, updateContext, &D_800D6268);
        object->unk_50.as_pm = &D_800C8FF0;
        object->unk_72.as_s16 = 0xC00;
        object->unk_6C.as_u16 = (u16) (object->unk_96.as_u8 * 3);
    }
}

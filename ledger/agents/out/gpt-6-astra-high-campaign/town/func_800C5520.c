#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_800478B8();                     /* extern */


/* Calls the handler when the object status is zero. */
void func_800C2C80(Rec_func_80094268_arg0 *object, M2C_UNK callback_arg) {
    if (object->unk_92 == 0) {
        func_800478B8(callback_arg);
    }
}

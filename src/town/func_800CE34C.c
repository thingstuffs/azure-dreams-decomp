#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CBAAC_0 {
    u8 pad_00[0x50];
    void (*unk_50)(void *, void *, M2C_UNK, M2C_UNK);
} S_800CBAAC_0;   /* arg0 in townInvokeObjectHandler */


/* Invoke the object handler with the object and forwarded arguments. */
void townInvokeObjectHandler(S_800CBAAC_0 *object, M2C_UNK callback_arg1, M2C_UNK callback_arg2) {
    object->unk_50(object, object, callback_arg1, callback_arg2);
}

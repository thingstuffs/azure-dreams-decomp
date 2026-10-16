#include "common.h"
#include "m2c_compat.h"

void townClearEntityRecordFields();                     /* extern */
extern M2C_UNK D_800982EC;

typedef struct S_80098F10_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_80098F10_0;   /* arg0 in townClearRecordAndSetNextHandler */

/* Run object setup and assign its next handler. */
void townClearRecordAndSetNextHandler(S_80098F10_0 *object, M2C_UNK setup_arg) {
    townClearEntityRecordFields(setup_arg);
    object->unk_04 = &D_800982EC;
}

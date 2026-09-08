#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C41D4(M2C_UNK);                            /* extern */

typedef struct S_800C3C28_0 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800C3C28_0;   /* arg2 in func_800C3C28 */

/* Calls the object handler when either monitored status flag is set. */
void func_800C3C28(M2C_UNK object, M2C_UNK unused, S_800C3C28_0 *status) {
    if (status->unk_14 & 0x6000) {
        func_800C41D4(object);
    }
}

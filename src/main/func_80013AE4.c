#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004CB2C();                         /* extern */

/* Process the embedded records at offsets 4 and 0x10. */
void func_80026AE4(s32 record_addr) {
    func_8004CB2C(record_addr + 4);
    func_8004CB2C(record_addr + 0x10);
}

#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80023A78();      /* extern */
M2C_UNK func_80023E14();                         /* extern */
M2C_UNK func_80023F94(s32, M2C_UNK, M2C_UNK);                            /* extern */

/* Configures the record, processes its embedded data, and updates the record. */
void func_80023FA0(s32 record, M2C_UNK setup_value, M2C_UNK processing_value) {
    func_80023F94(record, setup_value, processing_value);
    func_80023A78(record + 0x24C, record + 0x224, record + 0x234, processing_value);
    func_80023E14(record);
}

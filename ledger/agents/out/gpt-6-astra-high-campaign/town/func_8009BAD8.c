#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80094984();              /* extern */
M2C_UNK func_8009A1E8();       /* extern */
extern M2C_UNK D_800D0130;

/* Initialize the record from fixed data and apply its update parameters. */
void func_80099238(s32 record, M2C_UNK update_value, M2C_UNK init_context) {
    func_80094984(&D_800D0130, record, init_context);
    func_8009A1E8(record, update_value, init_context);
}

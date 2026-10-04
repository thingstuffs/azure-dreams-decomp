#include "common.h"
#include "m2c_compat.h"

void func_80094984();              /* extern */
void func_8009A1E8();       /* extern */
extern M2C_UNK D_800D0130;

/* Initialize the record from fixed data and apply its update parameters. */
void func_80099238(s32 record, s32 update_value, s32 init_context) {
    func_80094984(&D_800D0130, record, init_context);
    func_8009A1E8(record, update_value, init_context);
}

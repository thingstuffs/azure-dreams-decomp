#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B2DA0_arg1.h"

M2C_UNK func_800B2DA0();                 /* extern */
M2C_UNK func_800B30D8(Rec_func_800B2DA0_arg1 *);                            /* extern */
M2C_UNK func_800B32D4();                      /* extern */
M2C_UNK func_800B336C();                      /* extern */


/* Update the linked record components and finalize the data at offset 0x68. */
void func_800B3440(Rec_func_800B2DA0_arg1 *record) {
    func_800B30D8(record);
    func_800B336C(record);
    func_800B32D4(record);
    func_800B2DA0(record->unk_A8 + 0x68, record);
}

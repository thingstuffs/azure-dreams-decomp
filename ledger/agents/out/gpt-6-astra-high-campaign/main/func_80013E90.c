#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80026CF0_arg0.h"

M2C_UNK func_80026C00();         /* extern */
M2C_UNK func_80026D78();                       /* extern */


/* Store the initial value, link embedded data, and update the record. */
void func_80026E90(s8 *record, s32 initial_value) {
    ((Rec_func_80026CF0_arg0 *)record)->unk_00 = initial_value;
    func_80026C00(record + 0x50, record + 0x28, record + 0x38);
    func_80026D78(record);
}

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AF254_arg1.h"

M2C_UNK func_800AF254();                 /* extern */
M2C_UNK func_800AF520(Rec_func_800AF254_arg1 *);                            /* extern */
M2C_UNK func_800AF674();                      /* extern */
M2C_UNK func_800AF784();                      /* extern */
M2C_UNK func_800AF858();                 /* extern */


/* Run the record update sequence and process its stored value. */
void func_800AF860(Rec_func_800AF254_arg1 *record) {
    func_800AF520(record);
    func_800AF784(record);
    func_800AF674(record);
    func_800AF254(record->unk_A8.as_s32, record);
    func_800AF858(record->unk_A8.as_s32, record);
}

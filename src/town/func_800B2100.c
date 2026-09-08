#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AF254_arg1.h"

M2C_UNK func_800AF254();                 /* extern */
M2C_UNK func_800AF520(Rec_func_800AF254_arg1 *);                            /* extern */
M2C_UNK func_800AF674();                      /* extern */
M2C_UNK func_800AF784();                      /* extern */
M2C_UNK func_800AF858();                 /* extern */


void func_800AF860(Rec_func_800AF254_arg1 *arg0) {
    func_800AF520(arg0);
    func_800AF784(arg0);
    func_800AF674(arg0);
    func_800AF254(arg0->unk_A8.as_s32, arg0);
    func_800AF858(arg0->unk_A8.as_s32, arg0);
}

#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_func_800381D0_arg0.h"



s32 func_80038240();                              /* extern */
s32 func_80053EF0();                         /* extern */
extern M2C_UNK func_80038288;
extern M2C_UNK func_800382F0;
extern M2C_UNK func_8003832C;

M2C_UNK *func_800381D0(Rec_func_800381D0_arg0 *arg0) {
    if (func_80053EF0(4) != 0x100) {
        if (func_80038240(*arg0->unk_1C) != 0) {
            return &func_800382F0;
        }
        return &func_8003832C;
    }
    return &func_80038288;
}

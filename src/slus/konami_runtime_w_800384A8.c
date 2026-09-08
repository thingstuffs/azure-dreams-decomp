#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_func_800384A8_arg0.h"



M2C_UNK func_80038538();                      /* extern */
s32 func_80053EF0();                         /* extern */
extern M2C_UNK func_800384F8;

void func_800384A8(Rec_func_800384A8_arg0 *arg0) {
    if (func_80053EF0(4) != 0x100) {
        func_80038538(arg0);
        return;
    }
    arg0->unk_10 = &func_800384F8;
}

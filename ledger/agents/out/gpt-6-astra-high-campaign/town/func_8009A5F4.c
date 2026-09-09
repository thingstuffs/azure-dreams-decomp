#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80097D54_arg0.h"

s32 func_800352FC(Rec_func_80097D54_arg0 *, M2C_UNK, M2C_UNK, s32);                                /* extern */
M2C_UNK func_80093D90();    /* extern */
M2C_UNK func_80098988();    /* extern */
extern M2C_UNK D_800CFFF0;

/* Check the record, tick its countdown, and dispatch the appropriate handler. */
void func_80097D54(Rec_func_80097D54_arg0 *record, M2C_UNK call_arg_1, M2C_UNK call_arg_2, s32 check_arg) {
    u16 countdown;

    if (func_800352FC(record, call_arg_1, call_arg_2, check_arg) == 0) {
        countdown = record->unk_0A - 1;
        record->unk_0A = countdown;
        if ((countdown << 0x10) <= 0) {
            if (record->unk_1C == &D_800CFFF0) {
                func_80093D90(record, call_arg_1, call_arg_2);
                return;
            }
            goto finish;
        }
    } else {
finish:
        func_80098988(record, call_arg_1, call_arg_2);
    }
}

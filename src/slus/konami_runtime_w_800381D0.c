#include "common.h"

#include "common.h"
#include "records/Rec_func_800381D0_arg0.h"


s32 func_80038240();                              /* extern */
s32 func_80053EF0();                         /* extern */
void func_80038288();
void func_800382F0();
void func_8003832C();

/* Selects the next handler based on runtime status and the context byte. */
s32 *func_800381D0(Rec_func_800381D0_arg0 *context) {
    if (func_80053EF0(4) != 0x100) {
        if (func_80038240(*context->unk_1C) != 0) {
            return &func_800382F0;
        }
        return &func_8003832C;
    }
    return &func_80038288;
}

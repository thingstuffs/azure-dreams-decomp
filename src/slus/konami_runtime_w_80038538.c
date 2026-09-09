#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_func_800384A8_arg0.h"



M2C_UNK SD_Call();                     /* extern */
extern M2C_UNK func_80038A10;

/* Calls SD_Call with 0xB4 and installs func_80038A10 as the next handler. */
void func_80038538(Rec_func_800384A8_arg0 *state) {
    SD_Call(0xB4);
    state->unk_10 = &func_80038A10;
}

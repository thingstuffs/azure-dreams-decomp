#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



M2C_UNK func_80016CC4();                            /* extern */
void func_80016DBC();                            /* extern */


/* Run both setup routines and invoke the state callback with 0xE and 0x200. */
s32 func_80017534(void) {
    func_80016CC4();
    func_80016DBC();
    D_80016000->unk_20->callback_2F8(0xE, 0x200);
    return 0;
}

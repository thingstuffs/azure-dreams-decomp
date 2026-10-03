#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



M2C_UNK func_80016CC4();                            /* extern */


/* Run setup and invoke the state callback with 0xF and 0x200. */
s32 func_80017BC4(void) {
    func_80016CC4();
    D_80016000->unk_20->callback_2F8(0xF, 0x200);
    return 0;
}

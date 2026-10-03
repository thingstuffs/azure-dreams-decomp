#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



M2C_UNK func_800177C4();                     /* extern */


/* Dispatches mode 2, then invokes the handler for 0x596. */
void func_8054FB90(void) {
    D_80016000->unk_20->callback_1F4(2);
    func_800177C4(0x596);
}

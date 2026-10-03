#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


/* Invoke the state callback with fixed parameters and return success. */
s32 func_80017E5C(void) {
    D_80016000->unk_20->callback_310(0x26, 0x200, 0x9000);
    return 1;
}

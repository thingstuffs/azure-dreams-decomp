#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



/* Invoke the system object callback with 0x25 and 0x200. */
void func_80017458(void) {
    D_80016000->unk_20->callback_238(0x25, 0x200);
}

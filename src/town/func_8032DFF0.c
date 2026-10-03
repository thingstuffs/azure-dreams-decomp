#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



/* Invoke the callback at offset 0x1E8 with code 7. */
void func_800187F0(void) {
    D_80016000->unk_20->callback_1E8(7);
}

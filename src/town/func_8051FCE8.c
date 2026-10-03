#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



/* Dispatches the supplied value with bit 0x8000 set. */
void func_8051FCE8(s32 value) {
    D_80016000->unk_20->callback_280(value | 0x8000);
}

#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
#include "shared/town_root.h"



extern M2C_UNK D_8001601C;

/* Invoke the context callback with the global data and offset context value. */
void func_8047E278(void) {
    ((M2C_UNK (*) (M2C_UNK *, s32))D_80016000->unk_20->callback_26C)(&D_8001601C,
        ((s32)D_80016000->unk_38) + 0x20C);
}

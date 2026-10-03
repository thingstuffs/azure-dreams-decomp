#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



extern M2C_UNK D_800186A8;


/* Return the table value selected by the callback at offset 0x2D4. */
s32 func_80019514(void) {
    return *(s32 *)((s8 *) &D_800186A8 + (D_80016000->unk_20->callback_2D4(0) * 4));
}

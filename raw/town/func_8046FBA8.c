#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



extern s32 D_8001AC3C;


/* Pass D_8001AC3C to the callback at offset 0x21C. */
void func_8046FBA8(void) {
    D_80016000->unk_20->callback_218(&D_8001AC3C);
}

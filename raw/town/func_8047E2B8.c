#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



extern s32 D_80017870;


/* Pass D_80017870 to the callback at offset 0x21C. */
void func_8047E2B8(void) {
    D_80016000->unk_20->callback_224(&D_80017870);
}

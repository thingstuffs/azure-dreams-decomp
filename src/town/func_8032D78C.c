#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



extern M2C_UNK D_8001C0FC;


/* Pass D_8001C0FC to the callback at offset 0x21C. */
void func_80017F8C(void) {
    D_80016000->unk_20->callback_21C(&D_8001C0FC);
}

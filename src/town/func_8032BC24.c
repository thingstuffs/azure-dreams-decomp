#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



extern M2C_UNK D_8001BF80;


/* Pass D_8001BF80 and 0x14 to the object callback. */
void func_80016424(void) {
    D_80016000->unk_20->callback_344(&D_8001BF80, 0x14);
}

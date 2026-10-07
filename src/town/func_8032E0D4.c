#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



/* Clears the byte at offset 0x114 in the linked record. */
void func_800188D4(void) {
    ((TownProgressState *)D_80016000->unk_40)->unk_114 = 0;
}

#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"


/* Sets the referenced object's flag at offset 0x114 to 1. */
void func_800188B8(void) {
    ((TownProgressState *)D_80016000->unk_40)->unk_114 = 1;
}

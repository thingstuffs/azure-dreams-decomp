#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



/* Returns the byte at offset 0x114 in the referenced record. */
u8 func_800188EC(void) {
    return ((u8)((TownProgressState *)D_80016000->unk_40)->unk_114);
}

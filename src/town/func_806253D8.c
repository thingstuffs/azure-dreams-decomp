/* Relink of matched town/func_806149C0; every changed retail word is a paired relocation. */
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



/* Returns whether the referenced record's unk_38 field differs from 2. */
s32 func_800163D8(void) {
    return ((TownPositionState *)D_80016000->unk_1C)->unk_38 != 2;
}

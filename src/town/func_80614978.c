#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



/* Return whether the referenced record's unk_38 field is nonzero. */
s32 func_80614978(void) {
    return ((TownPositionState *)D_80016000->unk_1C)->unk_38 != 0;
}

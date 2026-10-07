#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"


/* Set the inner object's unk4 and unk8 fields to 1248 and 1184. */
void func_80016EF4(void) {
    ((TownPositionState *)D_80016000->unk_1C)->x = 1248;
    ((TownPositionState *)D_80016000->unk_1C)->y = 1184;
}

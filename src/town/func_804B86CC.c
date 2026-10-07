#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"


/* Set the town substate values to 800 and 1184. */
void func_80016ECC(void) {
    ((TownPositionState *)D_80016000->unk_1C)->x = 800;
    ((TownPositionState *)D_80016000->unk_1C)->y = 1184;
}

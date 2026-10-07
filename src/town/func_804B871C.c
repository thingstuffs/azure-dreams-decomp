#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



/* Initialize both linked record values to 0x4E0. */
void func_80016F1C(void) {
    ((TownPositionState *)D_80016000->unk_1C)->x = 0x4E0;
    ((TownPositionState *)D_80016000->unk_1C)->y = 0x4E0;
}

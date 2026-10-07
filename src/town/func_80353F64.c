#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



/* Set the current record's linked state fields to 0x15 and 0x12. */
void func_80353F64(void) {
    ((TownPositionState *)D_80016000->unk_1C)->x = 0x15;
    ((TownPositionState *)D_80016000->unk_1C)->y = 0x12;
}

#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))


/* Set the current record's two state values to 0x560 and 0x3E0. */
void func_80016F40(void) {
    ((TownPositionState *)D_80016000->unk_1C)->x = 0x560;
    ((TownPositionState *)D_80016000->unk_1C)->y = 0x3E0;
}

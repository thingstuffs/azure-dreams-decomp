#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"


/* Set the substructure's unk4 and unk8 fields to 864 and 1056. */
void func_80017E34(void) {
    ((TownPositionState *)D_80016000->unk_1C)->x = 864;
    ((TownPositionState *)D_80016000->unk_1C)->y = 1056;
}

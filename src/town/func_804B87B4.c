#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"


/* Set the current inner object's unk4 and unk8 values to 1696 and 864. */
void func_80016FB4(void) {
    ((TownPositionState *)D_80016000->unk_1C)->x = 1696;
    ((TownPositionState *)D_80016000->unk_1C)->y = 864;
}

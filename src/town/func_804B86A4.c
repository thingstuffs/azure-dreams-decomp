#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"


/* Set the referenced object's unk4 and unk8 fields to 800 and 736. */
void func_80016EA4(void) {
    ((TownPositionState *)D_80016000->unk_1C)->x = 800;
    ((TownPositionState *)D_80016000->unk_1C)->y = 736;
}

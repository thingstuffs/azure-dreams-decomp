#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"


/* Set the referenced structure's two values to 1248 and 992. */
void func_80016F68(void) {
    ((TownPositionState *)D_80016000->unk_1C)->x = 1248;
    ((TownPositionState *)D_80016000->unk_1C)->y = 992;
}

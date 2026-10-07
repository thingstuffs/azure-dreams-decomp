#include "shared/town_pointees.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"



/* Initialize the three context fields to 1, 11, and 3. */
void func_80480208(void) {
    (*(s32 * *)((u8 *)(((void **)D_80016000->unk_1C)) + 0)) = 1;
    ((TownPositionState *)D_80016000->unk_1C)->x = 11;
    ((TownPositionState *)D_80016000->unk_1C)->y = 3;
}

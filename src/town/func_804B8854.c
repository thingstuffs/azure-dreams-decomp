#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"


/* Set the town state's unk4 and unk8 values to 0x6A0 and 0x4A0. */
void func_80017054(void) {
    ((TownPositionState *)D_80016000->unk_1C)->x = 0x6A0;
    ((TownPositionState *)D_80016000->unk_1C)->y = 0x4A0;
}

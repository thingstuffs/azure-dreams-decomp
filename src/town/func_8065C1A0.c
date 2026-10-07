#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



extern s32 D_800183D4;


/* Copy the linked record's unk_34 value into D_800183D4. */
void func_8065C1A0(void) {
    D_800183D4 = ((TownPositionState *)D_80016000->unk_1C)->unk_34;
}

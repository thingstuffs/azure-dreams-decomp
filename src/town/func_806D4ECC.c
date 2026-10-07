#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"



/* Return the callback result for the pair (5, 0x17) minus the stored value. */
s32 func_806D4ECC(void) {
    s8 queryPair[2];

    queryPair[1] = 0x17;
    queryPair[0] = 5;
    return ((s32 (*) (s8 *))D_80016000->unk_20->callback_050)(queryPair)
    - ((TownProgressState *)D_80016000->unk_40)->unk_110;
}

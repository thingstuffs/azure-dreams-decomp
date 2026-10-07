#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"



/* Checks whether the stored value is at least the callback result for query {5, 0x17}. */
s32 func_8001890C(void) {
    s8 queryArgs[2];

    queryArgs[1] = 0x17;
    queryArgs[0] = 5;
    return (s32) ((u32)((TownProgressState *)D_80016000->unk_40)->unk_110)
    >= ((u32 (*) (s8 *))D_80016000->unk_20->callback_050)(queryArgs);
}

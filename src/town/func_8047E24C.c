#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



extern M2C_UNK D_8001781C;
extern M2C_UNK *D_8001794C;
extern M2C_UNK D_8001857C;


/* Set the global and current record's pointers to their static data. */
void func_8047E24C(void) {
    D_8001794C = &D_8001781C;
    ((TownPositionState *)D_80016000->unk_1C)->unk_40 = &D_8001857C;
}

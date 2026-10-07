#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



extern M2C_UNK D_80018AE4;
extern M2C_UNK *D_80018BA4;
extern M2C_UNK D_80018B38;


/* Initializes the global and current record's data pointers. */
void func_806D4EA0(void) {
    D_80018BA4 = &D_80018AE4;
    ((TownPositionState *)D_80016000->unk_1C)->unk_40 = &D_80018B38;
}

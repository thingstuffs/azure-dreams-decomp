#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



void func_80016100(void);                            /* extern */
extern M2C_UNK D_80017A7C;
extern M2C_UNK *D_80017B90;
extern M2C_UNK D_80017F64;


/* Run setup and install the global and context pointers. */
void func_8072A244(s32 setup_input, s32 setup_param) {
    func_80016100();
    D_80017B90 = &D_80017A7C;
    ((TownPositionState *)D_80016000->unk_1C)->unk_40 = &D_80017F64;
}

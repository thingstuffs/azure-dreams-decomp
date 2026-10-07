#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"



void func_800174CC();                            /* extern */
extern M2C_UNK D_80019814;
extern M2C_UNK D_80019884;
extern s32 D_80019AF8;
extern void *D_80019B90;

/* Initializes data pointers and computes the selected eight-byte entry address. */
void func_805D352C(void) {
    func_800174CC();
    D_80019B90 = &D_80019814;
    D_80019AF8 = ((s32)D_80016000->unk_40)
    + (D_80016000->unk_08 * 8);
    ((TownPositionState *)D_80016000->unk_1C)->unk_40 = &D_80019884;
}

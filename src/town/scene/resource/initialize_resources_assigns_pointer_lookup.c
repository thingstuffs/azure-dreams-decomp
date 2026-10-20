#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



void func_80018F8C(s32 slotIndex);
s32 func_800198A4();                /* extern */
s32 func_8001A554(s32);
s32 func_8001A5CC(s32);
extern M2C_UNK D_8002116C;


/* Initializes resources and assigns their data pointer when lookup succeeds. */
void initialize_resources_assigns_pointer_lookup(void) {
    s32 resource_id;

    resource_id = func_800198A4(0xD, 6);
    if (resource_id != -1) {
        func_80018F8C(resource_id);
        func_8001A554(F_sbs32_pad02);
        func_8001A554(F_sbs32_pad03);
        func_8001A554(F_sbs32_pad04);
        func_8001A554(F_sbs32_pad05);
        func_8001A554(F_sbs32_pad06);
        func_8001A554(F_okami_give_cape);
        func_8001A5CC(F_sbs32_pad25);
        ((TownPositionState *)D_80016000->unk_1C)->unk_40 = &D_8002116C;
    }
}

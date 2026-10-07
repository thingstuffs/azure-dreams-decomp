#include "common.h"
#include "m2c_compat.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 D_800190C0[3];


/* Store two 16.16 values, clear the third component, and invoke both callbacks. */
void func_806C51B0(void) {
    s32 *fixed_values;
    s32 second_value;

    D_800190C0[0] =
        ((TownPositionState *)D_80016000->unk_1C)->x
    << 16;
    second_value =
        ((TownPositionState *)D_80016000->unk_1C)->y;
    fixed_values = D_800190C0;
    fixed_values[2] = 0;
    fixed_values[1] = second_value << 16;
    ((M2C_UNK (*) (M2C_UNK))D_80016000->unk_20->callback_208)(0);
    ((M2C_UNK (*) (M2C_UNK))D_80016000->unk_20->callback_228)(0);
}

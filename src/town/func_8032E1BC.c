#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
#include "shared/town_root.h"


extern s32 func_8001890C(void);
extern u32 D_8001C368[];

/* Decrements the object's counter and invokes a callback if the object check succeeds. */
void func_800189BC(void) {
    TownStateRecord *counter_obj;

    counter_obj = D_80016000->unk_38;
    counter_obj->unk_2D5C = (u32) (((signed int)counter_obj->unk_2D5C) - D_8001C368[0]);
    if (func_8001890C() != 0) {
        ((M2C_UNK (*) (M2C_UNK, M2C_UNK))D_80016000->unk_20->callback_04C)(0x10,
            5);
    }
}

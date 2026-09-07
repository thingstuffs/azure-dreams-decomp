#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_80035484();   /* extern */
extern M2C_UNK D_80081EB0;
extern M2C_UNK D_800820A8;

/* Passes the fixed runtime data pair and supplied value to func_80035484. */
void func_80034F58(s32 value) {
    func_80035484(&D_800820A8, &D_80081EB0, value);
}

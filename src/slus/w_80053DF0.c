#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_800552C8();                            /* extern */
extern s16 D_8008480A;

/* Sets D_8008480A to the new value and calls func_800552C8. */
void func_80053DF0(s16 new_value) {
    D_8008480A = new_value;
    func_800552C8();
}

#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_800552C8();                            /* extern */
extern s16 D_8008480A;

void func_80053DF0(s16 arg0) {
    D_8008480A = arg0;
    func_800552C8();
}

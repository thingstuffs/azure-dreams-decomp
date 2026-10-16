#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80016530;
extern s32 D_80019BB4;

s32 func_80017890(void) {
    return *((D_80019BB4 * 4) + &D_80016530);
}

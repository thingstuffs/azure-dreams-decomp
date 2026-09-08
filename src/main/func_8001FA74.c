#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003D548();                     /* extern */
M2C_UNK func_80400EF8();                            /* extern */
extern s8 D_8008CA34;

/* Set the global mode to 2 and invoke the transition routines. */
void func_8001FA74(void) {
    D_8008CA34 = 2;
    func_80400EF8();
    func_8003D548(3);
}

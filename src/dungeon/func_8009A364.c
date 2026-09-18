#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK *D_8001371C;
extern M2C_UNK D_80013720;

/* Point D_8001371C at D_80013720. */
void func_8009FAC4(void) {
    (*(__typeof__(D_8001371C) *)0x8001371C) = (M2C_UNK *) 0x80013720;
}

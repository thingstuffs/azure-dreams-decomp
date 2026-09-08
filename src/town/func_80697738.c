#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80016B1C();              /* extern */
extern s32 D_80018AE0;
extern M2C_UNK D_80018AE8;

/* Stores the result of func_80016B1C(&D_80018AE8, 1) in D_80018AE0. */
void func_80697738(void) {
    D_80018AE0 = func_80016B1C(&D_80018AE8, 1);
}

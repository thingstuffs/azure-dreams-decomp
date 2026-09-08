#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80016104();              /* extern */
extern M2C_UNK D_80018E60;

/* Passes the value to func_80016104 with D_80018E60 as context. */
void func_80016A6C(s32 value) {
    func_80016104(&D_80018E60, value);
}

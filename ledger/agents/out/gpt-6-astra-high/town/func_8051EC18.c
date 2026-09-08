#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80018A64();                     /* extern */
extern M2C_UNK D_80020B64;

/* Pass 0x5C7 to func_80018A64 and return the address of D_80020B64. */
M2C_UNK *func_8051EC18(void) {
    func_80018A64(0x5C7);
    return &D_80020B64;
}

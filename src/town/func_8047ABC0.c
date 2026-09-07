#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800197D8();                     /* extern */
extern M2C_UNK D_8001A054;

M2C_UNK *func_8047ABC0(void) {
    func_800197D8(0x403);
    return &D_8001A054;
}

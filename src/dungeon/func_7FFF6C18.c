#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80094984();       /* extern */
extern M2C_UNK D_8009221C;
extern M2C_UNK D_800D00B8;

void func_80094378(M2C_UNK **arg0) {
    func_80094984(&D_800D00B8, arg0);
    *arg0 = &D_8009221C;
}

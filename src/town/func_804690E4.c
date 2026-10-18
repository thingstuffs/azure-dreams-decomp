#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80019D60();                   /* extern */
extern M2C_UNK D_80017BAC;

/* Passes D_80017BAC to func_80019D60. */
void apply_global_delta_record_k(void) {
    func_80019D60(&D_80017BAC);
}

#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800B2E3C();                         /* extern */

/* Calls func_800B2E3C with the input offset by 0x20. */
void forward_offset_to_record_loader(s32 base) {
    func_800B2E3C(base + 0x20);
}

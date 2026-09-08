#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800D4748;

/* Pass the keima resource to handler 6 and finalize the operation. */
void func_800C23A8(void) {
    func_8003E4FC(6, &D_800D4748, 0);
    func_8003F320();
}

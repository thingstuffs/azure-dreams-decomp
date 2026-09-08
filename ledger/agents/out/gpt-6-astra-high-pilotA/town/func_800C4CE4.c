#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800D4750;

/* Dispatch event 6 with D_800D4750 and process pending updates. */
void func_800C2444(void) {
    func_8003E4FC(6, &D_800D4750, 0);
    func_8003F320();
}

#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80018A0C;
extern u8 *D_80018BF0;

void func_80697518(void) {
    D_80018BF0 = &D_80018A0C;
}

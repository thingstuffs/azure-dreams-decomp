#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80018A64(s32);

/* Call func_80018A64 with IDs 0x1476 and 0x5C3 in sequence. */
void func_8051EAD0(void) {
    func_80018A64(0x1476);
    func_80018A64(0x5C3);
}

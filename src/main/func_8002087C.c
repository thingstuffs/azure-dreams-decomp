#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void func_804072CC(void *state, s32 *enabled, s32 *selected);                         /* extern */

/* Passes the input value plus 0x20 to func_804072CC. */
void func_8002087C(s32 value, s32 *enabled, s32 *selected) {
    func_804072CC((void *)(value + 0x20), enabled, selected);
}

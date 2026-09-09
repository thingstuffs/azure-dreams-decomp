#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */

extern void func_80018E34(s32);
/* Pass the value to func_80018E34, then call func_80018EA8. */
void func_800191C4(s32 value) {
    func_80018E34(value);
    func_80018EA8();
}

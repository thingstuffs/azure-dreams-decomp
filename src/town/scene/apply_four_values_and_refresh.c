#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80018BE4(s32, s32, s32, s32);
s32 func_80018C58(void);

/* Passes all four values to func_80018BE4, then runs func_80018C58. */
void apply_four_values_and_refresh(s32 value0, s32 value1, s32 value2, s32 value3) {
    func_80018BE4(value0, value1, value2, value3);
    func_80018C58();
}

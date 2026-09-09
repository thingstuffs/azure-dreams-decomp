#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */

extern void func_80045C34(u8 *, s32, void *);
/* Pass the buffer, value, and data to func_80045C34 and return zero. */
s32 func_800BBA20(u8 *buffer, s32 value, void *data) {
    func_80045C34(buffer, value, data);
    return 0;
}

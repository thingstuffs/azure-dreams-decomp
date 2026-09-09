#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */

extern void func_80019B54(void *, s32);
/* Forward the context and request to func_80019B54. */
void func_800179BC(void *context, s32 request) {
    func_80019B54(context, request);
}

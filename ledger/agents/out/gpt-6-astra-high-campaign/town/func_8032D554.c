#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */

extern void func_80019C68(void *, s32);
/* Forward the context and request to func_80019C68. */
void func_80017D54(void *context, s32 request) {
    func_80019C68(context, request);
}

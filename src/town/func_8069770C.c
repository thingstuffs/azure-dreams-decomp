#include "common.h"
#include "shared/town_dispatch_data.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80016B1C();              /* extern */
extern s32 D_80018AE0;

/* Store the result of calling func_80016B1C on D_80018AE8. */
void func_8069770C(void) {
    D_80018AE0 = func_80016B1C(&D_80018AE8, 0);
}

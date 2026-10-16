#include "common.h"
#include "m2c_compat.h"

void cardBootInitServer();                            /* extern */
void closeTimer2UpdateEvent();                            /* extern */
extern s8 D_80080A84;

/* Run setup callbacks and set the active flag. */
void cardBootStopTimerAndInitServer(void) {
    closeTimer2UpdateEvent();
    D_80080A84 = 1;
    cardBootInitServer();
}

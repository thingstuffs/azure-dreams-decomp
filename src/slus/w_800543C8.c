#include "common.h"

extern int D_800847D4[3]; /* size > 8 to force %hi/%lo addressing (see gp-vs-hilo notes) */

extern void processFirstPendingSoundChannel(void);
extern void func_800544A4(void);
extern void func_8005440C(void);

/* Reactivates a pending locked channel and updates audio tasks. */
void func_800543C8(void)
{
    if (D_800847D4[0] & 0xFF000000) {
        processFirstPendingSoundChannel();
    }
    func_800544A4();
    func_8005440C();
}

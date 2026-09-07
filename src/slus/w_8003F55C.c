#include "common.h"

/* Waits for CD sync to complete; if the sync result is "no intr" (2),
 * issues a CdlPause control command writing into the global CD position
 * buffer, then converts that position to an integer (sector count). */
extern int CdSync(int mode, unsigned char *result);
extern int CdControl(unsigned char com, unsigned char *param, unsigned char *result);
extern int CdPosToInt(unsigned char *loc);

unsigned char D_800814B8[16];

int func_8003F55C(void) {
    if (CdSync(1, 0) == 2) {
        CdControl(0x10, 0, D_800814B8);
    }
    return CdPosToInt(D_800814B8);
}

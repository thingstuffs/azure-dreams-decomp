#include "common.h"

extern int CdSync(int mode, unsigned char *result);
extern int CdControl(unsigned char com, unsigned char *param, unsigned char *result);
extern int CdPosToInt(unsigned char *loc);

/* Waits for CD sync to complete; if the sync result is "no intr" (2),
 * issues a CdlPause control command, then converts the resulting/last
 * CD position to an integer (sector count) and returns it. */
int func_80053D64(void) {
    unsigned char loc[4];

    if (CdSync(1, 0) == 2) {
        CdControl(0x10, 0, loc);
    }
    return CdPosToInt(loc);
}

#include "common.h"

extern int CdSync(int mode, unsigned char *result);
extern int CdControl(unsigned char com, unsigned char *param, unsigned char *result);
extern int CdPosToInt(unsigned char *loc);

unsigned char D_800814B8[16];

/* Refreshes the CD position when sync returns 2 and returns its sector count. */
int func_8003F55C(void) {
    if (CdSync(1, 0) == 2) {
        CdControl(0x10, 0, D_800814B8);
    }
    return CdPosToInt(D_800814B8);
}

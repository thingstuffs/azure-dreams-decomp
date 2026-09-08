#include "common.h"

extern int CdSync(int mode, unsigned char *result);
extern int CdControl(unsigned char com, unsigned char *param, unsigned char *result);
extern int CdPosToInt(unsigned char *loc);

/* Reads the CD position when the sync status is 2 and converts the position to a sector number. */
int func_80053D64(void) {
    unsigned char cd_position[4];

    if (CdSync(1, 0) == 2) {
        CdControl(0x10, 0, cd_position);
    }
    return CdPosToInt(cd_position);
}

#include "common.h"
#include "engine/audio.h"
#include "sdk/libcd.h"

/* Reads the CD position when the sync status is 2 and converts the position to a sector number. */
int sound_get_cd_sector_position(void) {
    unsigned char cd_position[4];

    if (CdSync(1, 0) == 2) {
        CdControl(0x10, 0, cd_position);
    }
    return CdPosToInt(cd_position);
}

#include "common.h"
#include "engine/cd.h"
#include "sdk/libcd.h"
#include "slus/data.h"

/* Refreshes the CD position when sync returns 2 and returns its sector count. */
int cd_poll_and_get_sector(void) {
    if (CdSync(1, 0) == 2) {
        CdControl(0x10, 0, cd_sector_position_result);
    }
    return CdPosToInt(cd_sector_position_result);
}

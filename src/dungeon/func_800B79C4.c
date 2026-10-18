#include "modules/dungeon_cd_control.h"

/* Submit D_800DF3DC and reset D_800DCF4D to -1. */
void submit_control_and_reset_status(void) {
    Control_CD(6, &D_800DF3DC, 0);
    D_800DCF4D = -1;
}

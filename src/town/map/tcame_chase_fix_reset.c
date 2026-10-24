#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 town_camera_chase_setting;

/* tcame_chase_fix_reset: clear the camera chase fix value. */
void tcame_chase_fix_reset(void) {
    town_camera_chase_setting = 0;
}

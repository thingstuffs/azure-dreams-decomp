#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 town_camera_chase_setting;

/* tcame_chase_fix: set the camera chase fix value. */
void tcame_chase_fix(s32 value) {
    town_camera_chase_setting = value;
}

#include "common.h"
#include "shared/game_work.h"

extern void to_camera_zero_00();

/* Clear the state field or invoke updates according to the record value. */
void func_80090A04(void *record) {
    s16 threshold_value = *(s16 *)((u8 *)record + 6);
    GameWork *state = &gameWork;

    if (threshold_value < 0x200) {
        state->view.viewAngle = 0;
        return;
    }
    if (threshold_value < 0x300) {
        to_camera_zero_00(state);
        to_camera_zero_00();
    }
    to_camera_zero_00();
    to_camera_zero_00();
}

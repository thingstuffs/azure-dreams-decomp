#include "common.h"
#include "shared/game_work.h"

extern s32 directional_buttons_to_angle(s32);

/* Adds an offset to the shared angle and wraps to 12 bits, preserving failure. */
s32 input_angle_with_offset(s32 unused, s32 angle_offset) {
    s32 base_angle;

    base_angle = directional_buttons_to_angle(g_game_work.buttons);
    if ((s16)base_angle == -1) {
        return -1;
    }
    return (base_angle + angle_offset) & 0xFFF;
}

#include "common.h"
#include "shared/game_work.h"

extern u32 D_80100D94[];

extern s32 step_angle_12_toward(s32, s32, s32);

/* Applies a pending intensity change to three channels and clears completed state. */
void update_view_gray_level(void)
{
    s32 target_level;
    GameWork *channels;
    u32 change_mode;
    s32 level;

    channels = &g_game_work;
    if (D_80100D94[0] == 0) {
        return;
    }
    change_mode = D_80100D94[0];
    switch (change_mode) {
    case 0:
        channels->view.tint.parts.tint_r = 0x80;
        channels->view.tint.parts.tint_g = 0x80;
        channels->view.tint.parts.tint_b = 0x80;
        D_80100D94[0] = 0;
        return;

    case 1:
        channels->view.tint.parts.tint_r = 0;
        channels->view.tint.parts.tint_g = 0;
        channels->view.tint.parts.tint_b = 0;
        D_80100D94[0] = 0;
        return;

    case 2:
        channels->view.tint.parts.tint_r = 0x40;
        channels->view.tint.parts.tint_g = 0x40;
        channels->view.tint.parts.tint_b = 0x40;
        D_80100D94[0] = 0;
        return;

    case 3:
        target_level = 0x80;
        break;

    case 4:
        target_level = 0;
        break;

    case 5:
        target_level = 0x40;
        break;

    default:
        return;
    }

    target_level &= 0xFF;
    level = step_angle_12_toward(channels->view.tint.parts.tint_r, target_level, 8);
    channels->view.tint.parts.tint_r = level;
    channels->view.tint.parts.tint_g = level;
    channels->view.tint.parts.tint_b = level;
    if ((level & 0xFF) == target_level) {
        D_80100D94[0] = 0;
    }
}

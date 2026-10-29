#include "common.h"
#include "shared/game_work.h"
#include "town/map.h"
#include "town/player.h"

extern u32 view_gray_command[];

/* Applies a pending intensity change to three channels and clears completed state. */
void update_view_gray_level(void)
{
    s32 target_level;
    GameWork *channels;
    u32 change_mode;
    s32 level;

    channels = &g_game_work;
    if (view_gray_command[0] == 0) {
        return;
    }
    change_mode = view_gray_command[0];
    switch (change_mode) {
    case 0:
        channels->view.tint.parts.tint_r = 0x80;
        channels->view.tint.parts.tint_g = 0x80;
        channels->view.tint.parts.tint_b = 0x80;
        view_gray_command[0] = 0;
        return;

    case 1:
        channels->view.tint.parts.tint_r = 0;
        channels->view.tint.parts.tint_g = 0;
        channels->view.tint.parts.tint_b = 0;
        view_gray_command[0] = 0;
        return;

    case 2:
        channels->view.tint.parts.tint_r = 0x40;
        channels->view.tint.parts.tint_g = 0x40;
        channels->view.tint.parts.tint_b = 0x40;
        view_gray_command[0] = 0;
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
        view_gray_command[0] = 0;
    }
}

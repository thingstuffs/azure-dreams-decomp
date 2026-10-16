#include "common.h"
#include "shared/game_work.h"

extern u32 D_80100D94[];

extern s32 townStepAngle12Toward(s32, s32, s32);

/* Applies a pending intensity change to three channels and clears completed state. */
void townUpdateViewGrayLevel(void)
{
    s32 target_level;
    GameWork *channels;
    u32 change_mode;
    s32 level;

    channels = &gameWork;
    if (D_80100D94[0] == 0) {
        return;
    }
    change_mode = D_80100D94[0];
    switch (change_mode) {
    case 0:
        channels->view.unk_090 = 0x80;
        channels->view.unk_091 = 0x80;
        channels->view.unk_092 = 0x80;
        D_80100D94[0] = 0;
        return;

    case 1:
        channels->view.unk_090 = 0;
        channels->view.unk_091 = 0;
        channels->view.unk_092 = 0;
        D_80100D94[0] = 0;
        return;

    case 2:
        channels->view.unk_090 = 0x40;
        channels->view.unk_091 = 0x40;
        channels->view.unk_092 = 0x40;
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
    level = townStepAngle12Toward(channels->view.unk_090, target_level, 8);
    channels->view.unk_090 = level;
    channels->view.unk_091 = level;
    channels->view.unk_092 = level;
    if ((level & 0xFF) == target_level) {
        D_80100D94[0] = 0;
    }
}

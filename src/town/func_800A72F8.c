#include "common.h"
#include "shared/game_work.h"

extern u32 D_80100D94[];
extern void *D_80089110[];

extern s32 func_80094AA0(s32, s32, s32);

/* Applies a pending intensity change to three channels and clears completed state. */
void func_800A4A58(void)
{
    s32 target_level;
    GameWork *channels;
    u32 change_mode;
    s32 level;
    static void *const case_labels[] = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4, &&case_5
    };

    channels = &gameWork;
    if (D_80100D94[0] == 0) {
        goto done;
    }
    change_mode = D_80100D94[0];
    if (change_mode >= 6) {
        goto done;
    }
    goto *D_80089110[change_mode];

case_0:
    channels->unk_0A8 = 0x80;
    channels->unk_0A9 = 0x80;
    channels->unk_0AA = 0x80;
    D_80100D94[0] = 0;
    goto done;

case_1:
    channels->unk_0A8 = 0;
    channels->unk_0A9 = 0;
    channels->unk_0AA = 0;
    D_80100D94[0] = 0;
    goto done;

case_2:
    channels->unk_0A8 = 0x40;
    channels->unk_0A9 = 0x40;
    channels->unk_0AA = 0x40;
    D_80100D94[0] = 0;
    goto done;

case_3:
    target_level = 0x80;
    goto update;

case_4:
    target_level = 0;
    goto update;

case_5:
    target_level = 0x40;
update:
    target_level &= 0xFF;
    level = func_80094AA0(channels->unk_0A8, target_level, 8);
    channels->unk_0A8 = level;
    channels->unk_0A9 = level;
    channels->unk_0AA = level;
    if ((level & 0xFF) == target_level) {
        D_80100D94[0] = 0;
    }

done:
    return;
}

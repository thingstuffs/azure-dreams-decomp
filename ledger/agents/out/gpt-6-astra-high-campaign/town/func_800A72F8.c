#include "common.h"

extern u32 D_80100D94[];
extern u8 D_80083160[];
extern void *D_80089110[];

extern s32 func_80094AA0(s32, s32, s32);

/* Applies a pending intensity change to three channels and clears completed state. */
void func_800A4A58(void)
{
    s32 target_level;
    u8 *channels;
    u32 change_mode;
    s32 level;
    u32 *state_page;
    static void *const case_labels[] = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4, &&case_5
    };

    channels = D_80083160;
    if (D_80100D94[0] == 0) {
        goto done;
    }
    change_mode = D_80100D94[0];
    if (change_mode >= 6) {
        goto done;
    }
    goto *D_80089110[change_mode];

case_0:
    channels[0xA8] = 0x80;
    channels[0xA9] = 0x80;
    channels[0xAA] = 0x80;
    goto clear_state;

case_1:
    {
        state_page = (u32 *)0x80100000;
        channels[0xA8] = 0;
        channels[0xA9] = 0;
        channels[0xAA] = 0;
        goto clear_store;
    }

case_2:
    channels[0xA8] = 0x40;
    channels[0xA9] = 0x40;
    __asm__ __volatile__("" ::: "memory");
    channels[0xAA] = 0x40;
    goto clear_state;

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
    level = func_80094AA0(channels[0xA8], target_level, 8);
    channels[0xA8] = level;
    channels[0xA9] = level;
    channels[0xAA] = level;
    if ((level & 0xFF) == target_level) {
clear_state:
        state_page = (u32 *)0x80100000;
clear_store:
        state_page[0xD94 / 4] = 0;
    }

done:
    return;
}

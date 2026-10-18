#include "slus/sound_reset_state.h"

/* Resets SPU playback state and initializes voice sentinels for the master channel. */
void func_8005CA90(s32 channel)
{
    s32 saved_channel = channel;
    s32 channel_value;
    s32 voice_index;

    ResetCallback(channel);
    func_8005CC04(saved_channel);

    if (saved_channel == 0) {
        u16 sentinel = 0xC000;
        for (voice_index = 23; voice_index >= 0; voice_index--) {
            D_80079520[voice_index] = sentinel;
        }
    }

    func_8005CB88();

    channel_value = D_800799C0[0];

    D_800794F8 = 0;
    D_800794FC = 0;
    D_80079508 = 0;
    D_8007950C = 0;
    D_8007950E = 0;
    D_80079510 = 0;
    D_80079514 = 0;
    D_80079500 = (u32)channel_value;

    store_u16_table_entry(0xD1, channel_value, 0);

    D_800799B4 = 0;
    D_800799B8 = 0;
    D_800799BC = 0;
    D_800794F4 = 0;
    D_80079974 = 0;
    D_800794F0 = 0;
    D_8007951C = 0;
    D_80079518 = 0;
    D_80079950 = 0;
}

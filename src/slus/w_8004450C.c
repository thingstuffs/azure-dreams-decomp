#include "slus/gp_af3_pair.h"

s32 func_8004450C(s16 state_index)
{
    if (D_80080AF3 != state_index) {
        S_8006E6F4 *state_table = D_8006E6F4;
        S_8006E6F4 *state_entry = state_table + state_index;

        Control_CD(6, (void *)state_entry->field4, 0);
        DrawSync(0);
        {
            void *state_callback = state_entry->field0;
            D_80081480 = D_8008148C;
            Control_CD(6, state_callback, 0);
        }
        D_80080AF3 = (s8)state_index;
        drain_cd_command_queue();
        func_8003F5E0(D_8008148C);
        SD_Call(0x11);
        func_800542BC();
        while (test_sound_channel_availability(0) != 1) {
        }
        return 0;
    }
    return 1;
}
